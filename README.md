# ros_cricket
## 1. Overview
### 1.1 Introduction

### 1.2 Ball Throwing


### 1.3 Multi-view Ball Tracking

### 1.4 Trajectory Prediction with Least Square

### 1.5 KUKA LWR Control


## 2. Software
### 2.1 Existing Packages We Utilized
1) Gazebo-related\
(**gazebo_dev**, **gazebo_msgs**, **gazebo_plugins**): They are used to experiment our project in Gazebo simulation and make the connection between Gazebo and ROS.

2) Robot-related:\
**reflexxes_type2**: robot arm trajectory planning.\
**lwr_controllers**: implements lwr controllers based on effort/position interfaces. We partially modified it by adding velocity controllers.\
**lwr_description**: contrains desctiption of lwr model. We partially modified it by adding cricket bat model.\
**lwr_hw**: contains LWR hardware interface configuration. We partially modified it in hardware interface.\
**single_lwr_launch**: keep it for launch files.
**single_lwr_moveit**: keep it for lwr’s integration.
**single_lwr_robot**: keep it for lwr’s integration.
**KDL**: used to calculate robot kinematics and transformation.

3) Vision-related:\
**cv_bridge**: It is used to make the conversion between images in OpenCV and image-related messages in ROS.\
**OpenCV**: It provides us with many useful functionalities helpful to our project (e.g. colorspace conversion, triangulation, least square solver, kalman filter, etc).\
**message_filters**: It is used to synchronize the multiple camera messages in the multi-view tracking system.

### 2.2 New ROS Packages We Implemented

All of our self-implemented packages are located in the "src" folder under our project repository on GitLab/GitHub.

1) **ball_throwing**: This package mainly provides a ball-throwing node with a SDF ball model.
Initial position to spawn, approximate target position and flying duration are passed in by launch file. Based on these parameters, it will create a ball shape target region which is within movable region of robot arm and use this region to constrain the random ball velocity range. The ball is spawned in Gazebo by calling the /gazebo/spawn_sdf_model service inside the node and the initial ball velocity is set by sending a message to /gazebo/set_model_state topic. The real ball position is also accessed from Gazebo through /gazebo/get_model_state topic and it is visualized in Rviz for validating the performance of tracking system.

2) **multi_view_plugin**: This package has an xacro file that includes a single Gazebo camera sensor (low-resolution: 300×300) and our self-implemented Gazebo model plugin "ball_tracker" used to detect and track the ball on 2D images (by range filtering on HSV colorspace and centroid calculation on binary images). This xacro model can be spawned with no gravity in Gazebo by specifying the pose. Besides, in the package, we also implement a class "multi_view_sys" (run in a ROS node) that subscribes and synchronizes (by message_filters) the 2D tracking result messages from multiple cameras, and imitates the calibration process for each camera through calculating the projection matrices by accessing the camera poses from Gazebo, and does triangulation to get 3D tracked position of the ball followed by Kalman filter smoothing. Those tracked or smoothed 3D results are published to specific type of topics that can be visualized in Rviz.

3) **traj_pred**: This package will run a node with our self-implemented trajectory predictor that subscribes the 3D tracking results from the multi-view system and use these stacked results to fit second-order polynomial curves by least square for predicting the 3D ball trajectory. It then reversely sends some valid waypoints on the trajectory to guid the motion planning of robot arm. The 3D results are published in specific topic type for visualization in Rviz.

4) **ekf**: This is a package using Kalman Filter to make estimation of the flight of the ball and his position. It receives the position of the 3D tracked position (observation) from multi_view_plugin, then it compute the posterior estimation. Due to the relatively low precision compared with the Kalman Filter provided by OpenCV and the high accuracy of the tracked result, we do not use this implemented package in our final version. (This package is not included in the final version, ie. the "master" branch of our project. We put it into the "inverse" branch.)

5) **cricket_coordinate**: This package is an interface between perception and robot control. It reads messages from perception-related packages and gets the estimated and predicted positions of the ball. Motion commands will be formulated according to this information and put into robot arm motion control pipeline sequentially.

6) **cricket_motion_planning**: This package is a trajectory planning package for LWR. Utilizing Reflexxes type II library, it generates target frame in Cartesian space in each control step. This package receives final target poses from cricket_coordinate, and breaks them into multiple intermediate frames, which has smooth position and velocity trajectory, sending them to the lower-level package in the control stack (i.e. cricket_lwr_interface or the built-in controller one_task_inverse_kinematics).

7) **cricket_lwr_interface**: This is a package calculating inverse kinematics for lwr. It receives Cartesian poses from upper-level packages, calculate corresponding position in joint space and send it to joint trajectory controller. It has a counterpart as one_task_inverse_kinematics, which is a built-in controller in an existing KUKA-related package.

8) **cricket_star**: This package is the master entrance of whole project. It ensembles all packages into one launch file and we could set several critical parameters for test. To run the whole project, you need to launch in this package.

## 3. Hardware and infrastructure
Due to the situation that we are not currently working in campus, we are not accessible to any real robot and sensors, so the whole project is done in the Gazebo simulation environment, and Rviz is used for visualizing some intermediate results.

## 4. Result
![result](https://github.com/panshim/ros_cricket/blob/master/reports/KUKA_cricket.gif)

## 5. Discussion
Since our project is simulated in Gazebo environment and the camera image rendering process by Gazebo is high load, the image frequency of the camera is dramatically bottle-necked by the computer even though we have already set the update rate of the camera sensor plugin to be very high (e.g. we set the update rate of camera sensor to be 200Hz but we only get roughly 40Hz image messages by inspecting the related topics, even though we are using a low-resolution camera, ie. 300×300). Using a low-resolution camera causes the problem that the ball is too small or even becomes invisible in some camera images. And a low image frequency causes the problem that we only get relatively sparse observations, which may lead to relatively large errors when fitting the trajectory. Fortunately, even so we still get accurate results. However, if we run the project in real world with real high-speed normal-resolution cameras, we believe the trajectory prediction could be more robust with dense observations and there would be more space for us to think about adding more ingredients.

Our project running in Gazebo uses a relatively easy physical model compared to real world (e.g.we do not add air drags), and the camera model is ideal. So if we would like to run our project on real robot in the future, we need to further think about ways to deal with camera noises and more complicated ball motions. This will involve adding an image denoising module, and using a modified Kalman Filter model (e.g. by including the acceleration or air drag imposed on the ball
into the state vector to be estimated). Besides, we can consider using a higher-order polynomial fitting or solving differential equations to predict more complicated ball trajectory in real world.

For robot control part, if we are going to apply the same strategy on a real robot rather than in simulation environment, the parameters throughout the control pipeline should be adjusted accordingly (e.g. maximum velocity constraints in Reflexxes function, joint limits, etc.). Besides, collision in a real robot would be severe, so we might have to implement a self-collision avoiding package for the safe concern.

For a object hitting or tracking task, it might be better to utilize a velocity controller than a inverse kinematics controller, because we don’t care about the ntermediate poses and the target poses is constantly changing throughout the whole process. We have configured a hardware interface for velocity controller in Gazebo simulation environment and successfully loaded the existing velocity controller. We haven’t implemented velocity-based control strategies on those controller and interface. I’m curious about the performance of velocity controllers in the future.