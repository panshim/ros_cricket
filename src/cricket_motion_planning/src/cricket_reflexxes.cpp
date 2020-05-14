#include "cricket_motion_planning/cricket_reflexxes.hpp"

CricketReflexxes::CricketReflexxes(ros::NodeHandle nh):nh(nh), tf_oper(nh)
{
    /* Step1: Subscriber & Publisher */
    //topic: [reflexxes_target_cart] --> {ReflexML} --> [cartesian_pos_cmd] --> {Inverse Postion Kine}.
    sub_reflex_target = nh.subscribe<geometry_msgs::Pose>("/reflexxes_target_cart", 10, &CricketReflexxes::SubMsgCallbackPose, this);
    sub_reflex_twist = nh.subscribe<geometry_msgs::Twist>("/reflexxes_target_twist", 10, &CricketReflexxes::SubMsgCallbackTwist, this);
    sub_jointstate = nh.subscribe<sensor_msgs::JointState>("/lwr/joint_states", 1, &CricketReflexxes::SubMsgCallbackJnt, this);
    pub_next_cart = nh.advertise<geometry_msgs::Pose>("/cartesian_pos_cmd", 1);
    pub_inv_next_cart = nh.advertise<lwr_controllers::PoseRPY>("/lwr/one_task_inverse_kinematics/command", 1);
    
    /* Step2: Reflexxes Motion Lib Call */
    IP=new RMLPositionInputParameters(NUMBER_OF_DOFS);
    OP=new RMLPositionOutputParameters(NUMBER_OF_DOFS);
    RML=new ReflexxesAPI(NUMBER_OF_DOFS, CYCLE_TIME_IN_SECONDS);
    timer = nh.createTimer(ros::Duration(CYCLE_TIME_IN_SECONDS), &CricketReflexxes::TimerCallback, this);
    ResultValue = 0;
    /* TF Operation class initialization in Initial List */

    /* Step3: set MAX ARGUMENTS for Reflexxes Call */
    IP->MaxVelocityVector->VecData          [0] = 2000.0;
    IP->MaxVelocityVector->VecData          [1] = 2000.0;
    IP->MaxVelocityVector->VecData          [2] = 2000.0;
    IP->MaxVelocityVector->VecData          [3] = 314.0;
    IP->MaxVelocityVector->VecData          [4] = 314.0;
    IP->MaxVelocityVector->VecData          [5] = 314.0;

    IP->MaxAccelerationVector->VecData      [0] = 5000000.0;
    IP->MaxAccelerationVector->VecData      [1] = 5000000.0;
    IP->MaxAccelerationVector->VecData      [2] = 5000000.0;
    IP->MaxAccelerationVector->VecData      [3] = 5000000.0;
    IP->MaxAccelerationVector->VecData      [4] = 5000000.0;
    IP->MaxAccelerationVector->VecData      [5] = 5000000.0;
    
    IP->MaxJerkVector->VecData              [0] = 10000000000.0;
    IP->MaxJerkVector->VecData              [1] = 10000000000.0;
    IP->MaxJerkVector->VecData              [2] = 10000000000.0;
    IP->MaxJerkVector->VecData              [3] = 10000000000.0;
    IP->MaxJerkVector->VecData              [4] = 10000000000.0;
    IP->MaxJerkVector->VecData              [5] = 10000000000.0;

    IP->SelectionVector->VecData            [0] = true;
    IP->SelectionVector->VecData            [1] = true;
    IP->SelectionVector->VecData            [2] = true;
    IP->SelectionVector->VecData            [3] = true;
    IP->SelectionVector->VecData            [4] = true;
    IP->SelectionVector->VecData            [5] = true;
    
    /* Step4: set Initial CURRENT POSITION for Reflexxes Call */
    // Note: For the very first motion after starting the controller, velocities & acceleration are commonly set to zero.
    prevTime = ros::Time::now();
    nowTime = prevTime;
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

    /* Step5: Cricket Bat Transformmation */
    tf::Vector3 batVec(0,0,-0.2);
    tf::Quaternion batQuat(0,0,-0.259,0.966);
    // tf::Quaternion batQuat(0,0,0,1);
    batTransform.setOrigin(batVec);
    batTransform.setRotation(batQuat);

    /* Step6: Forward Velocity Solver */
    std::string robot_description_string;
    nh.param("robot_description", robot_description_string, std::string());
    if(kdl_parser::treeFromString(robot_description_string, tree))
    {
        if(tree.getChain("lwr_base_link", "lwr_7_link", chain))
        {
            solv_fd_vel = new KDL::ChainFkSolverVel_recursive(chain);
        }
        else
        {
            ROS_ERROR("Cannot get a chain!");
        }
    }
    else
    {
        ROS_ERROR("Cannot get a tree!");
    }
    jntArrayVel.resize(chain.getNrOfJoints());
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
    
    // IP->TargetVelocityVector->VecData       [0] = tarVel.x;
    // IP->TargetVelocityVector->VecData       [1] = tarVel.y;
    // IP->TargetVelocityVector->VecData       [2] = tarVel.z;
    IP->TargetVelocityVector->VecData       [0] = 0;
    IP->TargetVelocityVector->VecData       [1] = 0;
    IP->TargetVelocityVector->VecData       [2] = 0;
    IP->TargetVelocityVector->VecData       [3] = 0;
    IP->TargetVelocityVector->VecData       [4] = 0;
    IP->TargetVelocityVector->VecData       [5] = 0;
}

