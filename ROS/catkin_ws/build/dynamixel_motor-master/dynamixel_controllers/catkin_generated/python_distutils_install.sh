#!/bin/sh -x

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

cd "/home/aditya/catkin_ws/src/dynamixel_motor-master/dynamixel_controllers"

# Note that PYTHONPATH is pulled from the environment to support installing
# into one location when some dependencies were installed in another
# location, #123.
/usr/bin/env \
    PYTHONPATH="/home/aditya/catkin_ws/install/lib/python2.7/dist-packages:/home/aditya/catkin_ws/build/lib/python2.7/dist-packages:$PYTHONPATH" \
    CATKIN_BINARY_DIR="/home/aditya/catkin_ws/build" \
    "/usr/bin/python" \
    "/home/aditya/catkin_ws/src/dynamixel_motor-master/dynamixel_controllers/setup.py" \
    build --build-base "/home/aditya/catkin_ws/build/dynamixel_motor-master/dynamixel_controllers" \
    install \
    $DESTDIR_ARG \
    --install-layout=deb --prefix="/home/aditya/catkin_ws/install" --install-scripts="/home/aditya/catkin_ws/install/bin"
