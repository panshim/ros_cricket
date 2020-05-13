#include "cricket_coordinate/cricket_coordinate.hpp"

int main(int argc, char **argv)
{
    /* To initialize a node called "cricket_coordinate_node" */
    ros::init(argc, argv, "cricket_coordinate_node");
    ros::NodeHandle nh;
    CricketCoordinate cood(nh);

<<<<<<< HEAD
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
=======
    /* Receive a keyboard signal: Player, Get Ready! */
    // std::cout << "press 'r' to get ready..." << std::endl;
    // std::cin >> readySignal;
    // if( readySignal == 'r' )
    // {
    ros::Duration(0.5).sleep();//wait cood to be constructed
    cood.getReady();
    // }
    std::cout << "Get into ball hitting loop!... " << std::endl;
>>>>>>> a30d7fd348b949f5b596b85e8de7ef4dc9196de1

    /* a loop to subscribe the ball & publish command */
    ros::spin();

    return 0;
}
