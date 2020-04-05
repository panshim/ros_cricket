; Auto-generated. Do not edit!


(cl:in-package lwr_controllers-srv)


;//! \htmlinclude SetCartesianImpedanceCommand-request.msg.html

(cl:defclass <SetCartesianImpedanceCommand-request> (roslisp-msg-protocol:ros-message)
  ((command
    :reader command
    :initarg :command
    :type lwr_controllers-msg:CartesianImpedancePoint
    :initform (cl:make-instance 'lwr_controllers-msg:CartesianImpedancePoint)))
)

(cl:defclass SetCartesianImpedanceCommand-request (<SetCartesianImpedanceCommand-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <SetCartesianImpedanceCommand-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'SetCartesianImpedanceCommand-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name lwr_controllers-srv:<SetCartesianImpedanceCommand-request> is deprecated: use lwr_controllers-srv:SetCartesianImpedanceCommand-request instead.")))

(cl:ensure-generic-function 'command-val :lambda-list '(m))
(cl:defmethod command-val ((m <SetCartesianImpedanceCommand-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader lwr_controllers-srv:command-val is deprecated.  Use lwr_controllers-srv:command instead.")
  (command m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <SetCartesianImpedanceCommand-request>) ostream)
  "Serializes a message object of type '<SetCartesianImpedanceCommand-request>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'command) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <SetCartesianImpedanceCommand-request>) istream)
  "Deserializes a message object of type '<SetCartesianImpedanceCommand-request>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'command) istream)
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<SetCartesianImpedanceCommand-request>)))
  "Returns string type for a service object of type '<SetCartesianImpedanceCommand-request>"
  "lwr_controllers/SetCartesianImpedanceCommandRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'SetCartesianImpedanceCommand-request)))
  "Returns string type for a service object of type 'SetCartesianImpedanceCommand-request"
  "lwr_controllers/SetCartesianImpedanceCommandRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<SetCartesianImpedanceCommand-request>)))
  "Returns md5sum for a message object of type '<SetCartesianImpedanceCommand-request>"
  "cc36264319f44d204c2ace0744aa21ee")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'SetCartesianImpedanceCommand-request)))
  "Returns md5sum for a message object of type 'SetCartesianImpedanceCommand-request"
  "cc36264319f44d204c2ace0744aa21ee")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<SetCartesianImpedanceCommand-request>)))
  "Returns full string definition for message of type '<SetCartesianImpedanceCommand-request>"
  (cl:format cl:nil "lwr_controllers/CartesianImpedancePoint command~%~%================================================================================~%MSG: lwr_controllers/CartesianImpedancePoint~%std_msgs/Header header~%# 1. If frame_id in header is NOT EMPTY, then x_FRI is considered to be the pose w.r.t. that frame, so the increment w.r.t. the current tip pose will be computed internally (in the teach pendant is equivalent to select the Cartesian increments to be in the WORLD frame) ~%# 2. If frame_id in header is EMPTY, then x_FRI is considered to be the pose w.r.t. to the current tip pose (in the teach pendant is equivalent to select the Cartesian increments to be in the TOOL frame)~%# The increment (or offset) is x_FRI~%geometry_msgs/Pose x_FRI~%# The stiffness, damping and wrench are expressed in the current tip frame readed in the HWiface~%lwr_controllers/Stiffness k_FRI~%lwr_controllers/Stiffness d_FRI~%geometry_msgs/Wrench f_FRI~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%================================================================================~%MSG: geometry_msgs/Pose~%# A representation of pose in free space, composed of position and orientation. ~%Point position~%Quaternion orientation~%~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%================================================================================~%MSG: geometry_msgs/Quaternion~%# This represents an orientation in free space in quaternion form.~%~%float64 x~%float64 y~%float64 z~%float64 w~%~%================================================================================~%MSG: lwr_controllers/Stiffness~%# This represents a diagonal Cartesian stiffness~%# It is motivated by the KDL class: http://people.mech.kuleuven.be/~~rsmits/kdl/api/html/classKDL_1_1Stiffness.html~%# The conversion would be straight-forward, however, a generic 6D stiffness matrix would be desirable~%~%float64 x~%float64 y~%float64 z~%float64 rx~%float64 ry~%float64 rz~%================================================================================~%MSG: geometry_msgs/Wrench~%# This represents force in free space, separated into~%# its linear and angular parts.~%Vector3  force~%Vector3  torque~%~%================================================================================~%MSG: geometry_msgs/Vector3~%# This represents a vector in free space. ~%# It is only meant to represent a direction. Therefore, it does not~%# make sense to apply a translation to it (e.g., when applying a ~%# generic rigid transformation to a Vector3, tf2 will only apply the~%# rotation). If you want your data to be translatable too, use the~%# geometry_msgs/Point message instead.~%~%float64 x~%float64 y~%float64 z~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'SetCartesianImpedanceCommand-request)))
  "Returns full string definition for message of type 'SetCartesianImpedanceCommand-request"
  (cl:format cl:nil "lwr_controllers/CartesianImpedancePoint command~%~%================================================================================~%MSG: lwr_controllers/CartesianImpedancePoint~%std_msgs/Header header~%# 1. If frame_id in header is NOT EMPTY, then x_FRI is considered to be the pose w.r.t. that frame, so the increment w.r.t. the current tip pose will be computed internally (in the teach pendant is equivalent to select the Cartesian increments to be in the WORLD frame) ~%# 2. If frame_id in header is EMPTY, then x_FRI is considered to be the pose w.r.t. to the current tip pose (in the teach pendant is equivalent to select the Cartesian increments to be in the TOOL frame)~%# The increment (or offset) is x_FRI~%geometry_msgs/Pose x_FRI~%# The stiffness, damping and wrench are expressed in the current tip frame readed in the HWiface~%lwr_controllers/Stiffness k_FRI~%lwr_controllers/Stiffness d_FRI~%geometry_msgs/Wrench f_FRI~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%================================================================================~%MSG: geometry_msgs/Pose~%# A representation of pose in free space, composed of position and orientation. ~%Point position~%Quaternion orientation~%~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%================================================================================~%MSG: geometry_msgs/Quaternion~%# This represents an orientation in free space in quaternion form.~%~%float64 x~%float64 y~%float64 z~%float64 w~%~%================================================================================~%MSG: lwr_controllers/Stiffness~%# This represents a diagonal Cartesian stiffness~%# It is motivated by the KDL class: http://people.mech.kuleuven.be/~~rsmits/kdl/api/html/classKDL_1_1Stiffness.html~%# The conversion would be straight-forward, however, a generic 6D stiffness matrix would be desirable~%~%float64 x~%float64 y~%float64 z~%float64 rx~%float64 ry~%float64 rz~%================================================================================~%MSG: geometry_msgs/Wrench~%# This represents force in free space, separated into~%# its linear and angular parts.~%Vector3  force~%Vector3  torque~%~%================================================================================~%MSG: geometry_msgs/Vector3~%# This represents a vector in free space. ~%# It is only meant to represent a direction. Therefore, it does not~%# make sense to apply a translation to it (e.g., when applying a ~%# generic rigid transformation to a Vector3, tf2 will only apply the~%# rotation). If you want your data to be translatable too, use the~%# geometry_msgs/Point message instead.~%~%float64 x~%float64 y~%float64 z~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <SetCartesianImpedanceCommand-request>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'command))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <SetCartesianImpedanceCommand-request>))
  "Converts a ROS message object to a list"
  (cl:list 'SetCartesianImpedanceCommand-request
    (cl:cons ':command (command msg))
))
;//! \htmlinclude SetCartesianImpedanceCommand-response.msg.html

(cl:defclass <SetCartesianImpedanceCommand-response> (roslisp-msg-protocol:ros-message)
  ()
)

(cl:defclass SetCartesianImpedanceCommand-response (<SetCartesianImpedanceCommand-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <SetCartesianImpedanceCommand-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'SetCartesianImpedanceCommand-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name lwr_controllers-srv:<SetCartesianImpedanceCommand-response> is deprecated: use lwr_controllers-srv:SetCartesianImpedanceCommand-response instead.")))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <SetCartesianImpedanceCommand-response>) ostream)
  "Serializes a message object of type '<SetCartesianImpedanceCommand-response>"
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <SetCartesianImpedanceCommand-response>) istream)
  "Deserializes a message object of type '<SetCartesianImpedanceCommand-response>"
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<SetCartesianImpedanceCommand-response>)))
  "Returns string type for a service object of type '<SetCartesianImpedanceCommand-response>"
  "lwr_controllers/SetCartesianImpedanceCommandResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'SetCartesianImpedanceCommand-response)))
  "Returns string type for a service object of type 'SetCartesianImpedanceCommand-response"
  "lwr_controllers/SetCartesianImpedanceCommandResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<SetCartesianImpedanceCommand-response>)))
  "Returns md5sum for a message object of type '<SetCartesianImpedanceCommand-response>"
  "cc36264319f44d204c2ace0744aa21ee")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'SetCartesianImpedanceCommand-response)))
  "Returns md5sum for a message object of type 'SetCartesianImpedanceCommand-response"
  "cc36264319f44d204c2ace0744aa21ee")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<SetCartesianImpedanceCommand-response>)))
  "Returns full string definition for message of type '<SetCartesianImpedanceCommand-response>"
  (cl:format cl:nil "~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'SetCartesianImpedanceCommand-response)))
  "Returns full string definition for message of type 'SetCartesianImpedanceCommand-response"
  (cl:format cl:nil "~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <SetCartesianImpedanceCommand-response>))
  (cl:+ 0
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <SetCartesianImpedanceCommand-response>))
  "Converts a ROS message object to a list"
  (cl:list 'SetCartesianImpedanceCommand-response
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'SetCartesianImpedanceCommand)))
  'SetCartesianImpedanceCommand-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'SetCartesianImpedanceCommand)))
  'SetCartesianImpedanceCommand-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'SetCartesianImpedanceCommand)))
  "Returns string type for a service object of type '<SetCartesianImpedanceCommand>"
  "lwr_controllers/SetCartesianImpedanceCommand")