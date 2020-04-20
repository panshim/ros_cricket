#ifndef _CRICKET_REFLEXXES_H_
#define _CRICKET_REFLEXXES_H_

#include <iostream>
// ROS
#include <ros/ros.h>
#include <geometry_msgs/Pose.h>
#include <tf/tf.h>
// Reflexxes Motion Planning Library
#include <ReflexxesAPI.h>
#include <RMLPositionFlags.h>
#include <RMLPositionInputParameters.h>
#include <RMLPositionOutputParameters.h>

#include "tf_operation.hpp"

// defines
#define CYCLE_TIME_IN_SECONDS   0.001 // 1000Hz traj. command frequency
#define NUMBER_OF_DOFS          6   // 6 DOF EndEffector

class CricketReflexxes
{
    private:
        // ROS Object
        ros::NodeHandle nh;
        geometry_msgs::Pose reflexxesTarget;
        geometry_msgs::Pose cartesian_pos_next_cmd;
        ros::Subscriber sub_reflex_target;
        ros::Publisher pub_next_cart;
        TFOperation tf_oper;
        // Set-up a timer with a period of one millisecond
        ros::Timer timer;
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
        void SubMsgCallback(const geometry_msgs::Pose rcv_msg);
        template<class T> static void QuaternionToRPY(const T Quat, double &roll, double &pitch, double &yaw);
        void RPYToQuaternion(tf::Quaternion &Quat, double roll, double pitch, double yaw);

};
#endif