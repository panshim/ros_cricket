//ROS
#include "ros/ros.h"
#include "ros/package.h"

//msgs
#include <gazebo_msgs/ModelState.h>
#include <gazebo_msgs/SpawnModel.h>
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/Pose.h>

#include <fstream>
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

        if (argc != 4)
        {
          ROS_INFO("usage: (rosrun) ball x[type:int] y[type:int] z[type:int]");
          return 1;
        }
        
        // spawn the ball initially
        std::string pkg_path = ros::package::getPath("ball_throwing");
        std::string sdf_path = pkg_path+"/sdf/ball.sdf";
        std::ifstream ifs(sdf_path.c_str());
        std::stringstream xml_stream;
        xml_stream << ifs.rdbuf();

        gazebo_msgs::SpawnModel spawn_msg;
        geometry_msgs::Pose init_pose;
        init_pose.position.x = atof(argv[1]);
        init_pose.position.y = atof(argv[2]);
        init_pose.position.z = atof(argv[3]);

        spawn_msg.request.model_name = "ball";
        spawn_msg.request.model_xml = xml_stream.str();
        spawn_msg.request.robot_namespace = "ball";
        spawn_msg.request.initial_pose = init_pose;

        ros::ServiceClient spawn = nh.serviceClient<gazebo_msgs::SpawnModel>("/gazebo/spawn_sdf_model");
        spawn.waitForExistence();

        if (spawn.call(spawn_msg))
        {
	  ROS_INFO("Successfully spawn the ball at (%f, %f, %f)", atof(argv[1]), atof(argv[2]), atof(argv[3]));
        } else {
          ROS_ERROR("Failed to spawn the ball!");
        }

        std::cout << "Please press 'Space' key to throw the ball; or press 'b' to reset the ball." << std::endl;       

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
			std::cout<<"Throwing the ball!!"<<std::endl;

			gazebo_msgs::ModelState msg_qd;

			msg_qd.model_name=std::string("ball");

                        msg_qd.pose = init_pose;

			msg_qd.twist.linear.x=double(rand())/double(RAND_MAX)*5;
			msg_qd.twist.linear.y=double(rand())/double(RAND_MAX)*5;
			msg_qd.twist.linear.z=8+double(rand())/double(RAND_MAX)*5;

			twist_pub.publish( msg_qd );

			std::cout<<"Throw done."<<std::endl;

		}

		if (in==98){
			std::cout<<"Reset the ball."<<std::endl;

			gazebo_msgs::ModelState msg_qd;

			msg_qd.model_name=std::string("ball");

			msg_qd.pose = init_pose;
			msg_qd.twist.linear.x=0;
			msg_qd.twist.linear.y=0;
			msg_qd.twist.linear.z=0;

			twist_pub.publish( msg_qd );

			std::cout<<"Reset done."<<std::endl;

		}
		ros::spinOnce();
	}

	return 0;
}
