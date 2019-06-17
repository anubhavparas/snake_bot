#prev=$(head -1 m.txt)
#new=$(tail -1 m.txt)
read prev < /root/prev.txt
read new < /root/new.txt

eval sed -i 's/$prev/$new/g' /root/cobra/src/transformer/src/sidewinding.cpp
cd /root/cobra/
source devel/setup.bash
catkin_make
