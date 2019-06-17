#include "ros/ros.h"
#include <transformer/Angle.h>
#include <dynamixel_msgs/MotorStateList.h>
#include <unistd.h>                     //Used for UART
#include <fcntl.h>                      //Used for UART
#include <termios.h>                    //Used for UART
#include <math.h>
#include"Dynamixel.h"
#include <ros/callback_queue.h>
#define PI 3.14159265
#define nMotor 2
#define RefAng 150

float RxAng[nMotor];
bool RxTorqueOff[nMotor];
float PrevAng[nMotor];
const float compensation[nMotor] = {0,0};//{0,-2,0,2.5,0,0,0,-2.5,0,0};
int uart_filestream = -1;

int init_uart(char *port);
void gaitCallback1(const dynamixel_msgs::MotorStateList::ConstPtr& msg);
void timerUartComms(const ros::TimerEvent& event);
void gaitCallback(const transformer::Angle::ConstPtr& msg);

int main(int argc, char **argv)
{
       ros::init(argc, argv, "communicator");

       if(init_uart(argv[1])){return 1;}
       ros::NodeHandle n;
       ros::Subscriber sub = n.subscribe("gait_topic",1000,gaitCallback);
       //ros::spin();\
         spinner.spin();
    ros::Subscriber sub1 = n.subscribe("motor_states/pan_tilt_port",1000,gaitCallback1);


/*char uartBuffer[10];
uartBuffer[0] = 0xFF;
       uartBuffer[1] = 0xFF;
uartBuffer[2]=3;
uartBuffer[3]=0xFE;
uartBuffer[4]=0x00;
uartBuffer[5]=0x08;*/
ROS_INFO("Wake me up when sept ends");
//sleep(2);
// dynamixel_ang_set(0x09,180);
ROS_INFO("Done Setting baud");
    ros::Timer timer = n.createTimer(ros::Duration(0.01), timerUartComms);
       ros::MultiThreadedSpinner spinner(40);
       spinner.spin();
       // ros::spin();
       return 0;
}
void gaitCallback(const transformer::Angle::ConstPtr& msg)
{
       RxAng[msg->motor_id] = RefAng + msg->angle_value + compensation[msg->motor_id];
RxTorqueOff[msg->motor_id] = msg->torque_off;
       ROS_INFO("Angles recd %d %f torque %d",msg->motor_id, msg->angle_value, msg->torque_off);
}

void gaitCallback1(const dynamixel_msgs::MotorStateList::ConstPtr& msg)
{
       RxAng[msg->motor_states[0].id+1] = (msg->motor_states[0].goal + compensation[msg->motor_states[0].id])*300/1024;
RxTorqueOff[msg->motor_states[0].id+1] = !(msg->motor_states[0].moving);
       ROS_INFO("Angles rcd %d %f ",msg->motor_states[0].id,RxAng[msg->motor_states[0].id+1]);
}

void timerUartComms(const ros::TimerEvent& event)
{
unsigned char IDTemp[nMotor];
float AngTemp[nMotor];
int nDynamixel = 0;


for(int i=0; i < nMotor; i++)
{
if(RxTorqueOff[i]==0)
{
if(RxAng[i]!=PrevAng[i])
{
IDTemp[nDynamixel] = i;
AngTemp[nDynamixel] = RxAng[i];
ROS_INFO("Angle via UART %d %f",IDTemp[nDynamixel],AngTemp[nDynamixel]);
nDynamixel++;
}
PrevAng[i] = RxAng[i];
}
else
{
dynamixel_torque_off(i);
RxTorqueOff[i] = 0;
ROS_INFO("Torque off via UART %d",i);
}
}

if(nDynamixel!=0)
{
dynamixel_ang_set_sync(IDTemp, AngTemp, nDynamixel);
ROS_INFO("Angles Sent Via Uart %d",nDynamixel);
}

}

int init_uart(char *port)
{
//char port[] = "/dev/ttyACM0";

uart_filestream = open("/dev/ttyUSB0", O_RDWR | O_NOCTTY | O_NDELAY);            //Open in non blocking read/write mod

       printf("UART init done");
       if (uart_filestream == -1)
       {
               //ERROR - CAN'T OPEN SERIAL PORT
               printf("Error - Unable to open UART.  Ensure it is not in use by another application\n");
               return 1;
       }

       struct termios options;
       tcgetattr(uart_filestream, &options);
       //options.c_cflag = B9600;
       options.c_cflag = B1000000 | CS8 | CLOCAL | CREAD;         //<Set baud rate
       options.c_iflag = IGNPAR | ICRNL;
       options.c_oflag = ~OPOST;
       options.c_lflag = 0;
       tcflush(uart_filestream, TCIFLUSH);
       tcsetattr(uart_filestream, TCSANOW, &options);
       return 0;
}
