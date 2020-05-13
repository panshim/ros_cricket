#include "ros/ros.h"
#include "geometry_msgs/PointStamped.h"
#include "geometry_msgs/TwistStamped.h"
#include "opencv2/opencv.hpp"

class TrajPredictor
{
  private:
    ros::NodeHandle nh_;

    float sec_; // after how many secs

    std::string topic_sub_;
    std::string topic_pub_pos_;
    std::string topic_pub_tgt_; // target (position, velocity)

    ros::Subscriber sub;
    ros::Publisher pub_pos;
    ros::Publisher pub_tgt;

    // least square formulation AX=B
    cv::Mat A; // LHS known
    cv::Mat X; // polynomial coefficients to solve
    cv::Mat B; // RHS

    cv::Point3f last_pos; 
    cv::Point3f current_pos;

    int i; // message index
    float last_time;
    float start_time;
    float finish_time;
    float rate_time;
    bool trigger;

  public:
    TrajPredictor(ros::NodeHandle& nh, float sec, std::string topic_sub, std::string topic_pub_pos, std::string topic_pub_tgt);
    ~TrajPredictor();
    void calCallback(const geometry_msgs::PointStamped::ConstPtr& msg);
    void solveLS();
};
