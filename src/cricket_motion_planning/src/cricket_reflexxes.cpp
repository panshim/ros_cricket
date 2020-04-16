#include "cricket_motion_planning/cricket_reflexxes.hpp"
#include "tf_operation.hpp"

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
    IP->MaxVelocityVector->VecData          [0] = 300.0;
    IP->MaxVelocityVector->VecData          [1] = 100.0;
    IP->MaxVelocityVector->VecData          [2] = 300.0;
    IP->MaxVelocityVector->VecData          [3] = 300.0;
    IP->MaxVelocityVector->VecData          [4] = 300.0;
    IP->MaxVelocityVector->VecData          [5] = 300.0;

    IP->MaxAccelerationVector->VecData      [0] = 300.0;
    IP->MaxAccelerationVector->VecData      [1] = 200.0;
    IP->MaxAccelerationVector->VecData      [2] = 100.0;
    IP->MaxAccelerationVector->VecData      [3] = 100.0;
    IP->MaxAccelerationVector->VecData      [4] = 100.0;
    IP->MaxAccelerationVector->VecData      [5] = 100.0;
    
    IP->MaxJerkVector->VecData              [0] = 400.0;
    IP->MaxJerkVector->VecData              [1] = 300.0;
    IP->MaxJerkVector->VecData              [2] = 200.0;
    IP->MaxJerkVector->VecData              [3] = 200.0;
    IP->MaxJerkVector->VecData              [4] = 200.0;
    IP->MaxJerkVector->VecData              [5] = 200.0;

    /* set Initial CURRENT POSITION for Reflexxes Call */
    // Note: For the very first motion after starting the controller, velocities & acceleration are commonly set to zero.
    tf_oper.TFListen("/lwr_base_link", "/lwr_7_link");
    IP->CurrentPositionVector->VecData      [0] = tf_oper.listen_transform.getOrigin().getX();
    IP->CurrentPositionVector->VecData      [1] = tf_oper.listen_transform.getOrigin().getY();
    IP->CurrentPositionVector->VecData      [2] = tf_oper.listen_transform.getOrigin().getZ();
    IP->CurrentPositionVector->VecData      [3] = tf_oper.listen_transform.getRotation().get;
    IP->CurrentPositionVector->VecData      [4] = tf_oper.listen_transform.getOrigin().getZ();
    IP->CurrentPositionVector->VecData      [5] = tf_oper.listen_transform.getOrigin().getZ();

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
    reflexeesTarget = rcv_msg;

    /* Set-up TARGET of the input parameters */
    IP->TargetPositionVector->VecData       [0] = reflexeesTarget.position.x;
    IP->TargetPositionVector->VecData       [1] = reflexeesTarget.position.y;
    IP->TargetPositionVector->VecData       [2] = reflexeesTarget.position.z;
    IP->TargetVelocityVector->VecData       [0] = 0;
    IP->TargetVelocityVector->VecData       [1] = 0;
    IP->TargetVelocityVector->VecData       [2] = 0;
    IP->SelectionVector->VecData            [0] = true;
    IP->SelectionVector->VecData            [1] = true;
    IP->SelectionVector->VecData            [2] = true;

}

void CricketReflexxes::TimerCallback(const ros::TimerEvent&)
{
    // Calling the Reflexxes OTG algorithm
    ResultValue =   RML->RMLPosition(*IP, OP, Flags);

    if (ResultValue < 0)
    {
        ROS_ERROR("ERROR Calc RMLPosition ---- error code: (%d).\n", ResultValue );
    }
    cartesian_pos_next_cmd.position.x = OP->NewPositionVector->VecData
    
    
    pub_next_cart.publish();
    
    tf_oper.TFListen("/lwr_base_link", "/lwr_7_link");
    IP->CurrentPositionVector->VecData [0] = tf_oper.listen_transform.getOrigin().getX();
    IP->CurrentPositionVector->VecData [1] = tf_oper.listen_transform.getOrigin().getY();
    IP->CurrentPositionVector->VecData [2] = tf_oper.listen_transform.getOrigin().getZ();
    // *IP->CurrentPositionVector      =*OP->NewPositionVector;
    *IP->CurrentVelocityVector      =*OP->NewVelocityVector;
    *IP->CurrentAccelerationVector  =*OP->NewAccelerationVector;
}