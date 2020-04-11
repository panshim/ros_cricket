#include "multi_view_plugin/multi_view_sys.hpp"

namespace gazebo
{
  MultiViewSys::MultiViewSys(std::string camera0_name, std::string camera1_name, std::string camera2_name, std::string camera3_name) {
  camera[0] = new Camera(camera0_name);
  camera[1] = new Camera(camera1_name);
  camera[2] = new Camera(camera2_name);
  camera[3] = new Camera(camera3_name);

  for (int i; i < num_camera; i++)
    camera[i].calibrate();
  }
