#include <camera_setting/camera.hpp>

camera::camera( std::string camera_name ){
    this->camera_name = camera_name;
}

camera::~camera(){}

std::string camera::get_name(){
    return this->camera_name;
}

void camera::calibrate(){
    
}
