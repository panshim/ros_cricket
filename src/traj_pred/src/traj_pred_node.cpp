#include "ros/ros.h"
#include "traj_pred/traj_predictor.hpp"
#include <sstream>

int main(int argc, char** argv)
{
  ros::init(argc, argv, "traj_pred_node");
  ros::NodeHandle nh;

  TrajPredictor traj_predictor(nh, atof(argv[1]), "ball/real_pos", "ball/pos_in_secs", "ball/target");
  ros::spin();
}
