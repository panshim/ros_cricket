#ifndef _CRICKET_REFLEXXES_H_
#define _CRICKET_REFLEXXES_H_

// C++
#include <iostream>
#include <string>
// ROS
#include <ros/ros.h>
#include <geometry_msgs/Pose.h>
#include <tf/tf.h>
#include <geometry_msgs/Twist.h>
#include <sensor_msgs/JointState.h>

// Reflexxes Motion Planning Library
#include <ReflexxesAPI.h>
#include <RMLPositionFlags.h>
#include <RMLPositionInputParameters.h>
#include <RMLPositionOutputParameters.h>

// KDL
#include <kdl/chainfksolvervel_recursive.hpp>
#include <kdl_parser/kdl_parser.hpp>
#include <kdl/jntarrayvel.hpp>
#include <kdl/framevel.hpp>

// self-made
#include "tf_operation.hpp"
#include "lwr_controllers/PoseRPY.h"

// defines
#define CYCLE_TIME_IN_SECONDS   0.1 // 1/n Hz traj. command frequency
#define NUMBER_OF_DOFS          6   // 6 DOF EndEffector
#define Pi                      3.14159265358979323846
class CricketReflexxes
{
    private:
        // ROS Object
        ros::NodeHandle nh;
        TFOperation tf_oper;
        geometry_msgs::Pose reflexxesTarget;
        geometry_msgs::Pose cartesian_pos_next_cmd;
        lwr_controllers::PoseRPY inv_pos_next_cmd;
        tf::Transform batTransform;
        tf::Transform eeTransform;
        
        // Publisher & Subscriber
        ros::Subscriber sub_reflex_target;
        ros::Subscriber sub_reflex_twist;
        ros::Subscriber sub_jointstate;
        ros::Publisher pub_next_cart;
        ros::Publisher pub_inv_next_cart;

        // Set-up a timer with a period of one millisecond
        ros::Timer timer;
        ros::Time prevTime;
        ros::Time nowTime;
        double intervalTime;
        
        // KDL: Forward Velocity
        KDL::Tree tree;
        KDL::Chain chain;
 	    KDL::ChainFkSolverVel_recursive* solv_fd_vel;
        KDL::JntArrayVel jntArrayVel;
        KDL::FrameVel frameVel;

        // Creating all relevant objects of the Type II Reflexxes Motion Library
        RMLPositionInputParameters  *IP;
        RMLPositionOutputParameters *OP;
        RMLPositionFlags            Flags;
        ReflexxesAPI                *RML;
        int                         ResultValue;

    public:
        CricketReflexxes(ros::NodeHandle nh);
        ~CricketReflexxes();
        void TimerCallback(const ros::TimerEvent&);
        void SubMsgCallbackPose(const geometry_msgs::Pose rcv_msg);
        void SubMsgCallbackTwist(const geometry_msgs::Twist rcv_msg);
        void SubMsgCallbackJnt(const sensor_msgs::JointState recv_js);
        template<class T> static void QuaternionToRPY(const T Quat, double &roll, double &pitch, double &yaw);
        void RPYToQuaternion(tf::Quaternion &Quat, double roll, double pitch, double yaw);
        double RotationPrincipleValue(double rad);//switch rotation to [-pi,pi]
};
#endif