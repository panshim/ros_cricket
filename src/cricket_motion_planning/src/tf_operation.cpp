#include "tf_operation.hpp"

TFOperation::TFOperation(ros::NodeHandle nh):nh(nh)
{}

TFOperation::~TFOperation()
{}

void TFOperation::TFListen(std::string base_frame, std::string target_frame)
{
    listener.lookupTransform(base_frame, target_frame, ros::Time::now(), listen_transform);
}


