; Auto-generated. Do not edit!


(cl:in-package lwr_controllers-msg)


;//! \htmlinclude ArmState.msg.html

(cl:defclass <ArmState> (roslisp-msg-protocol:ros-message)
  ((header
    :reader header
    :initarg :header
    :type std_msgs-msg:Header
    :initform (cl:make-instance 'std_msgs-msg:Header))
   (joint_name
    :reader joint_name
    :initarg :joint_name
    :type (cl:vector cl:string)
   :initform (cl:make-array 0 :element-type 'cl:string :initial-element ""))
   (est_ext_torques
    :reader est_ext_torques
    :initarg :est_ext_torques
    :type (cl:vector cl:float)
   :initform (cl:make-array 0 :element-type 'cl:float :initial-element 0.0))
   (est_ee_wrench
    :reader est_ee_wrench
    :initarg :est_ee_wrench
    :type geometry_msgs-msg:Wrench
    :initform (cl:make-instance 'geometry_msgs-msg:Wrench))
   (est_ee_wrench_base
    :reader est_ee_wrench_base
    :initarg :est_ee_wrench_base
    :type geometry_msgs-msg:Wrench
    :initform (cl:make-instance 'geometry_msgs-msg:Wrench)))
)

(cl:defclass ArmState (<ArmState>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <ArmState>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'ArmState)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name lwr_controllers-msg:<ArmState> is deprecated: use lwr_controllers-msg:ArmState instead.")))

(cl:ensure-generic-function 'header-val :lambda-list '(m))
(cl:defmethod header-val ((m <ArmState>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader lwr_controllers-msg:header-val is deprecated.  Use lwr_controllers-msg:header instead.")
  (header m))

(cl:ensure-generic-function 'joint_name-val :lambda-list '(m))
(cl:defmethod joint_name-val ((m <ArmState>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader lwr_controllers-msg:joint_name-val is deprecated.  Use lwr_controllers-msg:joint_name instead.")
  (joint_name m))

(cl:ensure-generic-function 'est_ext_torques-val :lambda-list '(m))
(cl:defmethod est_ext_torques-val ((m <ArmState>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader lwr_controllers-msg:est_ext_torques-val is deprecated.  Use lwr_controllers-msg:est_ext_torques instead.")
  (est_ext_torques m))

(cl:ensure-generic-function 'est_ee_wrench-val :lambda-list '(m))
(cl:defmethod est_ee_wrench-val ((m <ArmState>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader lwr_controllers-msg:est_ee_wrench-val is deprecated.  Use lwr_controllers-msg:est_ee_wrench instead.")
  (est_ee_wrench m))

(cl:ensure-generic-function 'est_ee_wrench_base-val :lambda-list '(m))
(cl:defmethod est_ee_wrench_base-val ((m <ArmState>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader lwr_controllers-msg:est_ee_wrench_base-val is deprecated.  Use lwr_controllers-msg:est_ee_wrench_base instead.")
  (est_ee_wrench_base m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <ArmState>) ostream)
  "Serializes a message object of type '<ArmState>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'header) ostream)
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'joint_name))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (cl:let ((__ros_str_len (cl:length ele)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) ele))
   (cl:slot-value msg 'joint_name))
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'est_ext_torques))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (cl:let ((bits (roslisp-utils:encode-single-float-bits ele)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)))
   (cl:slot-value msg 'est_ext_torques))
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'est_ee_wrench) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'est_ee_wrench_base) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <ArmState>) istream)
  "Deserializes a message object of type '<ArmState>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'header) istream)
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'joint_name) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'joint_name)))
    (cl:dotimes (i __ros_arr_len)
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:aref vals i) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:aref vals i) __ros_str_idx) (cl:code-char (cl:read-byte istream))))))))
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'est_ext_torques) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'est_ext_torques)))
    (cl:dotimes (i __ros_arr_len)
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:aref vals i) (roslisp-utils:decode-single-float-bits bits))))))
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'est_ee_wrench) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'est_ee_wrench_base) istream)
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<ArmState>)))
  "Returns string type for a message object of type '<ArmState>"
  "lwr_controllers/ArmState")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'ArmState)))
  "Returns string type for a message object of type 'ArmState"
  "lwr_controllers/ArmState")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<ArmState>)))
  "Returns md5sum for a message object of type '<ArmState>"
  "1ec4005eded14deb32698c63aa479d03")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'ArmState)))
  "Returns md5sum for a message object of type 'ArmState"
  "1ec4005eded14deb32698c63aa479d03")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<ArmState>)))
  "Returns full string definition for message of type '<ArmState>"
  (cl:format cl:nil "Header header~%~%string[] joint_name~%float32[] est_ext_torques~%geometry_msgs/Wrench est_ee_wrench~%geometry_msgs/Wrench est_ee_wrench_base~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%================================================================================~%MSG: geometry_msgs/Wrench~%# This represents force in free space, separated into~%# its linear and angular parts.~%Vector3  force~%Vector3  torque~%~%================================================================================~%MSG: geometry_msgs/Vector3~%# This represents a vector in free space. ~%# It is only meant to represent a direction. Therefore, it does not~%# make sense to apply a translation to it (e.g., when applying a ~%# generic rigid transformation to a Vector3, tf2 will only apply the~%# rotation). If you want your data to be translatable too, use the~%# geometry_msgs/Point message instead.~%~%float64 x~%float64 y~%float64 z~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'ArmState)))
  "Returns full string definition for message of type 'ArmState"
  (cl:format cl:nil "Header header~%~%string[] joint_name~%float32[] est_ext_torques~%geometry_msgs/Wrench est_ee_wrench~%geometry_msgs/Wrench est_ee_wrench_base~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%================================================================================~%MSG: geometry_msgs/Wrench~%# This represents force in free space, separated into~%# its linear and angular parts.~%Vector3  force~%Vector3  torque~%~%================================================================================~%MSG: geometry_msgs/Vector3~%# This represents a vector in free space. ~%# It is only meant to represent a direction. Therefore, it does not~%# make sense to apply a translation to it (e.g., when applying a ~%# generic rigid transformation to a Vector3, tf2 will only apply the~%# rotation). If you want your data to be translatable too, use the~%# geometry_msgs/Point message instead.~%~%float64 x~%float64 y~%float64 z~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <ArmState>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'header))
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'joint_name) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 4 (cl:length ele))))
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'est_ext_torques) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 4)))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'est_ee_wrench))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'est_ee_wrench_base))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <ArmState>))
  "Converts a ROS message object to a list"
  (cl:list 'ArmState
    (cl:cons ':header (header msg))
    (cl:cons ':joint_name (joint_name msg))
    (cl:cons ':est_ext_torques (est_ext_torques msg))
    (cl:cons ':est_ee_wrench (est_ee_wrench msg))
    (cl:cons ':est_ee_wrench_base (est_ee_wrench_base msg))
))
