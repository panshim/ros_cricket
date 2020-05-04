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



void vel_gen(const geometry_msgs::Pose& init_pose, const geometry_msgs::Pose& target_pose, 
					double* vel_xyz, double radius, double duration);


int main(int argc, char **argv){
	ros::init(argc,argv,"ball_throwing");
	ros::NodeHandle nh;

	ros::Publisher twist_pub = nh.advertise<gazebo_msgs::ModelState>("gazebo/set_model_state",10);

        if (argc != 9)
        {
          ROS_INFO("usage: (rosrun) ball x[type:int] y[type:int] z[type:int]");
          return 1;
        }

		ROS_INFO("------------------------------- (%f)", atof(argv[4]));
        
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

		// set target region parameters
		geometry_msgs::Pose target_pose;
        target_pose.position.x = atof(argv[4]);
        target_pose.position.y = atof(argv[5]);
        target_pose.position.z = atof(argv[6]);

		// radius of target region
		double RADIUS = atof(argv[7]);
		// duration of ball flying in sky
		double DURATION = atof(argv[8]);

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

			msg_qd.model_name = std::string("ball");

            msg_qd.pose = init_pose;

			double vel_xyz[3];

			vel_gen(init_pose, target_pose, vel_xyz, RADIUS, DURATION);

			ROS_INFO("velocity (%f, %f, %f)",vel_xyz[0], vel_xyz[1], vel_xyz[2]);

			msg_qd.twist.linear.x = vel_xyz[0];
			msg_qd.twist.linear.y = vel_xyz[1];
			msg_qd.twist.linear.z = vel_xyz[2];

			twist_pub.publish( msg_qd );

			std::cout<<"Throw done."<<std::endl;

		}

		if (in==98){
			std::cout<<"Reset the ball."<<std::endl;

			gazebo_msgs::ModelState msg_qd;

			msg_qd.model_name=std::string("ball");

			msg_qd.pose = init_pose;
			msg_qd.twist.linear.x = 0;
			msg_qd.twist.linear.y = 0;
			msg_qd.twist.linear.z = 0;

			twist_pub.publish( msg_qd );

			std::cout<<"Reset done."<<std::endl;

		}
		ros::spinOnce();
	}

	return 0;
}


void vel_gen(const geometry_msgs::Pose& init_pose, const geometry_msgs::Pose& target_pose, 
					double* vel_xyz, double radius, double duration){

	double r = double(rand()) / double(RAND_MAX) * radius;
	double alpha = double(rand()) / double(RAND_MAX) * 2.0 * M_PI;
	double gamma = double(rand()) / double(RAND_MAX) * 0.5 * M_PI;

	double target_x = target_pose.position.x + r * cos(gamma) * cos(alpha);
	double target_y = target_pose.position.y + r * cos(gamma) * sin(alpha);
	double target_z = target_pose.position.z + r * sin(gamma);

	vel_xyz[0] = (target_x - init_pose.position.x) / duration;
	vel_xyz[1] = (target_y - init_pose.position.y) / duration;
	vel_xyz[2] = (target_z - init_pose.position.z) / duration + 0.5 * duration * 9.801;

}