#include "cricket_lwr_interface/cricket_lwr.hpp"
#include "tf/transform_datatypes.h"

LwrCartesianCommand::LwrCartesianCommand(ros::NodeHandle& nh): nh(nh)
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
        else
        {
            ROS_ERROR("Cannot get a chain!");
        }
    }
    else
    {
        ROS_ERROR("Cannot get a tree!");
    }

    jointArrNrOut.resize(chain.getNrOfJoints());
    jointArrInit.resize(chain.getNrOfJoints());

    // 3. Initialize Subscriber
    subCartCmd = nh.subscribe<geometry_msgs::Pose>("cartesian_pos_cmd", 100, &LwrCartesianCommand::callback_cartesian, this);
    goalCmd.trajectory.header.stamp = ros::Time::now();

    // 4. Initialize The joint names & size
    goalCmd.trajectory.joint_names.resize(7);
    goalCmd.trajectory.joint_names[0] = "lwr_a1_joint";
    goalCmd.trajectory.joint_names[1] = "lwr_a2_joint";
    goalCmd.trajectory.joint_names[2] = "lwr_e1_joint";
    goalCmd.trajectory.joint_names[3] = "lwr_a3_joint";
    goalCmd.trajectory.joint_names[4] = "lwr_a4_joint";
    goalCmd.trajectory.joint_names[5] = "lwr_a5_joint";
    goalCmd.trajectory.joint_names[6] = "lwr_a6_joint";
    goalCmd.trajectory.points.resize(1);

    // 4. Initialize Publisher
    // pubJntCmd = nh.advertise<trajectory_msgs::JointTrajectory>("lwr/joint_trajectory_controller/command", 100);
    // contrCmd.joint_names.resize(7);
    // contrCmd.points.resize(1);
    // contrCmd.joint_names[0] = "lwr_a1_joint";
    // contrCmd.joint_names[1] = "lwr_a2_joint";
    // contrCmd.joint_names[2] = "lwr_e1_joint";
    // contrCmd.joint_names[3] = "lwr_a3_joint";
    // contrCmd.joint_names[4] = "lwr_a4_joint";
    // contrCmd.joint_names[5] = "lwr_a5_joint";
    // contrCmd.joint_names[6] = "lwr_a6_joint";
}


LwrCartesianCommand::~LwrCartesianCommand(){;}


void LwrCartesianCommand::callback_cartesian(geometry_msgs::Pose poseCmd)
{
    /* Inverse Kinematics ChainIkSolverPos_NR */
    double den = sqrt( pow(poseCmd.orientation.x,2) + pow(poseCmd.orientation.y,2) + pow(poseCmd.orientation.z,2) + pow(poseCmd.orientation.w,2) );
    poseCmd.orientation.x = poseCmd.orientation.x / den;
    poseCmd.orientation.y = poseCmd.orientation.y / den;
    poseCmd.orientation.z = poseCmd.orientation.z / den;
    poseCmd.orientation.w = poseCmd.orientation.w / den;

    tf::Quaternion quat;
    tf::quaternionMsgToTF(poseCmd.orientation, quat);
    tf::Matrix3x3 rotMat(quat.normalize());
    KDL::Vector rowVec0(rotMat.getRow(0).getX(), rotMat.getRow(0).getY(), rotMat.getRow(0).getZ());
    KDL::Vector rowVec1(rotMat.getRow(1).getX(), rotMat.getRow(1).getY(), rotMat.getRow(1).getZ());
    KDL::Vector rowVec2(rotMat.getRow(2).getX(), rotMat.getRow(2).getY(), rotMat.getRow(2).getZ());
    KDL::Rotation frameRot(rowVec0, rowVec1, rowVec2);
    KDL::Vector frameVec(poseCmd.position.x, poseCmd.position.y, poseCmd.position.z);
    KDL::Frame fkTargetFrame(frameRot, frameVec);
    solvIk->CartToJnt(jointArrInit, fkTargetFrame, jointArrNrOut);

    KDL::JntArray jointArrNrOut2;
    solvIk2->CartToJnt(jointArrInit, fkTargetFrame,jointArrNrOut2);
    /* END: Inverse Kinematics ChainIkSolverPos_NR */

    /* BEGIN: Publisher */
    // contrCmd.points[0].positions[0] = 1.0;
    // contrCmd.points[0].positions[1] = 0;
    // contrCmd.points[0].positions[2] = 0;
    // contrCmd.points[0].positions[3] = 0;
    // contrCmd.points[0].positions[4] = 0;
    // contrCmd.points[0].positions[5] = 0;
    // contrCmd.points[0].positions[6] = 0;
    // contrCmd.points[0].positions.push_back(jointArrNrOut(0));
    // contrCmd.points[0].positions.push_back(jointArrNrOut(1));
    // contrCmd.points[0].positions.push_back(jointArrNrOut(2));
    // contrCmd.points[0].positions.push_back(jointArrNrOut(3));
    // contrCmd.points[0].positions.push_back(jointArrNrOut(4));
    // contrCmd.points[0].positions.push_back(jointArrNrOut(5));
    // contrCmd.points[0].positions.push_back(jointArrNrOut(6));
    // contrCmd.header.stamp = ros::Time::now();
    // contrCmd.points[0].time_from_start = ros::Duration(1.0);
    // pubJntCmd.publish(contrCmd);
    /* END: Publisher */

    /* BEGIN: Request Action */
    goalCmd.trajectory.header.stamp = ros::Time::now();
    int index = 0;
    goalCmd.trajectory.points[index].positions.resize(7);
    goalCmd.trajectory.points[index].positions[0] = jointArrNrOut(0);
    goalCmd.trajectory.points[index].positions[1] = jointArrNrOut(1);
    goalCmd.trajectory.points[index].positions[2] = jointArrNrOut(2);
    goalCmd.trajectory.points[index].positions[3] = jointArrNrOut(3);
    goalCmd.trajectory.points[index].positions[4] = jointArrNrOut(4);
    goalCmd.trajectory.points[index].positions[5] = jointArrNrOut(5);
    goalCmd.trajectory.points[index].positions[6] = jointArrNrOut(6);
    goalCmd.trajectory.points[index].time_from_start = ros::Duration(1.0);

    LwrCartesianCommand::action_joint_request();
    while(!(jntClientPtr->getState().isDone()) && ros::ok())
    {
        ros::Duration(0.1).sleep(); // sleep for four seconds
    }
    /* END: Request Action */
}


void LwrCartesianCommand::publish_jointspace(const trajectory_msgs::JointTrajectory jntCmd)
{
    ;
}


void LwrCartesianCommand::action_joint_request()
{
    ROS_INFO("------Begin: Requesting LWR Control Action Server------");
    jntClientPtr->sendGoal(goalCmd);
    ROS_INFO("-----------------End: Requesting--------------------");
}