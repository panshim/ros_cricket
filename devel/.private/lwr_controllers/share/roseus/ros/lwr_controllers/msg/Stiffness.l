;; Auto-generated. Do not edit!


(when (boundp 'lwr_controllers::Stiffness)
  (if (not (find-package "LWR_CONTROLLERS"))
    (make-package "LWR_CONTROLLERS"))
  (shadow 'Stiffness (find-package "LWR_CONTROLLERS")))
(unless (find-package "LWR_CONTROLLERS::STIFFNESS")
  (make-package "LWR_CONTROLLERS::STIFFNESS"))

(in-package "ROS")
;;//! \htmlinclude Stiffness.msg.html


(defclass lwr_controllers::Stiffness
  :super ros::object
  :slots (_x _y _z _rx _ry _rz ))

(defmethod lwr_controllers::Stiffness
  (:init
   (&key
    ((:x __x) 0.0)
    ((:y __y) 0.0)
    ((:z __z) 0.0)
    ((:rx __rx) 0.0)
    ((:ry __ry) 0.0)
    ((:rz __rz) 0.0)
    )
   (send-super :init)
   (setq _x (float __x))
   (setq _y (float __y))
   (setq _z (float __z))
   (setq _rx (float __rx))
   (setq _ry (float __ry))
   (setq _rz (float __rz))
   self)
  (:x
   (&optional __x)
   (if __x (setq _x __x)) _x)
  (:y
   (&optional __y)
   (if __y (setq _y __y)) _y)
  (:z
   (&optional __z)
   (if __z (setq _z __z)) _z)
  (:rx
   (&optional __rx)
   (if __rx (setq _rx __rx)) _rx)
  (:ry
   (&optional __ry)
   (if __ry (setq _ry __ry)) _ry)
  (:rz
   (&optional __rz)
   (if __rz (setq _rz __rz)) _rz)
  (:serialization-length
   ()
   (+
    ;; float64 _x
    8
    ;; float64 _y
    8
    ;; float64 _z
    8
    ;; float64 _rx
    8
    ;; float64 _ry
    8
    ;; float64 _rz
    8
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; float64 _x
       (sys::poke _x (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _y
       (sys::poke _y (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _z
       (sys::poke _z (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _rx
       (sys::poke _rx (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _ry
       (sys::poke _ry (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _rz
       (sys::poke _rz (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; float64 _x
     (setq _x (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _y
     (setq _y (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _z
     (setq _z (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _rx
     (setq _rx (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _ry
     (setq _ry (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _rz
     (setq _rz (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;;
   self)
  )

(setf (get lwr_controllers::Stiffness :md5sum-) "88d995302418aa13534aa14fc9aeed94")
(setf (get lwr_controllers::Stiffness :datatype-) "lwr_controllers/Stiffness")
(setf (get lwr_controllers::Stiffness :definition-)
      "# This represents a diagonal Cartesian stiffness
# It is motivated by the KDL class: http://people.mech.kuleuven.be/~rsmits/kdl/api/html/classKDL_1_1Stiffness.html
# The conversion would be straight-forward, however, a generic 6D stiffness matrix would be desirable

float64 x
float64 y
float64 z
float64 rx
float64 ry
float64 rz
")



(provide :lwr_controllers/Stiffness "88d995302418aa13534aa14fc9aeed94")


