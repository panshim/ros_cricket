#ifndef _CRICKET_LWR_H_
#define _CRICKET_LWR_H_

// ROS
#include <ros/ros.h>
#include <geometry_msgs/Pose.h>
#include <actionlib/client/simple_action_client.h>
#include <control_msgs/FollowJointTrajectoryAction.h>
#include <trajectory_msgs/JointTrajectory.h>
// Boost headers
#include <boost/shared_ptr.hpp>
// KDL
#include <kdl_parser/kdl_parser.hpp>
#include <kdl/chainiksolvervel_pinv.hpp>
#include <kdl/chainfksolverpos_recursive.hpp>
#include <kdl/chainiksolverpos_lma.hpp>
#include <kdl/chainiksolverpos_nr.hpp>

typedef actionlib::SimpleActionClient<control_msgs::FollowJointTrajectoryAction> lwr_action_client;
typedef boost::shared_ptr<lwr_action_client>  lwr_action_client_Ptr;

#define INVERSE_KINE_TIME_STEP 0.8

class LwrCartesianCommand
{
    private:
        ros::NodeHandle nh;
        /* Subscriber & Publisher & Actionlib Client*/
        ros::Subscriber subCartCmd;
        ros::Publisher pubJntCmd;
        trajectory_msgs::JointTrajectory contrCmd;
        lwr_action_client_Ptr jntClientPtr;
        /* KDL Inverse Kinematics */
        KDL::ChainFkSolverPos* solvFk;
        KDL::ChainIkSolverVel* solvIkVel;
        KDL::ChainIkSolverPos* solvIk;
        KDL::ChainIkSolverPos* solvIk2;
        KDL::Tree tree;
        KDL::Chain chain;
        std::string robot_description_string;
        KDL::JntArray jointArrNrOut;
        KDL::JntArray jointArrInit;
        /* Cartesian & JointSpace Command */
        geometry_msgs::Pose poseCmd;
        control_msgs::FollowJointTrajectoryGoal goalCmd;
        // Set-up a timer with a period of one millisecond
        ros::Timer timer;

    public:
        LwrCartesianCommand(ros::NodeHandle& nh);
        ~LwrCartesianCommand();
        void callback_cartesian(geometry_msgs::Pose poseCmd);
        void callback_timer(const ros::TimerEvent& event);
        void action_joint_request();

};

#endif