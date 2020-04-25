#include <multi_view_plugin/ball_tracker.hpp>

namespace gazebo
{
  BallTracker::BallTracker(){}

  BallTracker::~BallTracker(){}

  void BallTracker::Load(physics::ModelPtr model, sdf::ElementPtr sdf)
  {
    model_ = model;
    gazebo_ros_ = GazeboRosPtr(new GazeboRos(model, sdf, "BallTracker"));

    ROS_INFO("BallTracker is loading...");
    gazebo_ros_->getParameter<std::string>(camera_name_, "camera_name", "");
    ROS_INFO("BallTracker: camera_name_ is %s", camera_name_.c_str());
    gazebo_ros_->getParameter<std::string>(topic_raw_, "raw_topic", "");
    ROS_INFO("BallTracker: topic_raw_ is %s", topic_raw_.c_str());
    gazebo_ros_->getParameter<std::string>(topic_binary_, "binary_topic", "");
    ROS_INFO("BallTracker: topic_binary_ is %s", topic_binary_.c_str());
    gazebo_ros_->getParameter<std::string>(topic_cm_, "cm_topic", "");
    ROS_INFO("BallTracker: topic_cm_ is %s", topic_cm_.c_str());

    sub_raw = gazebo_ros_->node()->subscribe(topic_raw_, 10, &BallTracker::Track, this);
    pub_binary = gazebo_ros_->node()->advertise<sensor_msgs::Image>(topic_binary_, 10);
    pub_cm = gazebo_ros_->node()->advertise<geometry_msgs::PointStamped>(topic_cm_, 10);
  }

  void BallTracker::Track(const sensor_msgs::ImageConstPtr& raw)
  {
    cv_bridge::CvImagePtr img_ptr;
    try
    {
      img_ptr = cv_bridge::toCvCopy(raw, "rgb8");
    }
    catch (cv_bridge::Exception& e)
    {
      ROS_ERROR("cv_bridge exception: %s", e.what());
      return;
    }

    BallTracker::hsvFilter(img_ptr);
    BallTracker::pubCenter(raw->header.stamp, img_ptr);

    cv::cvtColor(img_ptr->image, img_ptr->image, CV_GRAY2RGB);
    pub_binary.publish(img_ptr->toImageMsg());
  }

  void BallTracker::hsvFilter(const cv_bridge::CvImagePtr& img_ptr)
  {
    cv::cvtColor(img_ptr->image, img_ptr->image, CV_RGB2HSV);
    cv::Scalar hsv_lower(100, 80, 0);
    cv::Scalar hsv_upper(130, 255, 255);
    cv::inRange(img_ptr->image, hsv_lower, hsv_upper, img_ptr->image);
  }

  void BallTracker::pubCenter(const ros::Time t, const cv_bridge::CvImagePtr& img_ptr)
  {
    cv::Moments m = cv::moments(img_ptr->image, true);
    geometry_msgs::PointStamped cm;
    cm.header.stamp = t;
    cm.header.frame_id = "world";
    if (m.m00 == 0) // zero area
    {
      cm.point.x = 0;
      cm.point.y = 0;
      cm.point.z = -1;
    } else {
      cm.point.x = m.m10/m.m00;
      cm.point.y = m.m01/m.m00;
      cm.point.z = 0;
    }
    pub_cm.publish(cm);
  }

  GZ_REGISTER_MODEL_PLUGIN(BallTracker)
}
