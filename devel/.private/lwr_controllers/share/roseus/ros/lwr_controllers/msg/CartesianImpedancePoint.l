;; Auto-generated. Do not edit!


(when (boundp 'lwr_controllers::CartesianImpedancePoint)
  (if (not (find-package "LWR_CONTROLLERS"))
    (make-package "LWR_CONTROLLERS"))
  (shadow 'CartesianImpedancePoint (find-package "LWR_CONTROLLERS")))
(unless (find-package "LWR_CONTROLLERS::CARTESIANIMPEDANCEPOINT")
  (make-package "LWR_CONTROLLERS::CARTESIANIMPEDANCEPOINT"))

(in-package "ROS")
;;//! \htmlinclude CartesianImpedancePoint.msg.html
(if (not (find-package "GEOMETRY_MSGS"))
  (ros::roseus-add-msgs "geometry_msgs"))
(if (not (find-package "STD_MSGS"))
  (ros::roseus-add-msgs "std_msgs"))


(defclass lwr_controllers::CartesianImpedancePoint
  :super ros::object
  :slots (_header _x_FRI _k_FRI _d_FRI _f_FRI ))

(defmethod lwr_controllers::CartesianImpedancePoint
  (:init
   (&key
    ((:header __header) (instance std_msgs::Header :init))
    ((:x_FRI __x_FRI) (instance geometry_msgs::Pose :init))
    ((:k_FRI __k_FRI) (instance lwr_controllers::Stiffness :init))
    ((:d_FRI __d_FRI) (instance lwr_controllers::Stiffness :init))
    ((:f_FRI __f_FRI) (instance geometry_msgs::Wrench :init))
    )
   (send-super :init)
   (setq _header __header)
   (setq _x_FRI __x_FRI)
   (setq _k_FRI __k_FRI)
   (setq _d_FRI __d_FRI)
   (setq _f_FRI __f_FRI)
   self)
  (:header
   (&rest __header)
   (if (keywordp (car __header))
       (send* _header __header)
     (progn
       (if __header (setq _header (car __header)))
       _header)))
  (:x_FRI
   (&rest __x_FRI)
   (if (keywordp (car __x_FRI))
       (send* _x_FRI __x_FRI)
     (progn
       (if __x_FRI (setq _x_FRI (car __x_FRI)))
       _x_FRI)))
  (:k_FRI
   (&rest __k_FRI)
   (if (keywordp (car __k_FRI))
       (send* _k_FRI __k_FRI)
     (progn
       (if __k_FRI (setq _k_FRI (car __k_FRI)))
       _k_FRI)))
  (:d_FRI
   (&rest __d_FRI)
   (if (keywordp (car __d_FRI))
       (send* _d_FRI __d_FRI)
     (progn
       (if __d_FRI (setq _d_FRI (car __d_FRI)))
       _d_FRI)))
  (:f_FRI
   (&rest __f_FRI)
   (if (keywordp (car __f_FRI))
       (send* _f_FRI __f_FRI)
     (progn
       (if __f_FRI (setq _f_FRI (car __f_FRI)))
       _f_FRI)))
  (:serialization-length
   ()
   (+
    ;; std_msgs/Header _header
    (send _header :serialization-length)
    ;; geometry_msgs/Pose _x_FRI
    (send _x_FRI :serialization-length)
    ;; lwr_controllers/Stiffness _k_FRI
    (send _k_FRI :serialization-length)
    ;; lwr_controllers/Stiffness _d_FRI
    (send _d_FRI :serialization-length)
    ;; geometry_msgs/Wrench _f_FRI
    (send _f_FRI :serialization-length)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; std_msgs/Header _header
       (send _header :serialize s)
     ;; geometry_msgs/Pose _x_FRI
       (send _x_FRI :serialize s)
     ;; lwr_controllers/Stiffness _k_FRI
       (send _k_FRI :serialize s)
     ;; lwr_controllers/Stiffness _d_FRI
       (send _d_FRI :serialize s)
     ;; geometry_msgs/Wrench _f_FRI
       (send _f_FRI :serialize s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; std_msgs/Header _header
     (send _header :deserialize buf ptr-) (incf ptr- (send _header :serialization-length))
   ;; geometry_msgs/Pose _x_FRI
     (send _x_FRI :deserialize buf ptr-) (incf ptr- (send _x_FRI :serialization-length))
   ;; lwr_controllers/Stiffness _k_FRI
     (send _k_FRI :deserialize buf ptr-) (incf ptr- (send _k_FRI :serialization-length))
   ;; lwr_controllers/Stiffness _d_FRI
     (send _d_FRI :deserialize buf ptr-) (incf ptr- (send _d_FRI :serialization-length))
   ;; geometry_msgs/Wrench _f_FRI
     (send _f_FRI :deserialize buf ptr-) (incf ptr- (send _f_FRI :serialization-length))
   ;;
   self)
  )

(setf (get lwr_controllers::CartesianImpedancePoint :md5sum-) "71b8c728a99ddb73ba603776d4733a5f")
(setf (get lwr_controllers::CartesianImpedancePoint :datatype-) "lwr_controllers/CartesianImpedancePoint")
(setf (get lwr_controllers::CartesianImpedancePoint :definition-)
      "std_msgs/Header header
# 1. If frame_id in header is NOT EMPTY, then x_FRI is considered to be the pose w.r.t. that frame, so the increment w.r.t. the current tip pose will be computed internally (in the teach pendant is equivalent to select the Cartesian increments to be in the WORLD frame) 
# 2. If frame_id in header is EMPTY, then x_FRI is considered to be the pose w.r.t. to the current tip pose (in the teach pendant is equivalent to select the Cartesian increments to be in the TOOL frame)
# The increment (or offset) is x_FRI
geometry_msgs/Pose x_FRI
# The stiffness, damping and wrench are expressed in the current tip frame readed in the HWiface
lwr_controllers/Stiffness k_FRI
lwr_controllers/Stiffness d_FRI
geometry_msgs/Wrench f_FRI
================================================================================
MSG: std_msgs/Header
# Standard metadata for higher-level stamped data types.
# This is generally used to communicate timestamped data 
# in a particular coordinate frame.
# 
# sequence ID: consecutively increasing ID 
uint32 seq
#Two-integer timestamp that is expressed as:
# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')
# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')
# time-handling sugar is provided by the client library
time stamp
#Frame this data is associated with
# 0: no frame
# 1: global frame
string frame_id

================================================================================
MSG: geometry_msgs/Pose
# A representation of pose in free space, composed of position and orientation. 
Point position
Quaternion orientation

================================================================================
MSG: geometry_msgs/Point
# This contains the position of a point in free space
float64 x
float64 y
float64 z

================================================================================
MSG: geometry_msgs/Quaternion
# This represents an orientation in free space in quaternion form.

float64 x
float64 y
float64 z
float64 w

================================================================================
MSG: lwr_controllers/Stiffness
# This represents a diagonal Cartesian stiffness
# It is motivated by the KDL class: http://people.mech.kuleuven.be/~rsmits/kdl/api/html/classKDL_1_1Stiffness.html
# The conversion would be straight-forward, however, a generic 6D stiffness matrix would be desirable

float64 x
float64 y
float64 z
float64 rx
float64 ry
float64 rz
================================================================================
MSG: geometry_msgs/Wrench
# This represents force in free space, separated into
# its linear and angular parts.
Vector3  force
Vector3  torque

================================================================================
MSG: geometry_msgs/Vector3
# This represents a vector in free space. 
# It is only meant to represent a direction. Therefore, it does not
# make sense to apply a translation to it (e.g., when applying a 
# generic rigid transformation to a Vector3, tf2 will only apply the
# rotation). If you want your data to be translatable too, use the
# geometry_msgs/Point message instead.

float64 x
float64 y
float64 z
")



(provide :lwr_controllers/CartesianImpedancePoint "71b8c728a99ddb73ba603776d4733a5f")


