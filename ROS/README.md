- The catkin_ws consists of the dynamixel joint controller and data selection bus link. It consists of the python nodes controller_spawner used to give movement commands to the dynamixel and the controller_manager node used to get the status feedback of the dynaixels.

- The cobra workspace consists of the complete control nodes of the gait generated and the different feedback using gaits of the snake robot.

- The fileshellscript has its own readme inside the fileshellscript folder.
connecting the dynamixel: connect the dynamixels in a daisy chain and connect the first dynamixel to the **usb2dynamixel** and connect the last dynamixel to the power supply.


- In order to ping to the individual motors user has to make the catkin_ws in which user has to make the dynamixel_motors stack.

1.run roscore in one tab.
2.run dynamixel_manager node in one tab
3.lastly echo the messages published. 

- Similarly one can also control the motors using the dynamixel_spawner node similar to the the way as described above:
follow the links:
1)http://wiki.ros.org/dynamixel_controllers/Tutorials/ConnectingToDynamixelBus
2)http://wiki.ros.org/dynamixel_controllers/Tutorials/CreatingJointPositionController

- The gait generation is done by the cobra workspace, follow the commands as shown:
1.run roscore 
2.run the gait specific nodes as available in the transformer package,src folder.
3.run the communicator node in separate tab to transferthe uart values to the motors in daisy chain.
For example, to run sidewinding gait run the commands:
1.roscore
2.rosrun transformer sidewinding
3.rosrun transformer communicator

- The last folder fileshellscript consists of the shell and txt files for combining ubuntu with python to make a gui.

- The command to open the gui is:
 $ python gui.py
 -- Enter the respective values and run the respective gait. 
 -- Files such as the climbing and rolling do not have the right angles. So you have to simulate before using dynamix folder and then set the right values of Amplitude,Phase and Frequency in the respective folder of cpp.
