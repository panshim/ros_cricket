// Gazebo
#include "gazebo/common/common.hh"
#include "gazebo/physics/physics.hh"
#include "gazebo/math/gzmath.hh"
#include "gazebo_plugins/gazebo_ros_utils.h"

// ROS
#include "ros/ros.h"
#include "geometry_msgs/PolygonStamped.h"

// Boost
#include "boost/bind.hpp"


namespace gazebo
{
  class MultiViewSys : public ModelPlugin
  {
    private:
      GazeboRosPtr gazebo_ros_;
      physics::ModelPtr model_;
      ros::Subscriber imgs_sub;
      ros::Publisher track_pub;
      
      int num_camera = 4;
      std::vector<Camera> camera;

    public:
      MultiViewSys(std::string cameraA_name, std::string cameraB_name, std::string cameraC_name, std::string cameraD_name);
      ~MultiViewSys();
      void Load(physics::ModelPtr model, sdf::ElementPtr sdf);
      void Update();
  };
}

    


