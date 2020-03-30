;; Auto-generated. Do not edit!


(when (boundp 'lwr_controllers::MultiPriorityTask)
  (if (not (find-package "LWR_CONTROLLERS"))
    (make-package "LWR_CONTROLLERS"))
  (shadow 'MultiPriorityTask (find-package "LWR_CONTROLLERS")))
(unless (find-package "LWR_CONTROLLERS::MULTIPRIORITYTASK")
  (make-package "LWR_CONTROLLERS::MULTIPRIORITYTASK"))

(in-package "ROS")
;;//! \htmlinclude MultiPriorityTask.msg.html


(defclass lwr_controllers::MultiPriorityTask
  :super ros::object
  :slots (_links _tasks ))

(defmethod lwr_controllers::MultiPriorityTask
  (:init
   (&key
    ((:links __links) (make-array 0 :initial-element 0 :element-type :integer))
    ((:tasks __tasks) (make-array 0 :initial-element 0.0 :element-type :float))
    )
   (send-super :init)
   (setq _links __links)
   (setq _tasks __tasks)
   self)
  (:links
   (&optional __links)
   (if __links (setq _links __links)) _links)
  (:tasks
   (&optional __tasks)
   (if __tasks (setq _tasks __tasks)) _tasks)
  (:serialization-length
   ()
   (+
    ;; int32[] _links
    (* 4    (length _links)) 4
    ;; float64[] _tasks
    (* 8    (length _tasks)) 4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; int32[] _links
     (write-long (length _links) s)
     (dotimes (i (length _links))
       (write-long (elt _links i) s)
       )
     ;; float64[] _tasks
     (write-long (length _tasks) s)
     (dotimes (i (length _tasks))
       (sys::poke (elt _tasks i) (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
       )
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; int32[] _links
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _links (instantiate integer-vector n))
     (dotimes (i n)
     (setf (elt _links i) (sys::peek buf ptr- :integer)) (incf ptr- 4)
     ))
   ;; float64[] _tasks
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _tasks (instantiate float-vector n))
     (dotimes (i n)
     (setf (elt _tasks i) (sys::peek buf ptr- :double)) (incf ptr- 8)
     ))
   ;;
   self)
  )

(setf (get lwr_controllers::MultiPriorityTask :md5sum-) "42e011fbf13e33d6ed6e65ac7a0bdf63")
(setf (get lwr_controllers::MultiPriorityTask :datatype-) "lwr_controllers/MultiPriorityTask")
(setf (get lwr_controllers::MultiPriorityTask :definition-)
      "int32[] links
float64[] tasks

")



(provide :lwr_controllers/MultiPriorityTask "42e011fbf13e33d6ed6e65ac7a0bdf63")


