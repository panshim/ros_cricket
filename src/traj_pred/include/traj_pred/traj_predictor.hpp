#include "ros/ros.h"
#include "geometry_msgs/PointStamped.h"
#include "opencv2/opencv.hpp"

class TrajPredictor
{
  private:
    ros::NodeHandle nh_;

    std::string topic_sub_;
    std::string topic_pub_;

    ros::Subscriber sub;
    ros::Publisher pub;

    // least square formulation AX=B
    cv::Mat A; // LHS known
    cv::Mat X; // polynomial coefficients to solve
    cv::Mat B; // RHS

    cv::Point3f last_pos; 
    cv::Point3f current_pos;

    int i; // message index
    float last_time;
    float start_time;
    bool trigger;

  public:
    TrajPredictor(ros::NodeHandle& nh, std::string topic_sub, std::string topic_pub);
    ~TrajPredictor();
    void calCallback(const geometry_msgs::PointStamped::ConstPtr& msg);
    void solveLS();
};
