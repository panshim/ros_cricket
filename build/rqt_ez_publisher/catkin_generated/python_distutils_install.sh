#!/bin/sh

if [ -n "$DESTDIR" ] ; then
    case $DESTDIR in
        /*) # ok
            ;;
        *)
            /bin/echo "DESTDIR argument must be absolute... "
            /bin/echo "otherwise python's distutils will bork things."
            exit 1
    esac
    DESTDIR_ARG="--root=$DESTDIR"
fi

echo_and_run() { echo "+ $@" ; "$@" ; }

echo_and_run cd "/home/shimin/ROS_Prgm_Prj/src/rqt_ez_publisher-kinetic-devel"

# ensure that Python install destination exists
echo_and_run mkdir -p "$DESTDIR/home/shimin/ROS_Prgm_Prj/install/lib/python2.7/dist-packages"

# Note that PYTHONPATH is pulled from the environment to support installing
# into one location when some dependencies were installed in another
# location, #123.
echo_and_run /usr/bin/env \
    PYTHONPATH="/home/shimin/ROS_Prgm_Prj/install/lib/python2.7/dist-packages:/home/shimin/ROS_Prgm_Prj/build/rqt_ez_publisher/lib/python2.7/dist-packages:$PYTHONPATH" \
    CATKIN_BINARY_DIR="/home/shimin/ROS_Prgm_Prj/build/rqt_ez_publisher" \
    "/usr/bin/python" \
    "/home/shimin/ROS_Prgm_Prj/src/rqt_ez_publisher-kinetic-devel/setup.py" \
    build --build-base "/home/shimin/ROS_Prgm_Prj/build/rqt_ez_publisher" \
    install \
    $DESTDIR_ARG \
    --install-layout=deb --prefix="/home/shimin/ROS_Prgm_Prj/install" --install-scripts="/home/shimin/ROS_Prgm_Prj/install/bin"
