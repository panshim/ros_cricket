#include "multi_view_plugin/multi_view_sys.hpp"


MultiViewSys::MultiViewSys(ros::NodeHandle& nh) : nh (nh), sync (sub0, sub1, sub2, sub3, 10) 
{
  ROS_INFO("MultiViewSys is initializing...");
  camera_names.push_back("camera_A");
  camera_names.push_back("camera_B");
  camera_names.push_back("camera_C");
  camera_names.push_back("camera_D");

  for (int i = 0; i < num_camera; i++)
  {
    ROS_INFO("MultiViewSys: camera_names[%d] is %s", i, camera_names[i].c_str());
   
    cv::Mat proj = cv::Mat(3, 4, CV_32FC1);
    MultiViewSys::getProjectionMatrix(proj, camera_names[i]);
    proj_mats.push_back(proj);
  }

  sub0.subscribe(nh, (camera_names[0]+"/2D_tracking").c_str(), 1);
  sub1.subscribe(nh, (camera_names[1]+"/2D_tracking").c_str(), 1);
  sub2.subscribe(nh, (camera_names[2]+"/2D_tracking").c_str(), 1);
  sub3.subscribe(nh, (camera_names[3]+"/2D_tracking").c_str(), 1);

  sync.registerCallback(boost::bind(&MultiViewSys::triangulationCallback, this, _1, _2, _3, _4));
    
  topic_track_ = "ball/tracked_pos";
  ROS_INFO("MultiViewSys: topic_track_ is %s", topic_track_.c_str());
  pub_track = nh.advertise<geometry_msgs::PointStamped>(topic_track_, 10);

  // configure kalman filter smoothing
  kf = cv::KalmanFilter(state_size, msr_size, ctl_size, CV_32F);

  last_stamp = 0;
  current_stamp = 0;

  N = 0;
  dur_time = 0.0;

  topic_kf_ = "ball/tracked_pos_kf";
  ROS_INFO("MultiViewSys: topic_kf_ is %s", topic_kf_.c_str());
  topic_prediction_pos_vel_ = "ball/predicted_pos_vel";
  ROS_INFO("MultiViewSys: topic_prediction_pos_vel_ is %s", topic_prediction_pos_vel_.c_str());
  topic_prediction_pos_ = "ball/predicted_pos";
  ROS_INFO("MultiViewSys: topic_prediction_pos_ is %s", topic_prediction_pos_.c_str());

  pub_kf = nh.advertise<geometry_msgs::PointStamped>(topic_kf_, 10);
  pub_prediction_pos_vel = nh.advertise<geometry_msgs::AccelStamped>(topic_prediction_pos_vel_, 10);
  pub_prediction_pos = nh.advertise<geometry_msgs::PointStamped>(topic_prediction_pos_, 10);//only for visualizaiton in rviz

  cv::setIdentity(kf.transitionMatrix);
  kf.controlMatrix = cv::Mat::zeros(state_size, ctl_size, CV_32F);
  cv::setIdentity(kf.processNoiseCov, cv::Scalar(0.005));
  kf.processNoiseCov.at<float>(3, 3) = 0.2;
  kf.processNoiseCov.at<float>(4, 4) = 0.2;
  kf.processNoiseCov.at<float>(5, 5) = 0.2;

  kf.measurementMatrix = cv::Mat::zeros(msr_size, state_size, CV_32F);
  kf.measurementMatrix.at<float>(0, 0) = 1.0;
  kf.measurementMatrix.at<float>(1, 1) = 1.0;
  kf.measurementMatrix.at<float>(2, 2) = 1.0;
  cv::setIdentity(kf.measurementNoiseCov, cv::Scalar(0.005));
  cv::setIdentity(kf.errorCovPre, cv::Scalar(0.1));
}
  
MultiViewSys::~MultiViewSys(){}

