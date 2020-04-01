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
#include <kdl/chainiksolverpos_nr.hpp>
// #include <kdl/chainfksolverpos_recursive.hpp>
// #include <kdl/chainiksolvervel_pinv.hpp>
typedef actionlib::SimpleActionClient<control_msgs::FollowJointTrajectoryAction> lwr_action_client;
typedef boost::shared_ptr<lwr_action_client>  lwr_action_client_Ptr;

class LwrCartesianCommand
{
    private:
        ros::NodeHandle nh;
        /* Subscriber & Publisher & Actionlib Client*/
        ros::Subscriber subCartCmd;
        ros::Publisher pubJntCmd;
        lwr_action_client_Ptr jntClientPtr;
        /* KDL Inverse Kinematics */
        KDL::ChainIkSolverPos* solvIk;
        KDL::ChainIkSolverVel* solvIkVel;
        /* Cartesian & JointSpace Command */
        geometry_msgs::Pose poseCmd;
        control_msgs::FollowJointTrajectoryGoal goalCmd;

    public:
        LwrCartesianCommand(ros::NodeHandle& nh);
        ~LwrCartesianCommand();
        void callback_cartesian(const geometry_msgs::Pose poseCmd);
        void publish_jointspace(const trajectory_msgs::JointTrajectory jntCmd);
        void action_joint_request();

};