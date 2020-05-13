#include "cricket_coordinate/cricket_coordinate.hpp"

int main(int argc, char **argv)
{
    /* To initialize a node called "cricket_coordinate_node" */
    ros::init(argc, argv, "cricket_coordinate_node");
    ros::NodeHandle nh;
    CricketCoordinate cood(nh);

    while (ros::ok()) {
        /* Receive a keyboard signal: Player, Get Ready! */
        char readySignal;
        // std::cout << "press 'r' to get ready..." << std::endl;
        // std::cin >> readySignal;
        // if( readySignal == 'r' )
        // {
        cood.getReady();
        // }
        std::cout << "Get into ball hitting loop!... " << std::endl;
        system("rosnode list");

        /* a loop to subscribe the ball & publish command */
        ros::spin();
    }

    return 0;
}