void MultiViewSys::triangulationCallback(const geometry_msgs::PointStamped::ConstPtr& msg0,
				  	 const geometry_msgs::PointStamped::ConstPtr& msg1,
				 	 const geometry_msgs::PointStamped::ConstPtr& msg2,
				 	 const geometry_msgs::PointStamped::ConstPtr& msg3)
{
  std::vector<int> valid;
  std::vector<cv::Mat> pts_2D;
  if (msg0->point.z == 0) { valid.push_back(0); }
  pts_2D.push_back((cv::Mat_<float>(2, 1) << msg0->point.x, msg0->point.y));
  if (msg1->point.z == 0) { valid.push_back(1); }
  pts_2D.push_back((cv::Mat_<float>(2, 1) << msg1->point.x, msg1->point.y));
  if (msg2->point.z == 0) { valid.push_back(2); }
  pts_2D.push_back((cv::Mat_<float>(2, 1) << msg2->point.x, msg2->point.y));
  if (msg3->point.z == 0) { valid.push_back(3); }
  pts_2D.push_back((cv::Mat_<float>(2, 1) << msg3->point.x, msg3->point.y));

  int n_valid = valid.size();
  if (n_valid < 2) { return; }
  else {
    std::vector<cv::Mat> pts_3D;
    for (int i = 0; i < n_valid; i++)
    {
      cv::Mat pt_4D = cv::Mat(4, 1, CV_32F); // homogeneous 3D coordinate
      cv::triangulatePoints(proj_mats[valid[i]], proj_mats[valid[(i+1) % n_valid]], pts_2D[valid[i]], pts_2D[valid[(i+1) % n_valid]], pt_4D);
      cv::Mat pt_3D = cv::Mat(3, 1, CV_32F);
      pt_3D.at<float>(0, 0) = pt_4D.at<float>(0, 0) / pt_4D.at<float>(3, 0);
      pt_3D.at<float>(1, 0) = pt_4D.at<float>(1, 0) / pt_4D.at<float>(3, 0);
      pt_3D.at<float>(2, 0) = pt_4D.at<float>(2, 0) / pt_4D.at<float>(3, 0);
      pts_3D.push_back(pt_3D);
    }
    msg_track.header.stamp = msg3->header.stamp; // need to modify to reflect the latest timestamp
    msg_track.header.frame_id = "world";

    float x_sum = 0;
    float y_sum = 0;
    float z_sum = 0;
    for (int i = 0; i < n_valid; i++)
    {
      x_sum += pts_3D[i].at<float>(0, 0);
      y_sum += pts_3D[i].at<float>(1, 0);
      z_sum += pts_3D[i].at<float>(2, 0);
    }
    msg_track.point.x = x_sum / n_valid;
    msg_track.point.y = y_sum / n_valid;
    msg_track.point.z = z_sum / n_valid;
    pub_track.publish(msg_track);

    // kalman filter smoothing
    current_stamp = msg_track.header.stamp.toSec();
    track_pos = KDL::Vector(msg_track.point.x, msg_track.point.y, msg_track.point.z);
    if (last_stamp == 0) // node starts
    {
      last_stamp = current_stamp;
      last_pos = track_pos;
      kf_triggered = false;
    }
    else
    {
      KDL::Vector dp = track_pos - last_pos;
      if (track_pos[2] < 0.1) // ball on the ground, stop smoothing
      {
        last_stamp = current_stamp;
        last_pos = track_pos;
        kf_triggered = false;
      }
      else if ((track_pos[2] >= 0.1) && (dp.Norm() < 1)) // smoothing
      {
        float dt = current_stamp - last_stamp;
        if (!kf_triggered) // kalman filter triggered, initialize
        {
          kf.statePre.at<float>(0) = last_pos[0];
          kf.statePre.at<float>(1) = last_pos[1];
          kf.statePre.at<float>(2) = last_pos[2];
          kf.statePre.at<float>(3) = dp[0] / dt;
          kf.statePre.at<float>(4) = dp[1] / dt;
          kf.statePre.at<float>(5) = dp[2] / dt;

          kf_triggered = true;
        }
        cv::Mat msr_pos = (cv::Mat_<float>(msr_size, 1) << track_pos[0], track_pos[1], track_pos[2]);
        cv::Mat estimate = MultiViewSys::kfSmooth(dt, msr_pos);

        msg_kf.header.stamp = msg3->header.stamp;
        msg_kf.header.frame_id = "world";
        msg_kf.point.x = estimate.at<float>(0);
        msg_kf.point.y = estimate.at<float>(1);
        msg_kf.point.z = estimate.at<float>(2);
        
        pub_kf.publish(msg_kf);


        if (msg_kf.point.z>0.5)
        {
        	MultiViewSys::lsPrediction(dt, dur_time, msg_kf, pt, N);

        	N += 1;
        	dur_time = dur_time + dt;
        }

        last_stamp = current_stamp;
        last_pos = track_pos;
      }
      else // reset
      {
        last_stamp = 0;
        kf_triggered = false;
      }
    }
  }
}
      
