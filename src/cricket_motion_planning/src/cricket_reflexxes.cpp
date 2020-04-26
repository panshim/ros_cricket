#include "cricket_motion_planning/cricket_reflexxes.hpp"

CricketReflexxes::CricketReflexxes(ros::NodeHandle nh):nh(nh), tf_oper(nh)
{
    // Subscriber & Publisher
    //topic: [reflexxes_target_cart] --> {ReflexML} --> [cartesian_pos_cmd] --> {Inverse Postion Kine}.
    sub_reflex_target = nh.subscribe<geometry_msgs::Pose>("reflexxes_target_cart", 1, &CricketReflexxes::SubMsgCallbackPose, this);
    sub_reflex_twist = nh.subscribe<geometry_msgs::Twist>("reflexxes_target_twist", 1, &CricketReflexxes::SubMsgCallbackTwist, this);
    pub_next_cart = nh.advertise<geometry_msgs::Pose>("cartesian_pos_cmd", 10);
    pub_inv_next_cart = nh.advertise<lwr_controllers::PoseRPY>("/lwr/one_task_inverse_kinematics/command", 1);
    // Reflexxes Motion Lib Call
    IP=new RMLPositionInputParameters(NUMBER_OF_DOFS);
    OP=new RMLPositionOutputParameters(NUMBER_OF_DOFS);
    RML=new ReflexxesAPI(NUMBER_OF_DOFS, CYCLE_TIME_IN_SECONDS);
    timer = nh.createTimer(ros::Duration(CYCLE_TIME_IN_SECONDS), &CricketReflexxes::TimerCallback, this);
    ResultValue = 0;
    /* TF Operation class initialization in Initial List */

    /* set MAX ARGUMENTS for Reflexxes Call */
    IP->MaxVelocityVector->VecData          [0] = 2000.0;
    IP->MaxVelocityVector->VecData          [1] = 2000.0;
    IP->MaxVelocityVector->VecData          [2] = 2000.0;
    IP->MaxVelocityVector->VecData          [3] = 3140.0;
    IP->MaxVelocityVector->VecData          [4] = 3140.0;
    IP->MaxVelocityVector->VecData          [5] = 3140.0;

    IP->MaxAccelerationVector->VecData      [0] = 5000000.0;
    IP->MaxAccelerationVector->VecData      [1] = 5000000.0;
    IP->MaxAccelerationVector->VecData      [2] = 5000000.0;
    IP->MaxAccelerationVector->VecData      [3] = 5000000.0;
    IP->MaxAccelerationVector->VecData      [4] = 5000000.0;
    IP->MaxAccelerationVector->VecData      [5] = 5000000.0;
    
    IP->MaxJerkVector->VecData              [0] = 1000000000.0;
    IP->MaxJerkVector->VecData              [1] = 1000000000.0;
    IP->MaxJerkVector->VecData              [2] = 1000000000.0;
    IP->MaxJerkVector->VecData              [3] = 1000000000.0;
    IP->MaxJerkVector->VecData              [4] = 1000000000.0;
    IP->MaxJerkVector->VecData              [5] = 1000000000.0;

    IP->SelectionVector->VecData            [0] = true;
    IP->SelectionVector->VecData            [1] = true;
    IP->SelectionVector->VecData            [2] = true;
    IP->SelectionVector->VecData            [3] = true;
    IP->SelectionVector->VecData            [4] = true;
    IP->SelectionVector->VecData            [5] = true;

    /* set Initial CURRENT POSITION for Reflexxes Call */
    // Note: For the very first motion after starting the controller, velocities & acceleration are commonly set to zero.
    tf_oper.TFListen("/lwr_7_link", "/lwr_base_link");
    double roll, pitch, yaw;
    geometry_msgs::TransformStamped geo_ST;
    // from "tf::StampedTransform" to "geometry_msgs::TransformStamped"
    transformStampedTFToMsg(tf_oper.listen_transform, geo_ST);
    //extract "geometry_msgs::Quaternion" from "geometry_msgs::TransformStamped"
    geometry_msgs::Quaternion Quat(geo_ST.transform.rotation);
    CricketReflexxes::QuaternionToRPY<geometry_msgs::Quaternion>(Quat, roll, pitch, yaw);
    
    IP->CurrentPositionVector->VecData      [0] = geo_ST.transform.translation.x;
    IP->CurrentPositionVector->VecData      [1] = geo_ST.transform.translation.y;
    IP->CurrentPositionVector->VecData      [2] = geo_ST.transform.translation.z;
    IP->CurrentPositionVector->VecData      [3] = roll;
    IP->CurrentPositionVector->VecData      [4] = pitch;
    IP->CurrentPositionVector->VecData      [5] = yaw;

    IP->CurrentVelocityVector->VecData      [0] = 0;
    IP->CurrentVelocityVector->VecData      [1] = 0;
    IP->CurrentVelocityVector->VecData      [2] = 0;
    IP->CurrentVelocityVector->VecData      [3] = 0;
    IP->CurrentVelocityVector->VecData      [4] = 0;
    IP->CurrentVelocityVector->VecData      [5] = 0;
    
    IP->CurrentAccelerationVector->VecData  [0] = 0;
    IP->CurrentAccelerationVector->VecData  [1] = 0;
    IP->CurrentAccelerationVector->VecData  [2] = 0;
    IP->CurrentAccelerationVector->VecData  [3] = 0;
    IP->CurrentAccelerationVector->VecData  [4] = 0;
    IP->CurrentAccelerationVector->VecData  [5] = 0;
}

CricketReflexxes::~CricketReflexxes()
{
    delete IP;
    delete OP;
    delete RML;
}

