
#include "ekf_node.hpp"

 // external kaiman filter
EKFNode::EKFNode( ros::NodeHandle& nh, ros::NodeHandle& nhp, double r ) : 
  nh( nh ),
  nh_private( nhp ),
  z(6), //sensor measurement (observation) [x,y,z,??time]
  time(time),
  rate(r){

  // advertise estimation
  pub_pose=nh_private.advertise<geometry_msgs::InertiaStamped>("/ball/posterior_estimation",10);
  pub_tar = nh_private.advertise<geometry_msgs::TwistStamped>("/ball/target",10);

  pub_point=nh_private.advertise<geometry_msgs::PointStamped>("/ball/hjw",10);

  // subscribe sensor 
  sub_pose=nh.subscribe( "ball/tracked_pos", 100, &EKFNode::callback_sensors, this ); // now still hardcoded

}


// Sensor callback
// This only copies the observation
void EKFNode::callback_sensors( const geometry_msgs::PointStamped& sen){

  // get observation from the sensor
  // std::cout<<double(sen.header.stamp.toSec())<<std::endl;
  if(z(1)!=0){
    z(4) = (sen.point.x-z(1))/(double(sen.header.stamp.toSec())-time.toSec());
    z(5) = (sen.point.y-z(2))/(double(sen.header.stamp.toSec())-time.toSec());
    z(6) = (sen.point.z-z(3))/(double(sen.header.stamp.toSec())-time.toSec());
    z(1) = sen.point.x;
    z(2) = sen.point.y;
    z(3) = sen.point.z;
    time = sen.header.stamp;
  }
  else{
    z(1) = sen.point.x;
    z(2) = sen.point.y;
    z(3) = sen.point.z;
    z(4) = 0;
    z(5) = 0;
    z(6) = 0;
    time = sen.header.stamp; // TODO, still not figure our hout to use time 
  }

  /*
  geometry_msgs::InertiaStamped EST;

  double i = 0.4;

  //EST.header.stamp = (floor(time),(time-floor(time))*pow(10,9));
  EST.header.stamp = time + ros::Duration(i); // TODO : how to match the time?
  EST.header.frame_id = "world";

  EST.inertia.com.x = std::min(10.0,z(1)+i*z(4)); // x position
  EST.inertia.com.y = std::min(10.0,z(2)+i*z(5)); // y position
  EST.inertia.com.z = std::min(10.0,std::max(z(3)+i*z(6)-4.9*i*i,0.0)); // z position
  EST.inertia.ixx = z(4); // x velocity
  EST.inertia.ixy = z(5); // y velocity
  EST.inertia.ixz = z(6)-9.8*i; // z velocity


  geometry_msgs::PointStamped point_est;
  point_est.header.stamp = time + ros::Duration(i); // TODO : how to match the time?
  point_est.header.frame_id = "world";

  point_est.point.x = std::min(10.0,z(1)+i*z(4)); // x position
  point_est.point.y = std::min(10.0,z(2)+i*z(5)); // y position
  point_est.point.z = std::min(10.0,std::max(z(3)+i*z(6)-4.9*i*i,0.0)); // z position

  pub_pose.publish( EST );
  pub_point.publish( point_est );
  */


}


void EKFNode::update(){

  if(!ekf.is_initialized())
  {
    ekf.initialize();
  }


  if( ekf.is_initialized() ){ 
    ekf.update( ros::Time::now(), z);  // calling ekf.update

    geometry_msgs::InertiaStamped EST = ekf.get_posterior();

    double i = 1;

    //EST.header.stamp = (floor(time),(time-floor(time))*pow(10,9));
    EST.header.stamp = time + ros::Duration(i); // TODO : how to match the time?
    EST.header.frame_id = "world";

    EST.inertia.com.x = EST.inertia.com.x+i*EST.inertia.ixx; // x position
    EST.inertia.com.y = EST.inertia.com.y+i*EST.inertia.ixy; // y position
    EST.inertia.com.z = std::max(0.0,EST.inertia.com.z+i*EST.inertia.ixz-0.5*i*i*9.8); // z position
    EST.inertia.ixx = EST.inertia.ixx; // x velocity
    EST.inertia.ixy = EST.inertia.ixy; // y velocity
    EST.inertia.ixz = EST.inertia.ixz+(-9.8)*i; // z velocity

    geometry_msgs::PointStamped point_est;
    geometry_msgs::TwistStamped point_tar;

    point_est.header.stamp = time + ros::Duration(i); // TODO : how to match the time?
    point_est.header.frame_id = "world";

    point_est.point.x = EST.inertia.com.x; // x position
    point_est.point.y = EST.inertia.com.y; // y position
    point_est.point.z = EST.inertia.com.z; // z position

    point_tar.header.stamp = time + ros::Duration(i); // TODO : how to match the time?
    point_tar.header.frame_id = "world";

    point_tar.twist.linear.x = EST.inertia.com.x; // x position
    point_tar.twist.linear.y = EST.inertia.com.y; // y position
    point_tar.twist.linear.z = EST.inertia.com.z; // z position
    point_tar.twist.angular.x = EST.inertia.ixx;
    point_tar.twist.angular.y = EST.inertia.ixy;
    point_tar.twist.angular.z = EST.inertia.ixz;

    pub_tar.publish( point_tar );
    pub_point.publish( point_est );
  }
}


int main(int argc, char **argv){
  
  // Initialize ROS
  ros::init(argc, argv, "EKF");
  ros::NodeHandle nh, nhp("~");

  // create external Kalman filter class
  EKFNode ekf_node( nh, nhp, 1.0/50.0 );
  ros::Rate r(50.0);
  
  while(nh.ok()){
    ekf_node.update();
    ros::spinOnce();
    r.sleep();
  }

  return 0;
}
