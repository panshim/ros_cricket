#include "ros/ros.h"
#include "multi_view_plugin/multi_view_sys.hpp"

int main(int argc, char **argv)
{
  ros::init(argc, argv, "tracking_node");
  ros::NodeHandle nh;

  MultiViewSys mvs(nh);
  ros::spin();
}
