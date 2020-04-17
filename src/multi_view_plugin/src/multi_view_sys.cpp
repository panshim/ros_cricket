#include "multi_view_plugin/multi_view_sys.hpp"
#include "kdl_parser/kdl_parser.hpp"


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
      cv::triangulatePoints(proj_mats[0], proj_mats[2], pts_2D[0], pts_2D[2], pt_4D);
      cv::Mat pt_3D = cv::Mat(3, 1, CV_32F);
      pt_3D.at<float>(0, 0) = pt_4D.at<float>(0, 0) / pt_4D.at<float>(3, 0);
      pt_3D.at<float>(1, 0) = pt_4D.at<float>(1, 0) / pt_4D.at<float>(3, 0);
      pt_3D.at<float>(2, 0) = pt_4D.at<float>(2, 0) / pt_4D.at<float>(3, 0);
      pts_3D.push_back(pt_3D);
    }
    geometry_msgs::PointStamped msg_track;
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


