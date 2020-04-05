#include "ros/ros.h"
#include <gazebo_msgs/ModelState.h>
#include <geometry_msgs/Twist.h>

#include <sstream>
#include <stdlib.h>

#include <termio.h>
#include <stdio.h>
 
/*
int scanKeyboard()
{
int in;
struct termios new_settings;
struct termios stored_settings;
tcgetattr(0,&stored_settings);
new_settings = stored_settings;
new_settings.c_lflag &= (~ICANON);
new_settings.c_cc[VTIME] = 0;
tcgetattr(0,&stored_settings);
new_settings.c_cc[VMIN] = 1;
tcsetattr(0,TCSANOW,&new_settings);
 
in = getchar();
 
tcsetattr(0,TCSANOW,&stored_settings);
return in;
}


int main(){
while(1){
printf(":%d",scanKeyboard());
}
}
*/


int main(int argc, char **argv){
	ros::init(argc,argv,"ball_throwing");
	ros::NodeHandle nh;

	ros::Publisher twist_pub = nh.advertise<gazebo_msgs::ModelState>("gazebo/set_model_state",10);



	while(ros::ok()){
		// read the keyboard
		int in;
		struct termios new_settings;
		struct termios stored_settings;
		tcgetattr(0,&stored_settings);
		new_settings = stored_settings;
		new_settings.c_lflag &= (~ICANON);
		new_settings.c_cc[VTIME] = 0;
		tcgetattr(0,&stored_settings);
		new_settings.c_cc[VMIN] = 1;
		tcsetattr(0,TCSANOW,&new_settings);
		in = getchar();
		tcsetattr(0,TCSANOW,&stored_settings);
		// throw the ball
		if (in==32){
			std::cout<<"throwing the ball!!"<<std::endl;

			gazebo_msgs::ModelState msg_qd;

			msg_qd.model_name=std::string("BALL");

			msg_qd.twist.linear.x=double(rand())/double(RAND_MAX)*5;
			msg_qd.twist.linear.y=double(rand())/double(RAND_MAX)*5;
			msg_qd.twist.linear.z=8+double(rand())/double(RAND_MAX)*5;

			twist_pub.publish( msg_qd );

			std::cout<<"done"<<std::endl;

		}

		if (in==98){
			std::cout<<"set the ball to origin!!"<<std::endl;

			gazebo_msgs::ModelState msg_qd;

			msg_qd.model_name=std::string("BALL");

			msg_qd.pose.position.x=0;
			msg_qd.pose.position.y=0;
			msg_qd.pose.position.z=0;
			msg_qd.twist.linear.x=0;
			msg_qd.twist.linear.y=0;
			msg_qd.twist.linear.z=0;

			twist_pub.publish( msg_qd );

			std::cout<<"done"<<std::endl;

		}
		ros::spinOnce();
	}

	return 0;
}