void MultiViewSys::getProjectionMatrix(cv::Mat& proj, const std::string& camera_name)
{
  boost::shared_ptr<sensor_msgs::CameraInfo const> cam_ptr;
  sensor_msgs::CameraInfo cam_info;
  cam_ptr = ros::topic::waitForMessage<sensor_msgs::CameraInfo>(camera_name + "/camera_info");

  if (cam_ptr == NULL) { ROS_INFO("No Camera Info message received!"); }
  else
  {
    cam_info = *cam_ptr;
    cv::Mat K = cv::Mat(3, 3, CV_32FC1); // intrinsic matrix
    for (int i = 0; i < 9; i++)
    {
      K.at<float>(i/3, i%3) = cam_info.K[i];
    }

    cv::Mat R; // rotation matrix

    ros::ServiceClient cli =  nh.serviceClient<gazebo_msgs::GetModelState>("gazebo/get_model_state");
    cli.waitForExistence();
    gazebo_msgs::GetModelState srv;
    srv.request.model_name = camera_name;
    if (cli.call(srv))
    {
      KDL::Rotation kdl_rot = KDL::Rotation::Quaternion(srv.response.pose.orientation.x, srv.response.pose.orientation.y, srv.response.pose.orientation.z, srv.response.pose.orientation.w);
      cv::Mat R_inv = cv::Mat(3, 3, CV_32FC1);
      for (int i = 0; i < 3; i++)
      {
        for (int j = 0; j < 3; j++)
        {
          R_inv.at<float>(i, j) = kdl_rot(i, j);
        }
      }
      R = R_inv.t();

      cv::Mat Cam_coord(3, 1, CV_32FC1);
      Cam_coord.at<float>(0, 0) = srv.response.pose.position.x;
      Cam_coord.at<float>(1, 0) = srv.response.pose.position.y;
      Cam_coord.at<float>(2, 0) = srv.response.pose.position.z;
      cv::Mat T = - R * Cam_coord; // translation

      std::vector<cv::Mat> mats = {R, T};
      cv::Mat RT;
      cv::hconcat(mats, RT);
      // compensate for difference of frame definition
      cv::Mat const_rot = (cv::Mat_<float>(3, 3) << 0, -1, 0, 0, 0, -1, 1, 0, 0);
    
      proj = K * const_rot * RT;
    }
  }
}
    
void MultiViewSys::lsPrediction(const float dt, float dur_time, const geometry_msgs::PointStamped& msg_kf, 
								const float pt, int N)
{
	// using at least 5 points to estimate the trajectory 
	if (N == 0) //initialization
	{
		X = cv::Mat::zeros(3, 1, CV_32FC1);
		Y = cv::Mat::zeros(3, 1, CV_32FC1);
		Z = cv::Mat::zeros(3, 1, CV_32FC1);
		T = cv::Mat::zeros(3, 3, CV_32FC1);

		lsPredResult(dur_time, msg_kf.point.x, pt, 1, N);
		lsPredResult(dur_time, msg_kf.point.y, pt, 2, N);
		lsPredResult(dur_time, msg_kf.point.z, pt, 3, N);
	}
	else if (N<5)
	{

		lsPredResult(dur_time, msg_kf.point.x, pt, 1, N);
		lsPredResult(dur_time, msg_kf.point.y, pt, 2, N);
		lsPredResult(dur_time, msg_kf.point.z, pt, 3, N);
	}
	else
	{	

		lsPredResult(dur_time, msg_kf.point.x, pt, 1, N);
		lsPredResult(dur_time, msg_kf.point.y, pt, 2, N);
		lsPredResult(dur_time, msg_kf.point.z, pt, 3, N);

		est_kf_pos_vel.header.stamp = msg_kf.header.stamp + ros::Duration(pt);
		est_kf_pos.header.stamp = est_kf_pos_vel.header.stamp;

		est_kf_pos_vel.header.frame_id = "world";
		est_kf_pos.header.frame_id = "world";

		pub_prediction_pos_vel.publish(est_kf_pos_vel);
		pub_prediction_pos.publish(est_kf_pos);
	}
}

