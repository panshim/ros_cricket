# ros_cricket
## 1. Overview

## 2. Software
### 2.1 Existing Packages We Utilized

### 2.2 New ROS Packages We Implemented

All of our self-implemented packages are located in the "src" folder under our project repository on GitLab.

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