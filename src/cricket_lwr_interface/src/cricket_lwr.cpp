#include "cricket_lwr_interface/cricket_lwr.hpp"

LwrCartesianCommand::LwrCartesianCommand(ros::NodeHandle& nh): nh(nh)
{
    // Initialize jntClientPtr Client
    ROS_INFO("Creating action client for lwr-Controller ......");
    jntClientPtr.reset( new lwr_action_client("/lwr/joint_trajectory_controller/follow_joint_trajectory") );

        // Wait for arm controller action server to come up
    int iterations = 0, max_iterations = 3;
    while( !jntClientPtr->waitForServer(ros::Duration(2.0)) && ros::ok() && iterations < max_iterations )
   {
     ROS_DEBUG("Waiting for the arm_controller_action server to come up");
     ++iterations;
    }
    if ( iterations == max_iterations )
    {
        ROS_ERROR("Error in createArmClient: arm controller action server not available");
    }
    ROS_INFO("...... LWR-Controller has been created");


    // Initialize Subscriber
    subCartCmd = nh.subscribe("cartesian_pos_cmd", 10, &LwrCartesianCommand::callback_cartesian, this);
    goalCmd.trajectory.header.stamp = ros::Time::now();

    // Initialize The joint names & size
    goalCmd.trajectory.joint_names.push_back("lwr_a1_joint");
    goalCmd.trajectory.joint_names.push_back("lwr_a2_joint");
    goalCmd.trajectory.joint_names.push_back("lwr_a3_joint");
    goalCmd.trajectory.joint_names.push_back("lwr_a4_joint");
    goalCmd.trajectory.joint_names.push_back("lwr_a5_joint");
    goalCmd.trajectory.joint_names.push_back("lwr_a6_joint");
    goalCmd.trajectory.joint_names.push_back("lwr_e1_joint");
    goalCmd.trajectory.points.resize(2);
    
}

LwrCartesianCommand::~LwrCartesianCommand(){;}

void LwrCartesianCommand::callback_cartesian(const geometry_msgs::Pose poseCmd)
{
    ROS_INFO("Got the Cartesian Target. Then need moving ......");
    goalCmd.goal_time_tolerance = ros::Duration(5);
    
    // First trajectory positions
    goalCmd.trajectory.header.stamp = ros::Time::now();
    int index = 0;
    goalCmd.trajectory.points[index].positions.resize(7);
    goalCmd.trajectory.points[index].positions[0] = 0.2;
    goalCmd.trajectory.points[index].positions[1] = 0.0;
    goalCmd.trajectory.points[index].positions[2] = -1.5;
    goalCmd.trajectory.points[index].positions[3] = 1.94;
    goalCmd.trajectory.points[index].positions[4] = -1.57;
    goalCmd.trajectory.points[index].positions[5] = -0.5;
    goalCmd.trajectory.points[index].positions[6] = 0.0;
    // Velocities
    goalCmd.trajectory.points[index].velocities.resize(7);

    for (int j = 0; j < 7; ++j)
        goalCmd.trajectory.points[index].velocities[j] = 1.0;
    goalCmd.trajectory.points[index].time_from_start = ros::Duration(2);

    // Second trajectory point
    // Positions
    index += 1;
    goalCmd.trajectory.points[index].positions.resize(7);
    goalCmd.trajectory.points[index].positions[0] = 2.5;
    goalCmd.trajectory.points[index].positions[1] = 0.2;
    goalCmd.trajectory.points[index].positions[2] = -2.1;
    goalCmd.trajectory.points[index].positions[3] = 1.9;
    goalCmd.trajectory.points[index].positions[4] = 1.0;
    goalCmd.trajectory.points[index].positions[5] = -0.5;
    goalCmd.trajectory.points[index].positions[6] = 0.0;
    // Velocities
    goalCmd.trajectory.points[index].velocities.resize(7);
    for (int j = 0; j < 7; ++j)
    {
        goalCmd.trajectory.points[index].velocities[j] = 0.0;
    }
    // To be reached 4 seconds after starting along the trajectory
    goalCmd.trajectory.points[index].time_from_start = ros::Duration(4.0);

    // Request Action
    LwrCartesianCommand::action_joint_request();
    while(!(jntClientPtr->getState().isDone()) && ros::ok())
    {
        ros::Duration(4).sleep(); // sleep for four seconds
    }
}

void LwrCartesianCommand::publish_jointspace(const trajectory_msgs::JointTrajectory jntCmd)
{
    ;
}

void LwrCartesianCommand::action_joint_request()
{
    ROS_INFO("Requesting LWR Control Action Server ...");
    jntClientPtr->sendGoal(goalCmd);
    ROS_INFO("... Request End");
}