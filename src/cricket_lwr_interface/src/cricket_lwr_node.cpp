#include "cricket_lwr_interface/cricket_lwr.hpp"

int main(int argc, char **argv)
{
       /* To initialize a node called "cricket_lwr_node" */
    ros::init(argc, argv, "cricket_lwr_node");

    ros::NodeHandle nh;
    LwrCartesianCommand lwrCartCmd(nh); 
    
    /* Rate controlling: inside */
    ros::spin();

    return 0;
}