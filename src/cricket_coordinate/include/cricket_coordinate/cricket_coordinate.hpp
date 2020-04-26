#ifndef _CRICKET_COORDINATE_H_
#define _CRICKET_COORDINATE_H_
// C++
#include <iostream>
// ROS
#include <ros/ros.h>
#include <geometry_msgs/Pose.h>
#include <geometry_msgs/AccelStamped.h>
#include <tf/transform_datatypes.h>
#include <geometry_msgs/Twist.h>
// Gazebo
#include <gazebo_msgs/GetModelState.h>
#include <gazebo_msgs/GetLinkState.h>

class CricketCoordinate
{
    private:
        /* publish ready position for lwr-arm */
        ros::Publisher pub_ready;
        geometry_msgs::Pose ready_pose;
        /* publish Reflexxes Traj. Command */
        ros::Publisher pub_reflexxes_pose;
        ros::Publisher pub_reflexxes_twist;
        /* subscribe estimated ball position */
        ros::Subscriber sub_ball;
        ros::NodeHandle nh;
        /* Gazebo: handles to get base_link & lwr_7_link */
        ros::ServiceClient cli_model_lwr;
        ros::ServiceClient cli_link_7;
        gazebo_msgs::GetLinkState srv_linkbasestate;
        gazebo_msgs::GetLinkState srv_link7state;
        // store Pose, Trans, etc. infomation
        geometry_msgs::Pose link_base_pose;
        geometry_msgs::Pose link_7_pose;
        tf::Transform link_base_trans;
        tf::Transform link_7_trans;

    public:
        CricketCoordinate(ros::NodeHandle nh);
        ~CricketCoordinate();
        void SubBallCallback(const geometry_msgs::AccelStamped rcv_msg);
        bool BallWithinRange(const geometry_msgs::AccelStamped ball_pose);
        bool getReady();
        static tf::Transform GeoposeToTftrans(const geometry_msgs::Pose geoPose);
        static tf::Transform GeoaccToTftrans(const geometry_msgs::AccelStamped geoAcc);
        static geometry_msgs::Pose TftransToGeopose(const tf::Transform trans);
};

#endif