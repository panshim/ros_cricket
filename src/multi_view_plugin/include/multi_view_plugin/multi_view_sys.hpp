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

    message_filters::TimeSynchronizer<geometry_msgs::PointStamped, geometry_msgs::PointStamped, geometry_msgs::PointStamped, geometry_msgs::PointStamped> sync; // message synchronizer
      
  public:
    MultiViewSys(ros::NodeHandle& nh);
    ~MultiViewSys();

    void triangulationCallback(const geometry_msgs::PointStamped::ConstPtr& msg0,
			       const geometry_msgs::PointStamped::ConstPtr& msg1,
			       const geometry_msgs::PointStamped::ConstPtr& msg2,
			       const geometry_msgs::PointStamped::ConstPtr& msg3);
    void getProjectionMatrix(cv::Mat& proj, const std::string& camera_name);
};



