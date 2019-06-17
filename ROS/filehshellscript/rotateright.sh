cd /root/cobra
source devel/setup.bash
roscore & rosrun transformer rotateright & rosrun transformer communicator & xkill
#gnome-terminal -e 'bash -c \"xkil; exe
