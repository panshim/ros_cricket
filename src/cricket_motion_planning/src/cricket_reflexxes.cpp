#include "cricket_motion_planning/cricket_reflexxes.hpp"

CricketReflexxes::CricketReflexxes(ros::NodeHandle nh):nh(nh), tf_oper(nh)
{
    // Subscriber & Publisher
    //topic: [reflexxes_target_cart] --> {ReflexML} --> [cartesian_pos_cmd] --> {Inverse Postion Kine}.
    sub_reflex_target = nh.subscribe<geometry_msgs::Pose>("reflexxes_target_cart", 100, &CricketReflexxes::SubMsgCallback, this);
    pub_next_cart = nh.advertise<geometry_msgs::Pose>("cartesian_pos_cmd", 100);
    // Reflexxes Motion Lib Call
    IP=new RMLPositionInputParameters(NUMBER_OF_DOFS);
    OP=new RMLPositionOutputParameters(NUMBER_OF_DOFS);
    RML=new ReflexxesAPI(NUMBER_OF_DOFS, CYCLE_TIME_IN_SECONDS);
    timer = nh.createTimer(ros::Duration(CYCLE_TIME_IN_SECONDS), &CricketReflexxes::TimerCallback, this);
    ResultValue = 0;
    /* TF Operation class initialization in Initial List */

    /* set MAX ARGUMENTS for Reflexxes Call */
    IP->MaxVelocityVector->VecData          [0] = 20.0;
    IP->MaxVelocityVector->VecData          [1] = 20.0;
    IP->MaxVelocityVector->VecData          [2] = 20.0;
    IP->MaxVelocityVector->VecData          [3] = 10.0;
    IP->MaxVelocityVector->VecData          [4] = 10.0;
    IP->MaxVelocityVector->VecData          [5] = 10.0;

    IP->MaxAccelerationVector->VecData      [0] = 20.0;
    IP->MaxAccelerationVector->VecData      [1] = 20.0;
    IP->MaxAccelerationVector->VecData      [2] = 20.0;
    IP->MaxAccelerationVector->VecData      [3] = 10.0;
    IP->MaxAccelerationVector->VecData      [4] = 10.0;
    IP->MaxAccelerationVector->VecData      [5] = 10.0;
    
    IP->MaxJerkVector->VecData              [0] = 400.0;
    IP->MaxJerkVector->VecData              [1] = 300.0;
    IP->MaxJerkVector->VecData              [2] = 200.0;
    IP->MaxJerkVector->VecData              [3] = 20.0;
    IP->MaxJerkVector->VecData              [4] = 20.0;
    IP->MaxJerkVector->VecData              [5] = 20.0;

    /* set Initial CURRENT POSITION for Reflexxes Call */
    // Note: For the very first motion after starting the controller, velocities & acceleration are commonly set to zero.
    tf_oper.TFListen("/lwr_base_link", "/lwr_7_link");
    double roll, pitch, yaw;
    QuaternionToRPY<tf::Quaternion>(tf_oper.listen_transform.getRotation(), roll, pitch, yaw);
    IP->CurrentPositionVector->VecData      [0] = tf_oper.listen_transform.getOrigin().getX();
    IP->CurrentPositionVector->VecData      [1] = tf_oper.listen_transform.getOrigin().getY();
    IP->CurrentPositionVector->VecData      [2] = tf_oper.listen_transform.getOrigin().getZ();
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

void CricketReflexxes::SubMsgCallback(const geometry_msgs::Pose rcv_msg)
{
    // Update the object state
    reflexxesTarget = rcv_msg;

    /* Set-up TARGET of the input parameters */
    double roll, pitch, yaw;
    QuaternionToRPY<geometry_msgs::Quaternion>(reflexxesTarget.orientation, roll, pitch, yaw);
    IP->TargetPositionVector->VecData       [0] = reflexxesTarget.position.x;
    IP->TargetPositionVector->VecData       [1] = reflexxesTarget.position.y;
    IP->TargetPositionVector->VecData       [2] = reflexxesTarget.position.z;
    IP->TargetPositionVector->VecData       [3] = roll;
    IP->TargetPositionVector->VecData       [4] = pitch;
    IP->TargetPositionVector->VecData       [5] = yaw;

    IP->TargetVelocityVector->VecData       [0] = 0;
    IP->TargetVelocityVector->VecData       [1] = 0;
    IP->TargetVelocityVector->VecData       [2] = 0;
    IP->TargetVelocityVector->VecData       [3] = 0;
    IP->TargetVelocityVector->VecData       [4] = 0;
    IP->TargetVelocityVector->VecData       [5] = 0;

    IP->SelectionVector->VecData            [0] = true;
    IP->SelectionVector->VecData            [1] = true;
    IP->SelectionVector->VecData            [2] = true;
    IP->SelectionVector->VecData            [3] = true;
    IP->SelectionVector->VecData            [4] = true;
    IP->SelectionVector->VecData            [5] = true;

}

void CricketReflexxes::TimerCallback(const ros::TimerEvent&)
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
    
    // step3: Update the Module's Input: IP
    tf_oper.TFListen("/lwr_base_link", "/lwr_7_link");
    double roll, pitch, yaw;
    QuaternionToRPY<tf::Quaternion>(tf_oper.listen_transform.getRotation(), roll, pitch, yaw);
    IP->CurrentPositionVector->VecData      [0] = tf_oper.listen_transform.getOrigin().getX();
    IP->CurrentPositionVector->VecData      [1] = tf_oper.listen_transform.getOrigin().getY();
    IP->CurrentPositionVector->VecData      [2] = tf_oper.listen_transform.getOrigin().getZ();
    IP->CurrentPositionVector->VecData      [3] = roll;
    IP->CurrentPositionVector->VecData      [4] = pitch;
    IP->CurrentPositionVector->VecData      [5] = yaw;
    // *IP->CurrentPositionVector      =*OP->NewPositionVector;
    *IP->CurrentVelocityVector      =*OP->NewVelocityVector;
    *IP->CurrentAccelerationVector  =*OP->NewAccelerationVector;
}

template<class T> void CricketReflexxes::QuaternionToRPY(const T Quat, double &roll, double &pitch, double &yaw)
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