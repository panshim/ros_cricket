; Auto-generated. Do not edit!


(cl:in-package lwr_controllers-msg)


;//! \htmlinclude CartesianImpedancePoint.msg.html

(cl:defclass <CartesianImpedancePoint> (roslisp-msg-protocol:ros-message)
  ((header
    :reader header
    :initarg :header
    :type std_msgs-msg:Header
    :initform (cl:make-instance 'std_msgs-msg:Header))
   (x_FRI
    :reader x_FRI
    :initarg :x_FRI
    :type geometry_msgs-msg:Pose
    :initform (cl:make-instance 'geometry_msgs-msg:Pose))
   (k_FRI
    :reader k_FRI
    :initarg :k_FRI
    :type lwr_controllers-msg:Stiffness
    :initform (cl:make-instance 'lwr_controllers-msg:Stiffness))
   (d_FRI
    :reader d_FRI
    :initarg :d_FRI
    :type lwr_controllers-msg:Stiffness
    :initform (cl:make-instance 'lwr_controllers-msg:Stiffness))
   (f_FRI
    :reader f_FRI
    :initarg :f_FRI
    :type geometry_msgs-msg:Wrench
    :initform (cl:make-instance 'geometry_msgs-msg:Wrench)))
)

(cl:defclass CartesianImpedancePoint (<CartesianImpedancePoint>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <CartesianImpedancePoint>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'CartesianImpedancePoint)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name lwr_controllers-msg:<CartesianImpedancePoint> is deprecated: use lwr_controllers-msg:CartesianImpedancePoint instead.")))

(cl:ensure-generic-function 'header-val :lambda-list '(m))
(cl:defmethod header-val ((m <CartesianImpedancePoint>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader lwr_controllers-msg:header-val is deprecated.  Use lwr_controllers-msg:header instead.")
  (header m))

(cl:ensure-generic-function 'x_FRI-val :lambda-list '(m))
(cl:defmethod x_FRI-val ((m <CartesianImpedancePoint>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader lwr_controllers-msg:x_FRI-val is deprecated.  Use lwr_controllers-msg:x_FRI instead.")
  (x_FRI m))

(cl:ensure-generic-function 'k_FRI-val :lambda-list '(m))
(cl:defmethod k_FRI-val ((m <CartesianImpedancePoint>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader lwr_controllers-msg:k_FRI-val is deprecated.  Use lwr_controllers-msg:k_FRI instead.")
  (k_FRI m))

(cl:ensure-generic-function 'd_FRI-val :lambda-list '(m))
(cl:defmethod d_FRI-val ((m <CartesianImpedancePoint>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader lwr_controllers-msg:d_FRI-val is deprecated.  Use lwr_controllers-msg:d_FRI instead.")
  (d_FRI m))

(cl:ensure-generic-function 'f_FRI-val :lambda-list '(m))
(cl:defmethod f_FRI-val ((m <CartesianImpedancePoint>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader lwr_controllers-msg:f_FRI-val is deprecated.  Use lwr_controllers-msg:f_FRI instead.")
  (f_FRI m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <CartesianImpedancePoint>) ostream)
  "Serializes a message object of type '<CartesianImpedancePoint>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'header) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'x_FRI) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'k_FRI) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'd_FRI) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'f_FRI) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <CartesianImpedancePoint>) istream)
  "Deserializes a message object of type '<CartesianImpedancePoint>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'header) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'x_FRI) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'k_FRI) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'd_FRI) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'f_FRI) istream)
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<CartesianImpedancePoint>)))
  "Returns string type for a message object of type '<CartesianImpedancePoint>"
  "lwr_controllers/CartesianImpedancePoint")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'CartesianImpedancePoint)))
  "Returns string type for a message object of type 'CartesianImpedancePoint"
  "lwr_controllers/CartesianImpedancePoint")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<CartesianImpedancePoint>)))
  "Returns md5sum for a message object of type '<CartesianImpedancePoint>"
  "71b8c728a99ddb73ba603776d4733a5f")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'CartesianImpedancePoint)))
  "Returns md5sum for a message object of type 'CartesianImpedancePoint"
  "71b8c728a99ddb73ba603776d4733a5f")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<CartesianImpedancePoint>)))
  "Returns full string definition for message of type '<CartesianImpedancePoint>"
  (cl:format cl:nil "std_msgs/Header header~%# 1. If frame_id in header is NOT EMPTY, then x_FRI is considered to be the pose w.r.t. that frame, so the increment w.r.t. the current tip pose will be computed internally (in the teach pendant is equivalent to select the Cartesian increments to be in the WORLD frame) ~%# 2. If frame_id in header is EMPTY, then x_FRI is considered to be the pose w.r.t. to the current tip pose (in the teach pendant is equivalent to select the Cartesian increments to be in the TOOL frame)~%# The increment (or offset) is x_FRI~%geometry_msgs/Pose x_FRI~%# The stiffness, damping and wrench are expressed in the current tip frame readed in the HWiface~%lwr_controllers/Stiffness k_FRI~%lwr_controllers/Stiffness d_FRI~%geometry_msgs/Wrench f_FRI~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%================================================================================~%MSG: geometry_msgs/Pose~%# A representation of pose in free space, composed of position and orientation. ~%Point position~%Quaternion orientation~%~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%================================================================================~%MSG: geometry_msgs/Quaternion~%# This represents an orientation in free space in quaternion form.~%~%float64 x~%float64 y~%float64 z~%float64 w~%~%================================================================================~%MSG: lwr_controllers/Stiffness~%# This represents a diagonal Cartesian stiffness~%# It is motivated by the KDL class: http://people.mech.kuleuven.be/~~rsmits/kdl/api/html/classKDL_1_1Stiffness.html~%# The conversion would be straight-forward, however, a generic 6D stiffness matrix would be desirable~%~%float64 x~%float64 y~%float64 z~%float64 rx~%float64 ry~%float64 rz~%================================================================================~%MSG: geometry_msgs/Wrench~%# This represents force in free space, separated into~%# its linear and angular parts.~%Vector3  force~%Vector3  torque~%~%================================================================================~%MSG: geometry_msgs/Vector3~%# This represents a vector in free space. ~%# It is only meant to represent a direction. Therefore, it does not~%# make sense to apply a translation to it (e.g., when applying a ~%# generic rigid transformation to a Vector3, tf2 will only apply the~%# rotation). If you want your data to be translatable too, use the~%# geometry_msgs/Point message instead.~%~%float64 x~%float64 y~%float64 z~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'CartesianImpedancePoint)))
  "Returns full string definition for message of type 'CartesianImpedancePoint"
  (cl:format cl:nil "std_msgs/Header header~%# 1. If frame_id in header is NOT EMPTY, then x_FRI is considered to be the pose w.r.t. that frame, so the increment w.r.t. the current tip pose will be computed internally (in the teach pendant is equivalent to select the Cartesian increments to be in the WORLD frame) ~%# 2. If frame_id in header is EMPTY, then x_FRI is considered to be the pose w.r.t. to the current tip pose (in the teach pendant is equivalent to select the Cartesian increments to be in the TOOL frame)~%# The increment (or offset) is x_FRI~%geometry_msgs/Pose x_FRI~%# The stiffness, damping and wrench are expressed in the current tip frame readed in the HWiface~%lwr_controllers/Stiffness k_FRI~%lwr_controllers/Stiffness d_FRI~%geometry_msgs/Wrench f_FRI~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%================================================================================~%MSG: geometry_msgs/Pose~%# A representation of pose in free space, composed of position and orientation. ~%Point position~%Quaternion orientation~%~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%================================================================================~%MSG: geometry_msgs/Quaternion~%# This represents an orientation in free space in quaternion form.~%~%float64 x~%float64 y~%float64 z~%float64 w~%~%================================================================================~%MSG: lwr_controllers/Stiffness~%# This represents a diagonal Cartesian stiffness~%# It is motivated by the KDL class: http://people.mech.kuleuven.be/~~rsmits/kdl/api/html/classKDL_1_1Stiffness.html~%# The conversion would be straight-forward, however, a generic 6D stiffness matrix would be desirable~%~%float64 x~%float64 y~%float64 z~%float64 rx~%float64 ry~%float64 rz~%================================================================================~%MSG: geometry_msgs/Wrench~%# This represents force in free space, separated into~%# its linear and angular parts.~%Vector3  force~%Vector3  torque~%~%================================================================================~%MSG: geometry_msgs/Vector3~%# This represents a vector in free space. ~%# It is only meant to represent a direction. Therefore, it does not~%# make sense to apply a translation to it (e.g., when applying a ~%# generic rigid transformation to a Vector3, tf2 will only apply the~%# rotation). If you want your data to be translatable too, use the~%# geometry_msgs/Point message instead.~%~%float64 x~%float64 y~%float64 z~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <CartesianImpedancePoint>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'header))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'x_FRI))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'k_FRI))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'd_FRI))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'f_FRI))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <CartesianImpedancePoint>))
  "Converts a ROS message object to a list"
  (cl:list 'CartesianImpedancePoint
    (cl:cons ':header (header msg))
    (cl:cons ':x_FRI (x_FRI msg))
    (cl:cons ':k_FRI (k_FRI msg))
    (cl:cons ':d_FRI (d_FRI msg))
    (cl:cons ':f_FRI (f_FRI msg))
))