void CricketReflexxes::SubMsgCallbackPose(const geometry_msgs::Pose rcv_msg)
{
    // Update the object state
    reflexxesTarget = rcv_msg;

    /* Set-up TARGET of the input parameters */
    double roll, pitch, yaw;
    CricketReflexxes::QuaternionToRPY<geometry_msgs::Quaternion>(reflexxesTarget.orientation, roll, pitch, yaw);
    IP->TargetPositionVector->VecData       [0] = reflexxesTarget.position.x;
    IP->TargetPositionVector->VecData       [1] = reflexxesTarget.position.y;
    IP->TargetPositionVector->VecData       [2] = reflexxesTarget.position.z;
    IP->TargetPositionVector->VecData       [3] = roll;
    IP->TargetPositionVector->VecData       [4] = pitch;
    IP->TargetPositionVector->VecData       [5] = yaw;
}

void CricketReflexxes::SubMsgCallbackTwist(const geometry_msgs::Twist rcv_msg)
{
    // nomalize the velocity
    geometry_msgs::Vector3 tarVel = rcv_msg.linear;
    double den = sqrt( pow(rcv_msg.linear.x,2)+pow(rcv_msg.linear.y,2)+pow(rcv_msg.linear.z,2) );
    tarVel.x = -rcv_msg.linear.x / den;
    tarVel.y = -rcv_msg.linear.y / den;
    tarVel.z = -rcv_msg.linear.z / den;
    
    IP->TargetVelocityVector->VecData       [0] = tarVel.x;
    IP->TargetVelocityVector->VecData       [1] = tarVel.y;
    IP->TargetVelocityVector->VecData       [2] = tarVel.z;
    IP->TargetVelocityVector->VecData       [3] = 0;
    IP->TargetVelocityVector->VecData       [4] = 0;
    IP->TargetVelocityVector->VecData       [5] = 0;
}


void CricketReflexxes::TimerCallback(const ros::TimerEvent& event)
{
    // step1: Calling the Reflexxes OTG algorithm: Calc Module's Output: OP
    ResultValue =   RML->RMLPosition(*IP, OP, Flags);
    if (ResultValue < 0)
    {
        ROS_ERROR("ERROR Calc RMLPosition ---- error code: (%d).\n", ResultValue );
    }

    // step2: publish on topic: "cartesian_pos_cmd"
    tf::Quaternion tf_quat;
    RPYToQuaternion(tf_quat, OP->NewPositionVector->VecData[3], OP->NewPositionVector->VecData[4], OP->NewPositionVector->VecData[5]);
    cartesian_pos_next_cmd.position.x = OP->NewPositionVector->VecData[0];
    cartesian_pos_next_cmd.position.y = OP->NewPositionVector->VecData[1];
    cartesian_pos_next_cmd.position.z = OP->NewPositionVector->VecData[2];
    cartesian_pos_next_cmd.orientation.x = tf_quat.getX();
    cartesian_pos_next_cmd.orientation.y = tf_quat.getY();
    cartesian_pos_next_cmd.orientation.z = tf_quat.getZ();
    cartesian_pos_next_cmd.orientation.w = tf_quat.getW();
    pub_next_cart.publish(cartesian_pos_next_cmd);
    
    // Step 2.1(backup): publish on topic: "/lwr/one_task_inverse_kinematics/command"
    inv_pos_next_cmd.position.x = OP->NewPositionVector->VecData[0];
    inv_pos_next_cmd.position.y = OP->NewPositionVector->VecData[1];
    inv_pos_next_cmd.position.z = OP->NewPositionVector->VecData[2];
    inv_pos_next_cmd.orientation.roll = OP->NewPositionVector->VecData[3];
    inv_pos_next_cmd.orientation.pitch = OP->NewPositionVector->VecData[4];
    inv_pos_next_cmd.orientation.yaw = OP->NewPositionVector->VecData[5];
    pub_inv_next_cart.publish(inv_pos_next_cmd);

    // step3: Update the Module's Input: IP
    tf_oper.TFListen("/lwr_base_link", "/lwr_7_link");
    double roll, pitch, yaw;
    geometry_msgs::TransformStamped geo_ST;
    transformStampedTFToMsg(tf_oper.listen_transform, geo_ST);
    geometry_msgs::Quaternion Quat(geo_ST.transform.rotation);
    CricketReflexxes::QuaternionToRPY<geometry_msgs::Quaternion>(Quat, roll, pitch, yaw);
    // CricketReflexxes::QuaternionToRPY<tf::Quaternion>(tf_oper.listen_transform.getRotation(), roll, pitch, yaw);
    IP->CurrentPositionVector->VecData      [0] = geo_ST.transform.translation.x;
    IP->CurrentPositionVector->VecData      [1] = geo_ST.transform.translation.y;
    IP->CurrentPositionVector->VecData      [2] = geo_ST.transform.translation.z;
    IP->CurrentPositionVector->VecData      [3] = roll;
    IP->CurrentPositionVector->VecData      [4] = pitch;
    IP->CurrentPositionVector->VecData      [5] = yaw;
    *IP->CurrentVelocityVector      =*OP->NewVelocityVector;
    *IP->CurrentAccelerationVector  =*OP->NewAccelerationVector;
}


template<class T> void CricketReflexxes::QuaternionToRPY(T Quat, double &roll, double &pitch, double &yaw)
{
    // By default, in ROS, RPY rotation means ZYX (first Z axis, then Y axis, last X axis)
    tf::Quaternion q(Quat.x, Quat.y, Quat.z, Quat.w);
    tf::Matrix3x3 mat(q);
    mat.getRPY(roll, pitch, yaw);
}


void CricketReflexxes::RPYToQuaternion(tf::Quaternion &Quat, double roll, double pitch, double yaw)
{
    Quat.setRPY(roll, pitch, yaw);
}