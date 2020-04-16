#ifndef _TF_OPERATION_H_
#define _TF_OPERATION_H_

#include <ros/ros.h>
#include <tf/transform_listener.h>
#include <string>
class TFOperation
{
    private:
        ros::NodeHandle nh;
        tf::TransformListener listener;
    public:
        tf::StampedTransform listen_transform;
        TFOperation(ros::NodeHandle nh);
        ~TFOperation();
        void TFListen(std::string base_frame, std::string target_frame);
};


#endif