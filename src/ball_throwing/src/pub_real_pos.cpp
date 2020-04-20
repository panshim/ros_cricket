#include "ros/ros.h"
#include "geometry_msgs/PointStamped.h"
#include "geometry_msgs/Pose.h"
#include "gazebo_msgs/GetModelState.h"

class RealPosTransmitter
{
private:
  ros::ServiceClient cli;
  ros::Publisher pub;
  ros::NodeHandle nh;

public:
  RealPosTransmitter(ros::NodeHandle& nh) : nh(nh)
  {
    cli =  nh.serviceClient<gazebo_msgs::GetModelState>("gazebo/get_model_state");
    cli.waitForExistence();
    pub = nh.advertise<geometry_msgs::PointStamped>("ball/real_pos", 10);
  }

  ~RealPosTransmitter(){}

  void Call()
  {
    gazebo_msgs::GetModelState srv;
    srv.request.model_name = "ball";
    if (cli.call(srv))
    {
      geometry_msgs::PointStamped pub_msg;
      pub_msg.header.stamp = ros::Time::now();
      pub_msg.header.frame_id = "world";
      pub_msg.point = srv.response.pose.position;
      pub.publish(pub_msg);
    }
  }

  void timerCallback(const ros::TimerEvent& e)
  {
    RealPosTransmitter::Call();
  }
};


int main(int argc, char **argv)
{
  ros::init(argc, argv, "pub_real_pos");
  ros::NodeHandle nh;

  RealPosTransmitter rpt(nh);
  ros::Timer timer = nh.createTimer(ros::Duration(0.01), &RealPosTransmitter::timerCallback, &rpt);

  ros::spin();
}
