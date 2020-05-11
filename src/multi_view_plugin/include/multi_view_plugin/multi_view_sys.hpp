// ROS
#include "ros/ros.h"
#include "gazebo_msgs/GetModelState.h"
#include "geometry_msgs/PointStamped.h"
#include "sensor_msgs/CameraInfo.h"
#include "message_filters/subscriber.h"
#include "message_filters/time_synchronizer.h"

// OpenCV
#include <opencv2/opencv.hpp>
#include <opencv2/calib3d.hpp>

// KDL
#include "kdl_parser/kdl_parser.hpp"

// Boost
#include "boost/bind.hpp"


class MultiViewSys
{
  private:
    const int num_camera = 4;
    std::vector<std::string> camera_names;
    std::vector<cv::Mat> proj_mats; // projection matrices

    ros::NodeHandle nh;
      
    // subscribers
    message_filters::Subscriber<geometry_msgs::PointStamped> sub0;
    message_filters::Subscriber<geometry_msgs::PointStamped> sub1;
    message_filters::Subscriber<geometry_msgs::PointStamped> sub2;
    message_filters::Subscriber<geometry_msgs::PointStamped> sub3; 
   
    std::string topic_track_;
    ros::Publisher pub_track;
    geometry_msgs::PointStamped msg_track;

    message_filters::TimeSynchronizer<geometry_msgs::PointStamped, geometry_msgs::PointStamped, geometry_msgs::PointStamped, geometry_msgs::PointStamped> sync; // message synchronizer
      
    // kalman filter related
    bool kf_triggered = false;

    float last_stamp;
    float current_stamp;

    KDL::Vector last_pos;
    KDL::Vector track_pos;

    int state_size = 6; // x, y, z, v_x, v_y, v_z
    int msr_size = 3; // x, y, z (tracked)
    int ctl_size = 1; // gravity
    cv::Mat kf_ctl = (cv::Mat_<float>(1, 1) << -9.8);
    cv::Mat X;
    cv::Mat Y;
    cv::Mat Z;
    cv::Mat T;
    cv::Mat A;

    int N;
    float dur_time;

    cv::KalmanFilter kf;

    std::string topic_kf_;
    ros::Publisher pub_kf;
    std::string topic_prediction_pos_vel_;
    std::string topic_prediction_pos_;
    ros::Publisher pub_prediction_pos_vel;
    ros::Publisher pub_prediction_pos;

    geometry_msgs::PointStamped msg_kf;
    geometry_msgs::AccelStamped est_kf_pos_vel;
    geometry_msgs::PointStamped est_kf_pos;

    float pt = 0.2;


    
  public:
    MultiViewSys(ros::NodeHandle& nh);
    ~MultiViewSys();

    void triangulationCallback(const geometry_msgs::PointStamped::ConstPtr& msg0,
			       const geometry_msgs::PointStamped::ConstPtr& msg1,
			       const geometry_msgs::PointStamped::ConstPtr& msg2,
			       const geometry_msgs::PointStamped::ConstPtr& msg3);
    void getProjectionMatrix(cv::Mat& proj, const std::string& camera_name);
    void lsPrediction(const float dt, float dur_time, const geometry_msgs::PointStamped& msg_kf, 
                    const float pt, int N);
    void lsPredResult(const float dur_time, const float val, const float pt, const int flag, const int N);

};



