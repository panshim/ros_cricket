#ifndef __EKF_NODE__
#define __EKF_NODE__

#include <ros/ros.h>
#include <tf/tf.h>
#include <tf/transform_listener.h>
#include <tf/transform_broadcaster.h>

#include "ekf.hpp"

#include <geometry_msgs/PointStamped.h>
#include <geometry_msgs/AccelStamped.h>

class EKFNode{

private:

  BFL::ColumnVector z;
  BFL::ColumnVector time;

  double rate;
  
  ros::NodeHandle nh;
  ros::NodeHandle nh_private;

  ros::Subscriber sub_pose;
  ros::Publisher  pub_pose;

  EKF ekf;
  
public:

  EKFNode( ros::NodeHandle& nh, ros::NodeHandle& nhp, double rate );
  
  //void callback_sensors( const NavSatFix& nsf, const Imu& imu );
  void callback_sensors( const geometry_msgs::PointStamped& sen);
  void update();

};

#endif
