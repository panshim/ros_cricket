#include "cricket_lwr_interface/cricket_lwr.hpp"
#include "tf/transform_datatypes.h"
#define QUA_EPS 0.001
#define EPSI 0.00001
LwrCartesianCommand::LwrCartesianCommand(ros::NodeHandle& nh): nh(nh), timerLock(false)
{
    // 1. Initialize jntClientPtr Client
    ROS_INFO("------Begin: Creating action client for lwr-Controller------");
    jntClientPtr.reset( new lwr_action_client("/lwr/joint_trajectory_controller/follow_joint_trajectory") );

    int iterations = 0, max_iterations = 3; //Wait for arm controller action server to come up
    while( !jntClientPtr->waitForServer(ros::Duration(2.0)) && ros::ok() && iterations < max_iterations )
   {
     ROS_DEBUG("Waiting for the arm_controller_action server to come up!");
     ++iterations;
    }
    if ( iterations == max_iterations )
    {
        ROS_ERROR("Error in createArmClient: arm controller action server not available");
    }
    ROS_INFO("---------------End: LWR-Controller Created---------------");


    // 2. Initialize description parser & chain & Inverse Kinematics Solver
    nh.param("robot_description", robot_description_string, std::string());
    if(kdl_parser::treeFromString(robot_description_string, tree))
    {
        if(tree.getChain("lwr_base_link", "lwr_7_link", chain))
        {
            solvFk = new KDL::ChainFkSolverPos_recursive(chain);
            solvIkVel = new KDL::ChainIkSolverVel_pinv(chain);
            solvIk2 = new KDL::ChainIkSolverPos_NR(chain, *solvFk, *solvIkVel);
            solvIk = new KDL::ChainIkSolverPos_LMA(chain);
        }
        else{
            ROS_ERROR("Cannot get a chain!");
        }
    }
    else{
        ROS_ERROR("Cannot get a tree!");
    }

    jointArrNrOut.resize(chain.getNrOfJoints());
    jointArrInit.resize(chain.getNrOfJoints());

    // 3. Initialize Subscriber
    subCartCmd = nh.subscribe<geometry_msgs::Pose>("cartesian_pos_cmd", 10, &LwrCartesianCommand::callback_cartesian, this);

    // 4. Initialize The joint names & size
    goalCmd.trajectory.header.stamp = ros::Time::now();
    goalCmd.trajectory.joint_names.resize(7);
    goalCmd.trajectory.joint_names[0] = "lwr_a1_joint";
    goalCmd.trajectory.joint_names[1] = "lwr_a2_joint";
    goalCmd.trajectory.joint_names[2] = "lwr_e1_joint";
    goalCmd.trajectory.joint_names[3] = "lwr_a3_joint";
    goalCmd.trajectory.joint_names[4] = "lwr_a4_joint";
    goalCmd.trajectory.joint_names[5] = "lwr_a5_joint";
    goalCmd.trajectory.joint_names[6] = "lwr_a6_joint";
    goalCmd.trajectory.points.resize(1);

    /* 4.1 backup: using publisher */
    pubJntCommand = nh.advertise<control_msgs::FollowJointTrajectoryActionGoal>("/lwr/joint_trajectory_controller/follow_joint_trajectory/goal", 10);
    goalCommand.header.stamp = ros::Time::now();
    goalCommand.goal.trajectory.joint_names.resize(7);
    goalCommand.goal.trajectory.joint_names[0] = "lwr_a1_joint";
    goalCommand.goal.trajectory.joint_names[1] = "lwr_a2_joint";
    goalCommand.goal.trajectory.joint_names[2] = "lwr_e1_joint";
    goalCommand.goal.trajectory.joint_names[3] = "lwr_a3_joint";
    goalCommand.goal.trajectory.joint_names[4] = "lwr_a4_joint";
    goalCommand.goal.trajectory.joint_names[5] = "lwr_a5_joint";
    goalCommand.goal.trajectory.joint_names[6] = "lwr_a6_joint";
    goalCommand.goal.trajectory.points.resize(1);

    /* 5. Initialize a Timer */
    timer = nh.createTimer(ros::Duration(INVERSE_KINE_TIME_STEP), &LwrCartesianCommand::callback_timer, this);
}


LwrCartesianCommand::~LwrCartesianCommand()
{
    // 1st set solver
    delete solvIk;
    // 2nd set solver
    delete solvFk;
    delete solvIkVel;
    delete solvIk2;
}


