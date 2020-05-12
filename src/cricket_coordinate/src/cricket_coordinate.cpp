#include "cricket_coordinate/cricket_coordinate.hpp"

CricketCoordinate::CricketCoordinate(ros::NodeHandle nh):nh(nh)
{
    /* Get to the ready postion */
    pub_ready = nh.advertise<geometry_msgs::Pose>("reflexxes_target_cart", 1);
    ready_pose.position.x = 0.20;
    ready_pose.position.y = -0.20;
    ready_pose.position.z = 0.80;
    ready_pose.orientation.x = 0.5;
    ready_pose.orientation.y = 0.5;
    ready_pose.orientation.z = 0.5;
    ready_pose.orientation.w = 0.5;

    /* Subscrib tracking ball & Move if within the predesigned range */
    sub_ball = nh.subscribe("ball/target", 1, &CricketCoordinate::SubBallCallback, this);

    /* Publish Reflexxes Command */
    pub_reflexxes_pose = nh.advertise<geometry_msgs::Pose>("reflexxes_target_cart", 10);
    pub_reflexxes_twist = nh.advertise<geometry_msgs::Twist>("reflexxes_target_twist", 10);

    /* get Pose of LWR_base and LWR_ee */
    cli_model_lwr =  nh.serviceClient<gazebo_msgs::GetLinkState>("gazebo/get_link_state");
    srv_linkbasestate.request.link_name = "lwr_1_link";
    srv_linkbasestate.request.reference_frame = "world";
    cli_model_lwr.waitForExistence();
    if(cli_model_lwr.call(srv_linkbasestate))
    {
        link_base_pose = srv_linkbasestate.response.link_state.pose;
        link_base_trans = GeoposeToTftrans(link_base_pose);
    }
    else
    {
        std::cout << "Service cli_link_base call failed" << std::endl;
    }
    
    cli_link_7 = nh.serviceClient<gazebo_msgs::GetLinkState>("gazebo/get_link_state");
    srv_link7state.request.link_name = "lwr_7_link";
    srv_link7state.request.reference_frame = "world";
    cli_link_7.waitForExistence();
}

CricketCoordinate::~CricketCoordinate(){}

/* if Within the Range, then publish the ReflexxesCommand */
void CricketCoordinate::SubBallCallback(const geometry_msgs::TwistStamped rcv_msg)
{
    // get lwr_7_link's global trans
    if(cli_link_7.call(srv_link7state))
    {
        link_7_pose = srv_link7state.response.link_state.pose;
        link_7_trans = GeoposeToTftrans(link_7_pose);

        if(BallWithinRange(rcv_msg)) // if in range, then publish Reflexxes related topics
        {
            // publish target pose
            tf::Transform ball_trans = GeoaccToTftrans(rcv_msg);
            tf::Transform reflexxesTrans = link_base_trans.inverseTimes(ball_trans);
            pub_reflexxes_pose.publish( TftransToGeopose(reflexxesTrans) );
            
            // publish target twist
            geometry_msgs::Twist targetTwist;
            targetTwist.linear.x = rcv_msg.twist.angular.x;
            targetTwist.linear.y = rcv_msg.twist.angular.y;
            targetTwist.linear.z = rcv_msg.twist.angular.z;
            pub_reflexxes_twist.publish(targetTwist);
            std::cout << "Ball in Range, Move!!!" << std::endl;
        }
        else
        {
            std::cout << "Ball Not in Working Range..." << std::endl;
        }
    }
    else
    {
        std::cout << "Service cli_link_7 call failed" << std::endl;
    }
}

/* judge if the ball is within the predefined range: 1.close to the EE; 2.not lower than the table */
bool CricketCoordinate::BallWithinRange(const geometry_msgs::TwistStamped ball_pose)
{
    tf::Transform ball_trans = GeoaccToTftrans(ball_pose);
    return ( link_7_trans.getOrigin().distance(ball_trans.getOrigin())<2 && ball_trans.getOrigin().getZ()>1 );
}

/* LWR arm goes to ready position */
bool CricketCoordinate::getReady()
{
    pub_ready.publish(ready_pose);
    return true;
}

/* Message transformation */
tf::Transform CricketCoordinate::GeoposeToTftrans(const geometry_msgs::Pose geoPose)
{
    tf::Quaternion tfQuat(geoPose.orientation.x, geoPose.orientation.y, geoPose.orientation.z, geoPose.orientation.w);
    tf::Vector3 tfVec(geoPose.position.x, geoPose.position.y, geoPose.position.z);
    tf::Transform tfTrans(tfQuat, tfVec);
    
    return tfTrans;
}

/* Message transformation */
tf::Transform CricketCoordinate::GeoaccToTftrans(const geometry_msgs::TwistStamped geoAcc)
{
    // construct quaternion piece
    tf::Vector3 axisY(0.0, 1.0, 0.0);
    tf::Vector3 orientY(-geoAcc.twist.angular.x, -geoAcc.twist.angular.y, -geoAcc.twist.angular.z);
    tfScalar theta = axisY.angle(orientY);
    tf::Vector3 w = axisY.cross(orientY);

    // construct transformation
    tf::Quaternion tfQuat(w, theta);
    tf::Vector3 tfVec(geoAcc.twist.linear.x, geoAcc.twist.linear.y, geoAcc.twist.linear.z);
    tf::Transform tfTrans(tfQuat,tfVec);

    return tfTrans;
}

/* Message transformation */
geometry_msgs::Pose CricketCoordinate::TftransToGeopose(const tf::Transform trans)
{
    geometry_msgs::Pose geoPose;
    geoPose.position.x = trans.getOrigin().getX();
    geoPose.position.y = trans.getOrigin().getY();
    geoPose.position.z = trans.getOrigin().getZ();
    geoPose.orientation.x = trans.getRotation().getX();
    geoPose.orientation.y = trans.getRotation().getY();
    geoPose.orientation.z = trans.getRotation().getZ();
    geoPose.orientation.w = trans.getRotation().getW();

    return geoPose;
}
