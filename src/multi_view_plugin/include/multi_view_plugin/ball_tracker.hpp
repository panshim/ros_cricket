// Gazebo
#include "gazebo/common/common.hh"
#include "gazebo/physics/physics.hh"
#include "gazebo/math/gzmath.hh"
#include "gazebo_plugins/gazebo_ros_utils.h"

// ROS
#include <ros/ros.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/Image.h>
#include <geometry_msgs/Point.h>

// OpenCV
#include <opencv2/opencv.hpp>


namespace gazebo
{
  class BallTracker : public ModelPlugin
  {
  private:
    GazeboRosPtr gazebo_ros_;
    physics::ModelPtr model_;

    std::string camera_name_;
    std::string topic_raw_;
    std::string topic_binary_;
    std::string topic_cm_;

    cv::Mat P = cv::Mat(3, 4, CV_64FC1); // projection matrix

    ros::Subscriber sub_raw;
    ros::Publisher pub_binary;
    ros::Publisher pub_cm; // 2D center of mass publisher

  public:
    BallTracker();
    ~BallTracker();

    void Load(physics::ModelPtr model, sdf::ElementPtr sdf);
    void Track(const sensor_msgs::ImageConstPtr& raw);
    void setProjectionMatrix();
    cv::Mat getProjectionMatrix();
    void hsvFilter(const cv_bridge::CvImagePtr& img_ptr);
    void pubCenter(const cv_bridge::CvImagePtr& img_ptr);
  };
}