void LwrCartesianCommand::callback_cartesian(geometry_msgs::Pose poseMsg)
{
    /* Inverse Kinematics ChainIkSolverPos_NR */
    double den = sqrt( pow(poseMsg.orientation.x,2) + pow(poseMsg.orientation.y,2) + pow(poseMsg.orientation.z,2) + pow(poseMsg.orientation.w,2) );
    timerLock = true;
    if(0<den && den<QUA_EPS)
    {
        poseCmd.orientation.x = EPSI;
        poseCmd.orientation.y = EPSI;
        poseCmd.orientation.z = EPSI;
        poseCmd.orientation.w = 1;
        poseCmd.position = poseMsg.position;
    }
    else
    {
        poseCmd.orientation.x = poseMsg.orientation.x / den + EPSI;
        poseCmd.orientation.y = poseMsg.orientation.y / den + EPSI;
        poseCmd.orientation.z = poseMsg.orientation.z / den + EPSI;
        poseCmd.orientation.w = poseMsg.orientation.w / den + EPSI;
        poseCmd.position = poseMsg.position;
    }
}


void LwrCartesianCommand::callback_timer(const ros::TimerEvent& event)
{
    // should at least receive topic "cartesian_pos_cmd" once, before Inverse Kinematics
    if(!timerLock)
        return;

    /* construct "KDL::Rotation frameRot" */
    tf::Quaternion quat;
    tf::quaternionMsgToTF(poseCmd.orientation, quat);
    tf::Matrix3x3 rotMat(quat.normalize());
    KDL::Rotation frameRot(rotMat.getRow(0).getX(), rotMat.getRow(0).getY(), rotMat.getRow(0).getZ(),
                           rotMat.getRow(1).getX(), rotMat.getRow(1).getY(), rotMat.getRow(1).getZ(),
                           rotMat.getRow(2).getX(), rotMat.getRow(2).getY(), rotMat.getRow(2).getZ());
    
    /* construct "KDL::Frame fkTargetFrame" */
    KDL::Vector frameVec(poseCmd.position.x, poseCmd.position.y, poseCmd.position.z);
    KDL::Frame fkTargetFrame(frameRot, frameVec);
    
    /* Inverse Kinematics Solver */
    solvIk->CartToJnt(jointArrInit, fkTargetFrame, jointArrNrOut);

    // solvIk2->CartToJnt(jointArrInit, fkTargetFrame, jointArrNrOut);
    /* END: Inverse Kinematics ChainIkSolverPos_NR */

    /* BEGIN: Request Action */
    // int index = 0;
    // goalCmd.trajectory.points[index].positions.resize(7);
    // goalCmd.trajectory.points[index].positions[0] = jointArrNrOut(0);
    // goalCmd.trajectory.points[index].positions[1] = jointArrNrOut(1);
    // goalCmd.trajectory.points[index].positions[2] = jointArrNrOut(2);
    // goalCmd.trajectory.points[index].positions[3] = jointArrNrOut(3);
    // goalCmd.trajectory.points[index].positions[4] = jointArrNrOut(4);
    // goalCmd.trajectory.points[index].positions[5] = jointArrNrOut(5);
    // goalCmd.trajectory.points[index].positions[6] = jointArrNrOut(6);
    // goalCmd.trajectory.points[index].time_from_start = ros::Duration(0.1);
    // goalCmd.trajectory.header.stamp = ros::Time::now();
    // LwrCartesianCommand::action_joint_request();
    // while(!(jntClientPtr->getState().isDone()) && ros::ok())
    // {
    //     ros::Duration(0.001).sleep(); // sleep for four seconds
    // }
    /* END: Request Action */

    /* Backup: Using Publisher */
    int index = 0;
    goalCommand.goal.trajectory.points[index].positions.resize(7);
    goalCommand.goal.trajectory.points[index].positions[0] = jointArrNrOut(0);
    goalCommand.goal.trajectory.points[index].positions[1] = jointArrNrOut(1);
    goalCommand.goal.trajectory.points[index].positions[2] = jointArrNrOut(2);
    goalCommand.goal.trajectory.points[index].positions[3] = jointArrNrOut(3);
    goalCommand.goal.trajectory.points[index].positions[4] = jointArrNrOut(4);
    goalCommand.goal.trajectory.points[index].positions[5] = jointArrNrOut(5);
    goalCommand.goal.trajectory.points[index].positions[6] = jointArrNrOut(6);
    goalCommand.goal.trajectory.points[index].time_from_start = ros::Duration(0.1);
    goalCommand.goal.trajectory.header.stamp = ros::Time::now();
    pubJntCommand.publish(goalCommand);
}


void LwrCartesianCommand::action_joint_request()
{
    ROS_INFO("------Begin: Requesting LWR Control Action Server------");
    jntClientPtr->sendGoal(goalCmd);
}