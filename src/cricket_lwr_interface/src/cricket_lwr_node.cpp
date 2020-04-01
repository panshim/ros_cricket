#include "cricket_lwr_interface/cricket_lwr.hpp"

int main(int argc, char **argv)
{
       /* To initialize a node called "test_kdl_node" */
    ros::init(argc, argv, "test_kdl_node");

    ros::NodeHandle nh;
    LwrCartesianCommand lwrCartCmd(nh); 
    
    /* Rate controlling: inside */
    ros::spin();

    return 0;
}