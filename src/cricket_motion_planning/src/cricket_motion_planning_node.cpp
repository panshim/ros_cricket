#include "cricket_motion_planning/cricket_reflexxes.hpp"

int main(int argc, char **argv)
{
       /* To initialize a node called "test_kdl_node" */
    ros::init(argc, argv, "cricket_motion_planning_node");

    ros::NodeHandle nh;
    CricketReflexxes lwrMP(nh); 
    
    /* Rate controlling: inside */
    ros::spin();

    return 0;
}