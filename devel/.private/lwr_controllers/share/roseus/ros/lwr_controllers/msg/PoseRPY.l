;; Auto-generated. Do not edit!


(when (boundp 'lwr_controllers::PoseRPY)
  (if (not (find-package "LWR_CONTROLLERS"))
    (make-package "LWR_CONTROLLERS"))
  (shadow 'PoseRPY (find-package "LWR_CONTROLLERS")))
(unless (find-package "LWR_CONTROLLERS::POSERPY")
  (make-package "LWR_CONTROLLERS::POSERPY"))

(in-package "ROS")
;;//! \htmlinclude PoseRPY.msg.html
(if (not (find-package "GEOMETRY_MSGS"))
  (ros::roseus-add-msgs "geometry_msgs"))


(defclass lwr_controllers::PoseRPY
  :super ros::object
  :slots (_id _position _orientation ))

(defmethod lwr_controllers::PoseRPY
  (:init
   (&key
    ((:id __id) 0)
    ((:position __position) (instance geometry_msgs::Vector3 :init))
    ((:orientation __orientation) (instance lwr_controllers::RPY :init))
    )
   (send-super :init)
   (setq _id (round __id))
   (setq _position __position)
   (setq _orientation __orientation)
   self)
  (:id
   (&optional __id)
   (if __id (setq _id __id)) _id)
  (:position
   (&rest __position)
   (if (keywordp (car __position))
       (send* _position __position)
     (progn
       (if __position (setq _position (car __position)))
       _position)))
  (:orientation
   (&rest __orientation)
   (if (keywordp (car __orientation))
       (send* _orientation __orientation)
     (progn
       (if __orientation (setq _orientation (car __orientation)))
       _orientation)))
  (:serialization-length
   ()
   (+
    ;; int32 _id
    4
    ;; geometry_msgs/Vector3 _position
    (send _position :serialization-length)
    ;; lwr_controllers/RPY _orientation
    (send _orientation :serialization-length)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; int32 _id
       (write-long _id s)
     ;; geometry_msgs/Vector3 _position
       (send _position :serialize s)
     ;; lwr_controllers/RPY _orientation
       (send _orientation :serialize s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; int32 _id
     (setq _id (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; geometry_msgs/Vector3 _position
     (send _position :deserialize buf ptr-) (incf ptr- (send _position :serialization-length))
   ;; lwr_controllers/RPY _orientation
     (send _orientation :deserialize buf ptr-) (incf ptr- (send _orientation :serialization-length))
   ;;
   self)
  )

(setf (get lwr_controllers::PoseRPY :md5sum-) "ac4defc6a342778de62991685c2a0dda")
(setf (get lwr_controllers::PoseRPY :datatype-) "lwr_controllers/PoseRPY")
(setf (get lwr_controllers::PoseRPY :definition-)
      "#include <lwr_controllers/RPY.h>

int32 id
geometry_msgs/Vector3 position
RPY orientation

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
================================================================================
MSG: lwr_controllers/RPY
float64 roll
float64 pitch
float64 yaw

")



(provide :lwr_controllers/PoseRPY "ac4defc6a342778de62991685c2a0dda")


