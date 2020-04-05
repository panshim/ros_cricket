<<<<<<< HEAD
# Install script for directory: /home/liu/RSP-Proj/build/catkin_tools_prebuild

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/home/liu/RSP-Proj/install")
=======
# Install script for directory: /home/shimin/ROS_Prgm_Prj/build/catkin_tools_prebuild

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/home/shimin/ROS_Prgm_Prj/install")
>>>>>>> 24e8b89151bb1281ae4a6c477ecf802df642162d
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  
      if (NOT EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}")
        file(MAKE_DIRECTORY "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}")
      endif()
      if (NOT EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/.catkin")
        file(WRITE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/.catkin" "")
      endif()
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
<<<<<<< HEAD
   "/home/liu/RSP-Proj/install/_setup_util.py")
=======
   "/home/shimin/ROS_Prgm_Prj/install/_setup_util.py")
>>>>>>> 24e8b89151bb1281ae4a6c477ecf802df642162d
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
<<<<<<< HEAD
file(INSTALL DESTINATION "/home/liu/RSP-Proj/install" TYPE PROGRAM FILES "/home/liu/RSP-Proj/build/catkin_tools_prebuild/catkin_generated/installspace/_setup_util.py")
=======
file(INSTALL DESTINATION "/home/shimin/ROS_Prgm_Prj/install" TYPE PROGRAM FILES "/home/shimin/ROS_Prgm_Prj/build/catkin_tools_prebuild/catkin_generated/installspace/_setup_util.py")
>>>>>>> 24e8b89151bb1281ae4a6c477ecf802df642162d
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
<<<<<<< HEAD
   "/home/liu/RSP-Proj/install/env.sh")
=======
   "/home/shimin/ROS_Prgm_Prj/install/env.sh")
>>>>>>> 24e8b89151bb1281ae4a6c477ecf802df642162d
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
<<<<<<< HEAD
file(INSTALL DESTINATION "/home/liu/RSP-Proj/install" TYPE PROGRAM FILES "/home/liu/RSP-Proj/build/catkin_tools_prebuild/catkin_generated/installspace/env.sh")
=======
file(INSTALL DESTINATION "/home/shimin/ROS_Prgm_Prj/install" TYPE PROGRAM FILES "/home/shimin/ROS_Prgm_Prj/build/catkin_tools_prebuild/catkin_generated/installspace/env.sh")
>>>>>>> 24e8b89151bb1281ae4a6c477ecf802df642162d
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
<<<<<<< HEAD
   "/home/liu/RSP-Proj/install/setup.bash;/home/liu/RSP-Proj/install/local_setup.bash")
=======
   "/home/shimin/ROS_Prgm_Prj/install/setup.bash;/home/shimin/ROS_Prgm_Prj/install/local_setup.bash")
>>>>>>> 24e8b89151bb1281ae4a6c477ecf802df642162d
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
<<<<<<< HEAD
file(INSTALL DESTINATION "/home/liu/RSP-Proj/install" TYPE FILE FILES
    "/home/liu/RSP-Proj/build/catkin_tools_prebuild/catkin_generated/installspace/setup.bash"
    "/home/liu/RSP-Proj/build/catkin_tools_prebuild/catkin_generated/installspace/local_setup.bash"
=======
file(INSTALL DESTINATION "/home/shimin/ROS_Prgm_Prj/install" TYPE FILE FILES
    "/home/shimin/ROS_Prgm_Prj/build/catkin_tools_prebuild/catkin_generated/installspace/setup.bash"
    "/home/shimin/ROS_Prgm_Prj/build/catkin_tools_prebuild/catkin_generated/installspace/local_setup.bash"
>>>>>>> 24e8b89151bb1281ae4a6c477ecf802df642162d
    )
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
<<<<<<< HEAD
   "/home/liu/RSP-Proj/install/setup.sh;/home/liu/RSP-Proj/install/local_setup.sh")
=======
   "/home/shimin/ROS_Prgm_Prj/install/setup.sh;/home/shimin/ROS_Prgm_Prj/install/local_setup.sh")
>>>>>>> 24e8b89151bb1281ae4a6c477ecf802df642162d
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
<<<<<<< HEAD
file(INSTALL DESTINATION "/home/liu/RSP-Proj/install" TYPE FILE FILES
    "/home/liu/RSP-Proj/build/catkin_tools_prebuild/catkin_generated/installspace/setup.sh"
    "/home/liu/RSP-Proj/build/catkin_tools_prebuild/catkin_generated/installspace/local_setup.sh"
=======
file(INSTALL DESTINATION "/home/shimin/ROS_Prgm_Prj/install" TYPE FILE FILES
    "/home/shimin/ROS_Prgm_Prj/build/catkin_tools_prebuild/catkin_generated/installspace/setup.sh"
    "/home/shimin/ROS_Prgm_Prj/build/catkin_tools_prebuild/catkin_generated/installspace/local_setup.sh"
>>>>>>> 24e8b89151bb1281ae4a6c477ecf802df642162d
    )
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
<<<<<<< HEAD
   "/home/liu/RSP-Proj/install/setup.zsh;/home/liu/RSP-Proj/install/local_setup.zsh")
