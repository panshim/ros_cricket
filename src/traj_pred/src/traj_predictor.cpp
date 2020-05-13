#include "traj_pred/traj_predictor.hpp"

TrajPredictor::TrajPredictor(ros::NodeHandle& nh, float sec, std::string topic_sub, std::string topic_pub_pos, std::string topic_pub_tgt) : nh_(nh), sec_(sec), topic_sub_(topic_sub), topic_pub_pos_(topic_pub_pos), topic_pub_tgt_(topic_pub_tgt)
{
  sub = nh_.subscribe(topic_sub_, 10, &TrajPredictor::calCallback, this);
  pub_pos = nh.advertise<geometry_msgs::PointStamped>(topic_pub_pos_, 10);
  pub_tgt = nh.advertise<geometry_msgs::TwistStamped>(topic_pub_tgt_, 10);

  A = cv::Mat::zeros(1, 3, CV_32F);
  X = cv::Mat::zeros(3, 3, CV_32F);
  B = cv::Mat::zeros(1, 3, CV_32F);

  i = 0;
  start_time = 0;
  finish_time = 9.5;
  rate_time = 0.0;
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
        finish_time = msg->header.stamp.toSec() + 9.5;
        float dt = msg->header.stamp.toSec() - start_time;
        cv::Mat new_A_row = (cv::Mat_<float>(1, 3) << dt * dt, dt, 1);
        cv::Mat new_B_row = (cv::Mat_<float>(1, 3) << current_pos.x, current_pos.y, current_pos.z);
        A.at<float>(0, 0) = 0;
        A.at<float>(0, 1) = 0;
        A.at<float>(0, 2) = 1;
        A.push_back(new_A_row);
        B.at<float>(0, 0) = last_pos.x;
        B.at<float>(0, 1) = last_pos.y;
        B.at<float>(0, 2) = last_pos.z;
        B.push_back(new_B_row);
      }
      // send a false target to tell robot get ready
      geometry_msgs::TwistStamped msg_tgt;
      msg_tgt.header.stamp = msg->header.stamp;
      msg_tgt.header.frame_id = "world";
      msg_tgt.twist.linear.z = -100;
      pub_tgt.publish(msg_tgt);
    }
    else
    {
      if (current_pos.z < 0.5) // ball on the ground, reset
      {
        trigger = false;
        start_time = 0;
        last_time = msg->header.stamp.toSec();
        rate_time = msg->header.stamp.toSec();
        finish_time = last_time +3.3;

        last_pos = current_pos;
        A = cv::Mat(1, 3, CV_32F);
        B = cv::Mat(1, 3, CV_32F);
        return;
      }
      else if (current_pos.z < 0.9) {
        finish_time = msg->header.stamp.toSec() +9.5;
      }
      float dt = msg->header.stamp.toSec() - start_time;
      sec_ = (finish_time - msg->header.stamp.toSec()-0.8*(msg->header.stamp.toSec()-rate_time));
      sec_ = (3.3-2.2*dt);
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
        float az = X.at<float>(0, 2);
        float bz = X.at<float>(1, 2);
        float cz = X.at<float>(2, 2);

        cv::Mat dt_in_sec = (cv::Mat_<float>(1, 3) << (dt + sec_) * (dt + sec_), dt + sec_, 1); // sec_ seconds later
        cv::Mat pos_in_sec = dt_in_sec * X; 
        
        //float z_target = 3 - pos_1_sec.at<float>(2);
        //float t_target = (-bz - sqrt(bz * bz - 4 * az * (cz - z_target))) / (2 * az);
        //cv::Mat dt_target = (cv::Mat_<float>(1, 3) << (t_target * t_target), t_target, 1);
        //cv::Mat pos_one_sec = dt_target * X;
        msg_pub.point.x = pos_in_sec.at<float>(0);
        msg_pub.point.y = pos_in_sec.at<float>(1);
        msg_pub.point.z = pos_in_sec.at<float>(2);

        // use TwistStamped message to send target position and velocity information
        geometry_msgs::TwistStamped msg_tgt;
        msg_tgt.header = msg_pub.header;
        msg_tgt.twist.linear.x = msg_pub.point.x; // position
        msg_tgt.twist.linear.y = msg_pub.point.y;
        msg_tgt.twist.linear.z = msg_pub.point.z;
        msg_tgt.twist.angular.x = 2 * X.at<float>(0, 0) * (dt + sec_) + X.at<float>(1, 0);
        msg_tgt.twist.angular.y = 2 * X.at<float>(0, 1) * (dt + sec_) + X.at<float>(1, 1);
        msg_tgt.twist.angular.z = 2 * X.at<float>(0, 2) * (dt + sec_) + X.at<float>(1, 2);

        //msg_tgt.twist.angular.x = 2 * X.at<float>(0, 0) * (t_target) + X.at<float>(1, 0);
        //msg_tgt.twist.angular.y = 2 * X.at<float>(0, 1) * (t_target) + X.at<float>(1, 1);
        //msg_tgt.twist.angular.z = 2 * X.at<float>(0, 2) * (t_target) + X.at<float>(1, 2);

        // if (t_target - dt <= 0.1)
        // {
        //   msg_pub.point.x = pos_one_sec.at<float>(0) - msg_tgt.twist.angular.x * 0.05;
        //   msg_pub.point.y = pos_one_sec.at<float>(1) - msg_tgt.twist.angular.y * 0.05;
        //   msg_pub.point.z = pos_one_sec.at<float>(2) - msg_tgt.twist.angular.z * 0.05;

        //   msg_tgt.twist.linear.x = pos_one_sec.at<float>(0) - msg_tgt.twist.angular.x * 0.05;
        //   msg_tgt.twist.linear.y = pos_one_sec.at<float>(1) - msg_tgt.twist.angular.y * 0.05;
        //   msg_tgt.twist.linear.z = pos_one_sec.at<float>(2) - msg_tgt.twist.angular.z * 0.05;
        // }
        //if (t_target - dt <= 0.5)
        //{
        if ((msg_tgt.twist.linear.z>1.2)&&(msg_tgt.twist.linear.z<2.7)){
          pub_pos.publish(msg_pub);
          pub_tgt.publish(msg_tgt);

        }
      
      }
    }
  }
  last_time = msg->header.stamp.toSec();
  last_pos = current_pos;
  i++;
}  

void TrajPredictor::solveLS() { cv::solve(A, B, X, cv::DECOMP_SVD); }
