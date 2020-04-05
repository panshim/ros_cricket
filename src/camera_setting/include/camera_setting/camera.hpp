#include <ros/ros.h>

class camera
{

private:

    double mat[3][4];
    std::string camera_name;

public:

    camera(std::string camera_name);
    ~camera();

    std::string get_name();
    void calibrate();

};