=======
   "/home/shimin/ROS_Prgm_Prj/install/setup.zsh;/home/shimin/ROS_Prgm_Prj/install/local_setup.zsh")
>>>>>>> 24e8b89151bb1281ae4a6c477ecf802df642162d
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
<<<<<<< HEAD
file(INSTALL DESTINATION "/home/liu/RSP-Proj/install" TYPE FILE FILES
    "/home/liu/RSP-Proj/build/catkin_tools_prebuild/catkin_generated/installspace/setup.zsh"
    "/home/liu/RSP-Proj/build/catkin_tools_prebuild/catkin_generated/installspace/local_setup.zsh"
=======
file(INSTALL DESTINATION "/home/shimin/ROS_Prgm_Prj/install" TYPE FILE FILES
    "/home/shimin/ROS_Prgm_Prj/build/catkin_tools_prebuild/catkin_generated/installspace/setup.zsh"
    "/home/shimin/ROS_Prgm_Prj/build/catkin_tools_prebuild/catkin_generated/installspace/local_setup.zsh"
>>>>>>> 24e8b89151bb1281ae4a6c477ecf802df642162d
    )
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
<<<<<<< HEAD
   "/home/liu/RSP-Proj/install/.rosinstall")
=======
   "/home/shimin/ROS_Prgm_Prj/install/.rosinstall")
>>>>>>> 24e8b89151bb1281ae4a6c477ecf802df642162d
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
<<<<<<< HEAD
file(INSTALL DESTINATION "/home/liu/RSP-Proj/install" TYPE FILE FILES "/home/liu/RSP-Proj/build/catkin_tools_prebuild/catkin_generated/installspace/.rosinstall")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "/home/liu/RSP-Proj/build/catkin_tools_prebuild/catkin_generated/installspace/catkin_tools_prebuild.pc")
=======
file(INSTALL DESTINATION "/home/shimin/ROS_Prgm_Prj/install" TYPE FILE FILES "/home/shimin/ROS_Prgm_Prj/build/catkin_tools_prebuild/catkin_generated/installspace/.rosinstall")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "/home/shimin/ROS_Prgm_Prj/build/catkin_tools_prebuild/catkin_generated/installspace/catkin_tools_prebuild.pc")
>>>>>>> 24e8b89151bb1281ae4a6c477ecf802df642162d
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/catkin_tools_prebuild/cmake" TYPE FILE FILES
<<<<<<< HEAD
    "/home/liu/RSP-Proj/build/catkin_tools_prebuild/catkin_generated/installspace/catkin_tools_prebuildConfig.cmake"
    "/home/liu/RSP-Proj/build/catkin_tools_prebuild/catkin_generated/installspace/catkin_tools_prebuildConfig-version.cmake"
=======
    "/home/shimin/ROS_Prgm_Prj/build/catkin_tools_prebuild/catkin_generated/installspace/catkin_tools_prebuildConfig.cmake"
    "/home/shimin/ROS_Prgm_Prj/build/catkin_tools_prebuild/catkin_generated/installspace/catkin_tools_prebuildConfig-version.cmake"
>>>>>>> 24e8b89151bb1281ae4a6c477ecf802df642162d
    )
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
<<<<<<< HEAD
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/catkin_tools_prebuild" TYPE FILE FILES "/home/liu/RSP-Proj/build/catkin_tools_prebuild/package.xml")
=======
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/catkin_tools_prebuild" TYPE FILE FILES "/home/shimin/ROS_Prgm_Prj/build/catkin_tools_prebuild/package.xml")
>>>>>>> 24e8b89151bb1281ae4a6c477ecf802df642162d
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
<<<<<<< HEAD
  include("/home/liu/RSP-Proj/build/catkin_tools_prebuild/gtest/cmake_install.cmake")
=======
  include("/home/shimin/ROS_Prgm_Prj/build/catkin_tools_prebuild/gtest/cmake_install.cmake")
>>>>>>> 24e8b89151bb1281ae4a6c477ecf802df642162d

endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
<<<<<<< HEAD
file(WRITE "/home/liu/RSP-Proj/build/catkin_tools_prebuild/${CMAKE_INSTALL_MANIFEST}"
=======
file(WRITE "/home/shimin/ROS_Prgm_Prj/build/catkin_tools_prebuild/${CMAKE_INSTALL_MANIFEST}"
>>>>>>> 24e8b89151bb1281ae4a6c477ecf802df642162d
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
