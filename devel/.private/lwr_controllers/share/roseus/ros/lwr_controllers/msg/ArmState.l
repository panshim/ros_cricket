;; Auto-generated. Do not edit!


(when (boundp 'lwr_controllers::ArmState)
  (if (not (find-package "LWR_CONTROLLERS"))
    (make-package "LWR_CONTROLLERS"))
  (shadow 'ArmState (find-package "LWR_CONTROLLERS")))
(unless (find-package "LWR_CONTROLLERS::ARMSTATE")
  (make-package "LWR_CONTROLLERS::ARMSTATE"))

(in-package "ROS")
;;//! \htmlinclude ArmState.msg.html
(if (not (find-package "GEOMETRY_MSGS"))
  (ros::roseus-add-msgs "geometry_msgs"))
(if (not (find-package "STD_MSGS"))
  (ros::roseus-add-msgs "std_msgs"))


(defclass lwr_controllers::ArmState
  :super ros::object
  :slots (_header _joint_name _est_ext_torques _est_ee_wrench _est_ee_wrench_base ))

(defmethod lwr_controllers::ArmState
  (:init
   (&key
    ((:header __header) (instance std_msgs::Header :init))
    ((:joint_name __joint_name) (let (r) (dotimes (i 0) (push "" r)) r))
    ((:est_ext_torques __est_ext_torques) (make-array 0 :initial-element 0.0 :element-type :float))
    ((:est_ee_wrench __est_ee_wrench) (instance geometry_msgs::Wrench :init))
    ((:est_ee_wrench_base __est_ee_wrench_base) (instance geometry_msgs::Wrench :init))
    )
   (send-super :init)
   (setq _header __header)
   (setq _joint_name __joint_name)
   (setq _est_ext_torques __est_ext_torques)
   (setq _est_ee_wrench __est_ee_wrench)
   (setq _est_ee_wrench_base __est_ee_wrench_base)
   self)
  (:header
   (&rest __header)
   (if (keywordp (car __header))
       (send* _header __header)
     (progn
       (if __header (setq _header (car __header)))
       _header)))
  (:joint_name
   (&optional __joint_name)
   (if __joint_name (setq _joint_name __joint_name)) _joint_name)
  (:est_ext_torques
   (&optional __est_ext_torques)
   (if __est_ext_torques (setq _est_ext_torques __est_ext_torques)) _est_ext_torques)
  (:est_ee_wrench
   (&rest __est_ee_wrench)
   (if (keywordp (car __est_ee_wrench))
       (send* _est_ee_wrench __est_ee_wrench)
     (progn
       (if __est_ee_wrench (setq _est_ee_wrench (car __est_ee_wrench)))
       _est_ee_wrench)))
  (:est_ee_wrench_base
   (&rest __est_ee_wrench_base)
   (if (keywordp (car __est_ee_wrench_base))
       (send* _est_ee_wrench_base __est_ee_wrench_base)
     (progn
       (if __est_ee_wrench_base (setq _est_ee_wrench_base (car __est_ee_wrench_base)))
       _est_ee_wrench_base)))
  (:serialization-length
   ()
   (+
    ;; std_msgs/Header _header
    (send _header :serialization-length)
    ;; string[] _joint_name
    (apply #'+ (mapcar #'(lambda (x) (+ 4 (length x))) _joint_name)) 4
    ;; float32[] _est_ext_torques
    (* 4    (length _est_ext_torques)) 4
    ;; geometry_msgs/Wrench _est_ee_wrench
    (send _est_ee_wrench :serialization-length)
    ;; geometry_msgs/Wrench _est_ee_wrench_base
    (send _est_ee_wrench_base :serialization-length)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; std_msgs/Header _header
       (send _header :serialize s)
     ;; string[] _joint_name
     (write-long (length _joint_name) s)
     (dolist (elem _joint_name)
       (write-long (length elem) s) (princ elem s)
       )
     ;; float32[] _est_ext_torques
     (write-long (length _est_ext_torques) s)
     (dotimes (i (length _est_ext_torques))
       (sys::poke (elt _est_ext_torques i) (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
       )
     ;; geometry_msgs/Wrench _est_ee_wrench
       (send _est_ee_wrench :serialize s)
     ;; geometry_msgs/Wrench _est_ee_wrench_base
       (send _est_ee_wrench_base :serialize s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; std_msgs/Header _header
     (send _header :deserialize buf ptr-) (incf ptr- (send _header :serialization-length))
   ;; string[] _joint_name
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _joint_name (make-list n))
     (dotimes (i n)
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setf (elt _joint_name i) (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
     ))
   ;; float32[] _est_ext_torques
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _est_ext_torques (instantiate float-vector n))
     (dotimes (i n)
     (setf (elt _est_ext_torques i) (sys::peek buf ptr- :float)) (incf ptr- 4)
     ))
   ;; geometry_msgs/Wrench _est_ee_wrench
     (send _est_ee_wrench :deserialize buf ptr-) (incf ptr- (send _est_ee_wrench :serialization-length))
   ;; geometry_msgs/Wrench _est_ee_wrench_base
     (send _est_ee_wrench_base :deserialize buf ptr-) (incf ptr- (send _est_ee_wrench_base :serialization-length))
   ;;
   self)
  )

(setf (get lwr_controllers::ArmState :md5sum-) "1ec4005eded14deb32698c63aa479d03")
(setf (get lwr_controllers::ArmState :datatype-) "lwr_controllers/ArmState")
(setf (get lwr_controllers::ArmState :definition-)
      "Header header

string[] joint_name
float32[] est_ext_torques
geometry_msgs/Wrench est_ee_wrench
geometry_msgs/Wrench est_ee_wrench_base

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



(provide :lwr_controllers/ArmState "1ec4005eded14deb32698c63aa479d03")


