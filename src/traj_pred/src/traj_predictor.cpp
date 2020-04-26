#include "traj_pred/traj_predictor.hpp"

TrajPredictor::TrajPredictor(ros::NodeHandle& nh, std::string topic_sub, std::string topic_pub) : nh_(nh), topic_sub_(topic_sub), topic_pub_(topic_pub)
{
  sub = nh_.subscribe(topic_sub_, 10, &TrajPredictor::calCallback, this);
  pub = nh.advertise<geometry_msgs::PointStamped>(topic_pub_, 10);

  A = cv::Mat::zeros(1, 3, CV_32F);
  X = cv::Mat::zeros(3, 3, CV_32F);
  B = cv::Mat::zeros(1, 3, CV_32F);

  i = 0;
  start_time = 0;
  trigger = false;
}

TrajPredictor::~TrajPredictor(){}

void TrajPredictor::calCallback(const geometry_msgs::PointStamped::ConstPtr& msg)
{
  current_pos = cv::Point3f(msg->point.x, msg->point.y, msg->point.z);
  if (i != 0)
  {
    if (!trigger)
    {
      float dz = current_pos.z - last_pos.z;
      if (current_pos.z > 1) // trigger
      {
        trigger = true;
        std::cout << "polynomial curve fitting starts." << std::endl;
        start_time = last_time;
        float dt = msg->header.stamp.toSec() - start_time;
        cv::Mat new_A_row = (cv::Mat_<float>(1, 3) << dt * dt, dt, 1);
        cv::Mat new_B_row = (cv::Mat_<float>(1, 3) << current_pos.x, current_pos.y, current_pos.z);
        A.at<float>(0, 2) = 1;
        A.push_back(new_A_row);
        B.at<float>(0, 0) = last_pos.x;
        B.at<float>(0, 1) = last_pos.y;
        B.at<float>(0, 2) = last_pos.z;
        B.push_back(new_B_row);
      }
    }
    else
    {
      if (current_pos.z < 0.2) // ball on the ground, reset
      {
        trigger = false;
        start_time = 0;
        last_time = msg->header.stamp.toSec();
        last_pos = current_pos;
        A = cv::Mat(1, 3, CV_32F);
        B = cv::Mat(1, 3, CV_32F);
        i++;
        return;
      }
      float dt = msg->header.stamp.toSec() - start_time;
      cv::Mat new_A_row = (cv::Mat_<float>(1, 3) << dt * dt, dt, 1);
      cv::Mat new_B_row = (cv::Mat_<float>(1, 3) << current_pos.x, current_pos.y, current_pos.z);
      A.push_back(new_A_row);
      B.push_back(new_B_row);
      if (A.rows >= 5) // have more than 5 samples, start fitting curves
      {
        TrajPredictor::solveLS();
        geometry_msgs::PointStamped msg_pub;
        msg_pub.header.stamp = msg->header.stamp;
        msg_pub.header.frame_id = "world";
        cv::Mat dt_one_sec = (cv::Mat_<float>(1, 3) << (dt + 0.5) * (dt + 0.5), dt + 0.5, 1); // half second later
        cv::Mat pos_one_sec = dt_one_sec * X; 
        msg_pub.point.x = pos_one_sec.at<float>(0);
        msg_pub.point.y = pos_one_sec.at<float>(1);
        msg_pub.point.z = pos_one_sec.at<float>(2);
        
        pub.publish(msg_pub);
      }
    }
  }
  last_time = msg->header.stamp.toSec();
  last_pos = current_pos;
  i++;
}  

void TrajPredictor::solveLS() { cv::solve(A, B, X, cv::DECOMP_SVD); }
