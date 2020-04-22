
#include "ekf_node.hpp"

 // external kaiman filter
EKFNode::EKFNode( ros::NodeHandle& nh, ros::NodeHandle& nhp, double r ) : 
  nh( nh ),
  nh_private( nhp ),
  z(3), //sensor measurement (observation) [x,y,z,??time]
  time(1),
  rate(r){

  // advertise estimation
  pub_pose=nh_private.advertise<geometry_msgs::AccelStamped>("posterior",10);

  // subscribe sensor 
  sub_pose=nh.subscribe( "pose", 100, &EKFNode::callback_sensors, this ); // now still hardcoded

}


// Sensor callback
// This only copies the observation
void EKFNode::callback_sensors( const geometry_msgs::PointStamped& sen){

  // get observation from the sensor
  z(1) = sen.point.x;
  z(2) = sen.point.y;
  z(3) = sen.point.z;
  time(1) = double(sen.header.stamp.sec); // TODO, still not figure our hout to use time 

}


void EKFNode::update(){
  if( ekf.is_initialized() ){ 
    ekf.update( ros::Time::now(), z);  // calling ekf.update
    pub_pose.publish( ekf.get_posterior() );
  }
}


int main(int argc, char **argv){
  
  // Initialize ROS
  ros::init(argc, argv, "EKF");
  ros::NodeHandle nh, nhp("~");

  // create external Kalman filter class
  EKFNode ekf_node( nh, nhp, 1.0/25.0 );
  ros::Rate r(25.0);
  
  while(nh.ok()){
    ekf_node.update();
    ros::spinOnce();
    r.sleep();
  }

  return 0;
}