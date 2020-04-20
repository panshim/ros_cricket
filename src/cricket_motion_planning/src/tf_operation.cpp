#include "tf_operation.hpp"

TFOperation::TFOperation(ros::NodeHandle nh):nh(nh)
{}

TFOperation::~TFOperation()
{}

void TFOperation::TFListen(std::string target_frame, std::string base_frame)
{
    ros::Time now = ros::Time::now();
    listener.waitForTransform(target_frame, base_frame, now, ros::Duration(2.0));
    listener.lookupTransform(target_frame, base_frame, now, listen_transform);
}