void MultiViewSys::lsPredResult(const float dur_time, const float val, const float pt, const int flag, const int N)
{
	//float pos_tmp;
	//float vel_tmp;

	T.at<float>(0,0) = N+1.0;
	T.at<float>(0,1) += dur_time;
	T.at<float>(1,0) = T.at<float>(0,1);
	T.at<float>(0,2) += std::pow(dur_time,2);
	T.at<float>(1,1) = T.at<float>(0,2);
	T.at<float>(2,0) = T.at<float>(0,2);
	T.at<float>(1,2) += std::pow(dur_time,3);
	T.at<float>(2,1) = T.at<float>(1,2);
	T.at<float>(2,2) += std::pow(dur_time,4);

	if(flag==1) //X Matrix
	{
		for (int i=0;i<3;i++)
		{
			X.at<float>(i,0) = X.at<float>(i,0) + val*std::pow(dur_time,i);
		}
	}
	else if(flag==2)//Y Matirx
	{
		for (int i=0;i<3;i++)
		{
			Y.at<float>(i,0) = Y.at<float>(i,0) + val*std::pow(dur_time,i);
		}
	}
	else//Z Matrix
	{
		for (int i=0;i<3;i++)
		{
			Z.at<float>(i,0) = Z.at<float>(i,0) + val*std::pow(dur_time,i);
		}
	}

	if (N>=5) // run LS
	{

		if (flag==1)
		{
			A = cv::Mat::zeros(3,1,CV_32FC1);
			cv::solve(T,X,A,cv::DECOMP_LU);
			est_kf_pos_vel.accel.linear.x = A.at<float>(0,0)+A.at<float>(1,0)*(dur_time+pt)+A.at<float>(2,0)*(dur_time+pt)*(dur_time+pt);
			est_kf_pos_vel.accel.angular.x = A.at<float>(1,0)+A.at<float>(2,0)*(dur_time+pt);
			est_kf_pos.point.x = est_kf_pos_vel.accel.linear.x;
		}
		else if (flag==2)
		{
			A = cv::Mat::zeros(3,1,CV_32FC1);
			cv::solve(T,Y,A,cv::DECOMP_LU);
			est_kf_pos_vel.accel.linear.y = A.at<float>(0,0)+A.at<float>(1,0)*(dur_time+pt)+A.at<float>(2,0)*(dur_time+pt)*(dur_time+pt);
			est_kf_pos_vel.accel.angular.y = A.at<float>(1,0)+A.at<float>(2,0)*(dur_time+pt);
			est_kf_pos.point.y = est_kf_pos_vel.accel.linear.y;
		}
		else
		{
			A = cv::Mat::zeros(3,1,CV_32FC1);
			cv::solve(T,Z,A,cv::DECOMP_LU);
			est_kf_pos_vel.accel.linear.z = std::max(float(0.0),A.at<float>(0,0)+A.at<float>(1,0)*(dur_time+pt)+A.at<float>(2,0)*(dur_time+pt)*(dur_time+pt));
			est_kf_pos_vel.accel.angular.z = A.at<float>(1,0)+A.at<float>(2,0)*(dur_time+pt);
			est_kf_pos.point.z = est_kf_pos_vel.accel.linear.z;
		}
	}
}
