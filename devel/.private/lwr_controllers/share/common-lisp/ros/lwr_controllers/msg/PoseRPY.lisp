; Auto-generated. Do not edit!


(cl:in-package lwr_controllers-msg)


;//! \htmlinclude PoseRPY.msg.html

(cl:defclass <PoseRPY> (roslisp-msg-protocol:ros-message)
  ((id
    :reader id
    :initarg :id
    :type cl:integer
    :initform 0)
   (position
    :reader position
    :initarg :position
    :type geometry_msgs-msg:Vector3
    :initform (cl:make-instance 'geometry_msgs-msg:Vector3))
   (orientation
    :reader orientation
    :initarg :orientation
    :type lwr_controllers-msg:RPY
    :initform (cl:make-instance 'lwr_controllers-msg:RPY)))
)

(cl:defclass PoseRPY (<PoseRPY>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <PoseRPY>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'PoseRPY)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name lwr_controllers-msg:<PoseRPY> is deprecated: use lwr_controllers-msg:PoseRPY instead.")))

(cl:ensure-generic-function 'id-val :lambda-list '(m))
(cl:defmethod id-val ((m <PoseRPY>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader lwr_controllers-msg:id-val is deprecated.  Use lwr_controllers-msg:id instead.")
  (id m))

(cl:ensure-generic-function 'position-val :lambda-list '(m))
(cl:defmethod position-val ((m <PoseRPY>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader lwr_controllers-msg:position-val is deprecated.  Use lwr_controllers-msg:position instead.")
  (position m))

(cl:ensure-generic-function 'orientation-val :lambda-list '(m))
(cl:defmethod orientation-val ((m <PoseRPY>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader lwr_controllers-msg:orientation-val is deprecated.  Use lwr_controllers-msg:orientation instead.")
  (orientation m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <PoseRPY>) ostream)
  "Serializes a message object of type '<PoseRPY>"
  (cl:let* ((signed (cl:slot-value msg 'id)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'position) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'orientation) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <PoseRPY>) istream)
  "Deserializes a message object of type '<PoseRPY>"
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'id) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'position) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'orientation) istream)
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<PoseRPY>)))
  "Returns string type for a message object of type '<PoseRPY>"
  "lwr_controllers/PoseRPY")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'PoseRPY)))
  "Returns string type for a message object of type 'PoseRPY"
  "lwr_controllers/PoseRPY")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<PoseRPY>)))
  "Returns md5sum for a message object of type '<PoseRPY>"
  "ac4defc6a342778de62991685c2a0dda")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'PoseRPY)))
  "Returns md5sum for a message object of type 'PoseRPY"
  "ac4defc6a342778de62991685c2a0dda")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<PoseRPY>)))
  "Returns full string definition for message of type '<PoseRPY>"
  (cl:format cl:nil "#include <lwr_controllers/RPY.h>~%~%int32 id~%geometry_msgs/Vector3 position~%RPY orientation~%~%================================================================================~%MSG: geometry_msgs/Vector3~%# This represents a vector in free space. ~%# It is only meant to represent a direction. Therefore, it does not~%# make sense to apply a translation to it (e.g., when applying a ~%# generic rigid transformation to a Vector3, tf2 will only apply the~%# rotation). If you want your data to be translatable too, use the~%# geometry_msgs/Point message instead.~%~%float64 x~%float64 y~%float64 z~%================================================================================~%MSG: lwr_controllers/RPY~%float64 roll~%float64 pitch~%float64 yaw~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'PoseRPY)))
  "Returns full string definition for message of type 'PoseRPY"
  (cl:format cl:nil "#include <lwr_controllers/RPY.h>~%~%int32 id~%geometry_msgs/Vector3 position~%RPY orientation~%~%================================================================================~%MSG: geometry_msgs/Vector3~%# This represents a vector in free space. ~%# It is only meant to represent a direction. Therefore, it does not~%# make sense to apply a translation to it (e.g., when applying a ~%# generic rigid transformation to a Vector3, tf2 will only apply the~%# rotation). If you want your data to be translatable too, use the~%# geometry_msgs/Point message instead.~%~%float64 x~%float64 y~%float64 z~%================================================================================~%MSG: lwr_controllers/RPY~%float64 roll~%float64 pitch~%float64 yaw~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <PoseRPY>))
  (cl:+ 0
     4
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'position))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'orientation))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <PoseRPY>))
  "Converts a ROS message object to a list"
  (cl:list 'PoseRPY
    (cl:cons ':id (id msg))
    (cl:cons ':position (position msg))
    (cl:cons ':orientation (orientation msg))
))
