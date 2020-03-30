;; Auto-generated. Do not edit!


(when (boundp 'lwr_controllers::SetCartesianImpedanceCommand)
  (if (not (find-package "LWR_CONTROLLERS"))
    (make-package "LWR_CONTROLLERS"))
  (shadow 'SetCartesianImpedanceCommand (find-package "LWR_CONTROLLERS")))
(unless (find-package "LWR_CONTROLLERS::SETCARTESIANIMPEDANCECOMMAND")
  (make-package "LWR_CONTROLLERS::SETCARTESIANIMPEDANCECOMMAND"))
(unless (find-package "LWR_CONTROLLERS::SETCARTESIANIMPEDANCECOMMANDREQUEST")
  (make-package "LWR_CONTROLLERS::SETCARTESIANIMPEDANCECOMMANDREQUEST"))
(unless (find-package "LWR_CONTROLLERS::SETCARTESIANIMPEDANCECOMMANDRESPONSE")
  (make-package "LWR_CONTROLLERS::SETCARTESIANIMPEDANCECOMMANDRESPONSE"))

(in-package "ROS")





(defclass lwr_controllers::SetCartesianImpedanceCommandRequest
  :super ros::object
  :slots (_command ))

(defmethod lwr_controllers::SetCartesianImpedanceCommandRequest
  (:init
   (&key
    ((:command __command) (instance lwr_controllers::CartesianImpedancePoint :init))
    )
   (send-super :init)
   (setq _command __command)
   self)
  (:command
   (&rest __command)
   (if (keywordp (car __command))
       (send* _command __command)
     (progn
       (if __command (setq _command (car __command)))
       _command)))
  (:serialization-length
   ()
   (+
    ;; lwr_controllers/CartesianImpedancePoint _command
    (send _command :serialization-length)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; lwr_controllers/CartesianImpedancePoint _command
       (send _command :serialize s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; lwr_controllers/CartesianImpedancePoint _command
     (send _command :deserialize buf ptr-) (incf ptr- (send _command :serialization-length))
   ;;
   self)
  )

(defclass lwr_controllers::SetCartesianImpedanceCommandResponse
  :super ros::object
  :slots ())

(defmethod lwr_controllers::SetCartesianImpedanceCommandResponse
  (:init
   (&key
    )
   (send-super :init)
   self)
  (:serialization-length
   ()
   (+
    0
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;;
   self)
  )

(defclass lwr_controllers::SetCartesianImpedanceCommand
  :super ros::object
  :slots ())

(setf (get lwr_controllers::SetCartesianImpedanceCommand :md5sum-) "cc36264319f44d204c2ace0744aa21ee")
(setf (get lwr_controllers::SetCartesianImpedanceCommand :datatype-) "lwr_controllers/SetCartesianImpedanceCommand")
(setf (get lwr_controllers::SetCartesianImpedanceCommand :request) lwr_controllers::SetCartesianImpedanceCommandRequest)
(setf (get lwr_controllers::SetCartesianImpedanceCommand :response) lwr_controllers::SetCartesianImpedanceCommandResponse)

(defmethod lwr_controllers::SetCartesianImpedanceCommandRequest
  (:response () (instance lwr_controllers::SetCartesianImpedanceCommandResponse :init)))

(setf (get lwr_controllers::SetCartesianImpedanceCommandRequest :md5sum-) "cc36264319f44d204c2ace0744aa21ee")
(setf (get lwr_controllers::SetCartesianImpedanceCommandRequest :datatype-) "lwr_controllers/SetCartesianImpedanceCommandRequest")
(setf (get lwr_controllers::SetCartesianImpedanceCommandRequest :definition-)
      "lwr_controllers/CartesianImpedancePoint command

================================================================================
MSG: lwr_controllers/CartesianImpedancePoint
std_msgs/Header header
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
---
")

(setf (get lwr_controllers::SetCartesianImpedanceCommandResponse :md5sum-) "cc36264319f44d204c2ace0744aa21ee")
(setf (get lwr_controllers::SetCartesianImpedanceCommandResponse :datatype-) "lwr_controllers/SetCartesianImpedanceCommandResponse")
(setf (get lwr_controllers::SetCartesianImpedanceCommandResponse :definition-)
      "lwr_controllers/CartesianImpedancePoint command

================================================================================
MSG: lwr_controllers/CartesianImpedancePoint
std_msgs/Header header
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
---
")



(provide :lwr_controllers/SetCartesianImpedanceCommand "cc36264319f44d204c2ace0744aa21ee")


