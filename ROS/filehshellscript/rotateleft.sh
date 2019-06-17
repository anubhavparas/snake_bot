cd /root/cobra
source devel/setup.bash
roscore & rosrun transformer rotateleft & rosrun transformer communicator & xkill
#gnome-terminal -e 'bash -c \"xkil; exe
