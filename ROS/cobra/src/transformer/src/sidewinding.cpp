/*
0 -> sidewinding left
1 -> sidewinding right
*/
#include "ros/ros.h"
#include "std_msgs/String.h"
#include <transformer/Angle.h>
#include <math.h>
#include <sstream>

#define nMotor 10

#define PI 3.14159265

#define POS1ARRAY {-51,-20,120,32,0,20,120,20,-69}
float A_x, A_y, W_x, W_y, delta_x, delta_y, phi, dir; 
bool torque_of=0;
double tb = 0;

void set_gait_param()
{
        A_x = 25;
        A_y = 8;
        W_x = 3.14;
        W_y = 3.14;
        delta_x = 2*3.14/3;
        delta_y = 2*3.14/3;
        phi=0;
        dir=1;
}

double angle_gen(uint8_t motor_id, double t)
{
        double angle;
	  if(motor_id%2==0)
                angle = A_x*sin( W_x*t + dir*motor_id*delta_x );
        else 
                angle = A_y*sin( W_y*t + dir*motor_id*delta_y + phi);
               
        return angle;
}


int main(int argc, char **argv)
{
        set_gait_param();       
        transformer::Angle msg;
        ros::init(argc, argv, "gait_generator");
        ros::NodeHandle n;
        ros::Publisher gait_pub = n.advertise<transformer::Angle>("gait_topic",1000);
        ros::Rate loop_rate(100);
	
	double cTime;
        double iTime = ros::WallTime::now().toSec();        

        while(ros::ok())
        {
                cTime = ros::WallTime::now().toSec()-iTime;
                for(int i=0; i<nMotor; i++)
                {
                        msg.motor_id = i;
                        msg.angle_value = angle_gen(i,cTime);
                        gait_pub.publish(msg);
			ROS_INFO("ID:%d Angle:%f", i, msg.angle_value);
                }       
                ros::spinOnce();
                loop_rate.sleep();        
        }

        return 0;
}