void CricketReflexxes::SubMsgCallbackJnt(const sensor_msgs::JointState recv_js)
{
    for(int i=0; i<chain.getNrOfJoints(); i++)
    {
        jntArrayVel.q(i) = recv_js.position[i];
        jntArrayVel.qdot(i) = recv_js.velocity[i];
    }
}

void CricketReflexxes::TimerCallback(const ros::TimerEvent& event)
{
    // step1: Update the Module's Input: IP
    tf_oper.TFListen("/lwr_7_link", "/lwr_base_link");
    double roll, pitch, yaw;
    geometry_msgs::TransformStamped geo_ST;
    transformStampedTFToMsg(tf_oper.listen_transform, geo_ST);
    geometry_msgs::Quaternion Quat(geo_ST.transform.rotation);
    CricketReflexxes::QuaternionToRPY<geometry_msgs::Quaternion>(Quat, roll, pitch, yaw);
    
    //calc. current forward velocity
    solv_fd_vel->JntToCart(jntArrayVel, frameVel);
    IP->CurrentVelocityVector->VecData      [0] = frameVel.GetTwist().vel[0];
    IP->CurrentVelocityVector->VecData      [1] = frameVel.GetTwist().vel[1];
    IP->CurrentVelocityVector->VecData      [2] = frameVel.GetTwist().vel[2];
    IP->CurrentVelocityVector->VecData      [3] = frameVel.GetTwist().rot[0];
    IP->CurrentVelocityVector->VecData      [4] = frameVel.GetTwist().rot[1];
    IP->CurrentVelocityVector->VecData      [5] = frameVel.GetTwist().rot[2];

    IP->CurrentPositionVector->VecData      [0] = geo_ST.transform.translation.x;
    IP->CurrentPositionVector->VecData      [1] = geo_ST.transform.translation.y;
    IP->CurrentPositionVector->VecData      [2] = geo_ST.transform.translation.z;
    IP->CurrentPositionVector->VecData      [3] = roll;
    IP->CurrentPositionVector->VecData      [4] = pitch;
    IP->CurrentPositionVector->VecData      [5] = yaw;
    // *IP->CurrentVelocityVector      =*OP->NewVelocityVector;
    *IP->CurrentAccelerationVector  =*OP->NewAccelerationVector;

    // step2: Calling the Reflexxes OTG algorithm: Calc Module's Output: OP
    ResultValue =   RML->RMLPosition(*IP, OP, Flags);
    if (ResultValue < 0)
    {
        ROS_ERROR("ERROR Calc RMLPosition ---- error code: (%d).\n", ResultValue );
        std::cout << "IntervalTime: " << intervalTime << std::endl;
        std::cout << "OP->Vec[0]" << OP->NewPositionVector->VecData[0] << std::endl;
        std::cout << "OP->Vec[1]" << OP->NewPositionVector->VecData[1] << std::endl;
        std::cout << "OP->Vec[2]" << OP->NewPositionVector->VecData[2] << std::endl;
        std::cout << "OP->Vec[3]" << OP->NewPositionVector->VecData[3] << std::endl;
        std::cout << "OP->Vec[4]" << OP->NewPositionVector->VecData[4] << std::endl;
        std::cout << "OP->Vec[5]" << OP->NewPositionVector->VecData[5] << std::endl;
    }

    // step3: publish on topic: "cartesian_pos_cmd"
    tf::Quaternion tf_quat;
    RPYToQuaternion(tf_quat, OP->NewPositionVector->VecData[3], OP->NewPositionVector->VecData[4], OP->NewPositionVector->VecData[5]);
    
    // contruct eeTransform and drift
    tf::Vector3 eeVec(OP->NewPositionVector->VecData[0], OP->NewPositionVector->VecData[1], OP->NewPositionVector->VecData[2] );
    eeTransform.setOrigin(eeVec);
    eeTransform.setRotation(tf_quat);

    // hitting point is on the "Bat", not the "End-Effector"
    eeTransform = eeTransform * batTransform;

    //Construct topic: "cartesian_pos_cmd"
    cartesian_pos_next_cmd.position.x = eeTransform.getOrigin().getX();
    cartesian_pos_next_cmd.position.y = eeTransform.getOrigin().getY();
    cartesian_pos_next_cmd.position.z = eeTransform.getOrigin().getZ();
    cartesian_pos_next_cmd.orientation.x = eeTransform.getRotation().getX();
    cartesian_pos_next_cmd.orientation.y = eeTransform.getRotation().getY();
    cartesian_pos_next_cmd.orientation.z = eeTransform.getRotation().getZ();
    cartesian_pos_next_cmd.orientation.w = eeTransform.getRotation().getW();
    pub_next_cart.publish(cartesian_pos_next_cmd);
    

    // Step 3.1(backup): publish on topic: "/lwr/one_task_inverse_kinematics/command"
    tf::Matrix3x3 mat(eeTransform.getRotation());
    mat.getRPY(roll, pitch, yaw);
    inv_pos_next_cmd.position.x = eeTransform.getOrigin().getX();
    inv_pos_next_cmd.position.y = eeTransform.getOrigin().getY();
    inv_pos_next_cmd.position.z = eeTransform.getOrigin().getZ();
    inv_pos_next_cmd.orientation.roll = roll;
    inv_pos_next_cmd.orientation.pitch = pitch;
    inv_pos_next_cmd.orientation.yaw = yaw;

    pub_inv_next_cart.publish(inv_pos_next_cmd);
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

double CricketReflexxes::RotationPrincipleValue(double rad)
{
    while(rad<-Pi)
        rad += 2*Pi;
    while(rad>Pi)
        rad -= 2*Pi;
    return rad;
}