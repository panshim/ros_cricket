# CMake generated Testfile for 
# Source directory: /home/shimin/ROS_Prgm_Prj/src/debug_tool/rqt_ez_publisher
# Build directory: /home/shimin/ROS_Prgm_Prj/build/rqt_ez_publisher
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(_ctest_rqt_ez_publisher_nosetests_test.function_test.py "/home/shimin/ROS_Prgm_Prj/build/rqt_ez_publisher/catkin_generated/env_cached.sh" "/usr/bin/python" "/opt/ros/kinetic/share/catkin/cmake/test/run_tests.py" "/home/shimin/ROS_Prgm_Prj/build/rqt_ez_publisher/test_results/rqt_ez_publisher/nosetests-test.function_test.py.xml" "--return-code" "\"/usr/bin/cmake\" -E make_directory /home/shimin/ROS_Prgm_Prj/build/rqt_ez_publisher/test_results/rqt_ez_publisher" "/usr/bin/nosetests-2.7 -P --process-timeout=60 /home/shimin/ROS_Prgm_Prj/src/debug_tool/rqt_ez_publisher/test/function_test.py --with-xunit --xunit-file=/home/shimin/ROS_Prgm_Prj/build/rqt_ez_publisher/test_results/rqt_ez_publisher/nosetests-test.function_test.py.xml")
add_test(_ctest_rqt_ez_publisher_rostest_test_ros.test "/home/shimin/ROS_Prgm_Prj/build/rqt_ez_publisher/catkin_generated/env_cached.sh" "/usr/bin/python" "/opt/ros/kinetic/share/catkin/cmake/test/run_tests.py" "/home/shimin/ROS_Prgm_Prj/build/rqt_ez_publisher/test_results/rqt_ez_publisher/rostest-test_ros.xml" "--return-code" "/opt/ros/kinetic/share/rostest/cmake/../../../bin/rostest --pkgdir=/home/shimin/ROS_Prgm_Prj/src/debug_tool/rqt_ez_publisher --package=rqt_ez_publisher --results-filename test_ros.xml --results-base-dir \"/home/shimin/ROS_Prgm_Prj/build/rqt_ez_publisher/test_results\" /home/shimin/ROS_Prgm_Prj/src/debug_tool/rqt_ez_publisher/test/ros.test ")
subdirs(gtest)
