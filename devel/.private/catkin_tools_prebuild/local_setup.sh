#!/usr/bin/env sh
# generated from catkin/cmake/template/local_setup.sh.in

# since this file is sourced either use the provided _CATKIN_SETUP_DIR
# or fall back to the destination set at configure time
<<<<<<< HEAD
: ${_CATKIN_SETUP_DIR:=/home/liu/RSP-Proj/devel/.private/catkin_tools_prebuild}
=======
: ${_CATKIN_SETUP_DIR:=/home/shimin/ROS_Prgm_Prj/devel/.private/catkin_tools_prebuild}
>>>>>>> 24e8b89151bb1281ae4a6c477ecf802df642162d
CATKIN_SETUP_UTIL_ARGS="--extend --local"
. "$_CATKIN_SETUP_DIR/setup.sh"
unset CATKIN_SETUP_UTIL_ARGS
