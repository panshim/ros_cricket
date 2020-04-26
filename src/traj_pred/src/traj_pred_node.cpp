#include "ros/ros.h"
#include "traj_pred/traj_predictor.hpp"

int main(int argc, char** argv)
{
  ros::init(argc, argv, "traj_pred_node");
  ros::NodeHandle nh;
  
  TrajPredictor traj_predictor(nh, "ball/tracked_pos_kf", "ball/pos_after_1sec");
  ros::spin();
}
