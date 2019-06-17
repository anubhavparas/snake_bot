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
       A_y = 0;
       W_x = 3.14;
       W_y = 3.14;
       delta_x = 2*3.14/3;
       delta_y = 2*3.14/3;
       phi=0;
       dir=1;
}

double interpolate(uint8_t motor_id, double t)
{
float pos1[]=POS1ARRAY;
float pos2[]={-66,-20,100,23,0,11,100,20,-51};
float pos3[]={-72,-20,100,5,0,-13,100,20,-42};
float pos4[]={-60,-20,100,-10,0,-31,100,20,-51};
float pos5[]={-45,-20,100,2,0,-16,100,20,-72};
float pos6[]={-42,-20,100,17,0,2,100,20,-77};
float pos7[]=POS1ARRAY;
float tt1=0.2,tt2=1,tt3=0.5,tt4=0.1,tt5=1,tt6=0.5,tt7=0.1;
float angle;

t = t-tb*(tt1+tt2+tt3+tt4+tt5+tt6+tt7);

if(t<tt1) // Initial Pose
angle=pos1[motor_id-1];

else if(t<(tt1+tt2)) // Dance Right
{
angle=pos1[motor_id-1]+(t-tt1)/tt2*(pos2[motor_id-1]-pos1[motor_id-1]);
}
else if(t<(tt1+tt2+tt3)) // Dance Right
{
angle=pos2[motor_id-1]+(t-tt1-tt2)/tt3*(pos3[motor_id-1]-pos2[motor_id-1]);
}
else if(t<(tt1+tt2+tt3+tt4)) // Dance Right
{
angle=pos3[motor_id-1]+(t-tt1-tt2-tt3)/tt4*(pos4[motor_id-1]-pos3[motor_id-1]);
}
else if(t<(tt1+tt2+tt3+tt4+tt5)) // Dance Right
{
angle=pos4[motor_id-1]+(t-tt1-tt2-tt3-tt4)/tt5*(pos5[motor_id-1]-pos4[motor_id-1]);
}
else if(t<(tt1+tt2+tt3+tt4+tt5+tt6)) // Dance Right
{
angle=pos5[motor_id-1]+(t-tt1-tt2-tt3-tt4-tt5)/tt6*(pos6[motor_id-1]-pos5[motor_id-1]);
}
else if(t<(tt1+tt2+tt3+tt4+tt5+tt6+tt7)) // Dance Right
{
angle=pos6[motor_id-1]+(t-tt1-tt2-tt3-tt4-tt5-tt6)/tt7*(pos7[motor_id-1]-pos6[motor_id-1]);
}
else
{
angle=pos7[motor_id-1];
tb++;
}
return angle;
}


double angle_gen2(uint8_t motor_id, double t)
{
double angle,alpha=20,tt1=2.5,tt2=1.5,tt3=1.5,tt4=1.5;
torque_of=0;
if(t<tt1)
{
if(motor_id==2 || motor_id==4 || motor_id==5 || motor_id==6 || motor_id==8)
{
angle=0;
}
else if (motor_id==1 || motor_id==3 || motor_id==7 || motor_id==9)
{
angle=t/tt1*90;
}
}
else if( t<(tt1+tt2) )
{
if(motor_id==2 || motor_id==4 || motor_id==6 || motor_id==8)
{
angle=0;
}
else if (motor_id==1 || motor_id==9)
{
angle=90+alpha*(t-tt1)/tt2;
}
else if (motor_id==3 || motor_id==7)
{
angle=90-alpha*(t-tt1)/tt2;
}
else if (motor_id==5 )
{
angle=-4*alpha*(t-tt1)/tt2;
}
}

else if( t<(tt1+tt2+tt3) )
{
if(motor_id==2 || motor_id==8)
{
angle=0;
}
else if (motor_id==4)
{
angle=90*(t-tt1-tt2)/tt3;
}
else if (motor_id==6)
{
angle=-90*(t-tt1-tt2)/tt3;
}
else if (motor_id==1 || motor_id==9)
{
angle=90+alpha;
}
else if (motor_id==3 || motor_id==7)
{
angle=90-alpha;
}
else if (motor_id==5 )
{
angle=-4*alpha;
torque_of=1;
}
}

else if (t<(tt1+tt2+tt3+tt4))
{
if(motor_id==2 || motor_id==8)
{
angle=0;
}
else if (motor_id==4)
{
angle=90;
}
else if (motor_id==6)
{
angle=-90;
}
else if (motor_id==1 || motor_id==9)
{
angle=90+alpha-alpha*(t-tt1-tt2-tt3)/tt4;
}
else if (motor_id==3 || motor_id==7)
{
angle=(90-alpha)*(1-(t-tt1-tt2-tt3)/tt4);
}
else if (motor_id==5 )
{
angle=0;
}
}

else
{
if(motor_id==2 || motor_id==8)
{
angle=0;
}
else if (motor_id==4)
{
angle=90;
}
else if (motor_id==6)
{
angle=-90;
}
else if (motor_id==1 || motor_id==9)
{
angle=90;
}
else if (motor_id==3 || motor_id==7)
{
angle=0;
}
else if (motor_id==5 )
{
angle=0;
}
}
return angle;
}

double biped_walk(uint8_t motor_id, double t)
{
double angle,theta=12,A1=7,A=9,pitch_angle=20;
double t1=2,t2=2,t3=2,t4=2,t5=3;
if(t<t1) // Initial Pose
{
if(motor_id==1 || motor_id==9)
angle=92;
else if(motor_id==3 || motor_id==5 || motor_id==7)
angle=0;
else if(motor_id==2)
angle=theta;
else if(motor_id==8)
angle=-theta;
else if(motor_id==4)
angle=90+theta;
else if(motor_id==6)
angle=-90-theta;
}
else if(t<(t1+t2)) // Dance Right
{
if(motor_id==1 || motor_id==9)
angle=92;
else if(motor_id==3 || motor_id==5 || motor_id==7)
angle=0;
else if(motor_id==2)
angle=theta+A*(t-t1)/t2;
else if(motor_id==8)
angle=-theta+A*(t-t1)/t2;
else if(motor_id==4)
angle=90+theta+A1*(t-t1)/t2;
else if(motor_id==6)
angle=-90-theta+A1*(t-t1)/t2;
}
else if(t<(t1+t2+t3)) // Lift by ROLL 4,6
{
if(motor_id==1 || motor_id==9)
angle=92;
else if(motor_id==3 || motor_id==5 || motor_id==7)
angle=0;
else if(motor_id==2)
angle=theta+ A + 2*A*(t-t1-t2)/t3;
else if(motor_id==8)
angle=-theta+A+2*A*(t-t1-t2)/t3;
else if(motor_id==4)
angle=90+theta+A1-2*A1*(t-t1-t2)/t3;
else if(motor_id==6)
angle=-90-theta+A1-2*A1*(t-t1-t2)/t3;
}
else if(t<(t1+t2+t3+t4)) // Lift and Pitch
{
if(motor_id==1 || motor_id==9) // see later
angle=92;
else if(motor_id==5)
angle=0;
else if(motor_id==3)
angle=0;
else if(motor_id==7)
angle=-pitch_angle*(t-t1-t2-t3)/t4;
else if(motor_id==2)
angle=theta+3*A;
else if(motor_id==8)
angle=-theta+3*A;
else if(motor_id==4)
angle=90+theta-A1;
else if(motor_id==6)
angle=-90-theta-A1;
}
else if(t<(t1+t2+t3+t4+t5)) // Lift and Pitch
{
if( motor_id==9) // see later
angle=92;
if(motor_id==1 ) // see later
angle=92 + 10 *(t-t1-t2-t3-t4)/t5;
else if(motor_id==5)
angle=0;
else if(motor_id==3)
angle=0;
else if(motor_id==7)
angle=-pitch_angle;
else if(motor_id==2)
angle=theta+3*A ;//- 6*A*(t-t1-t2-t3-t4)/t5;
else if(motor_id==8)
angle=-theta+3*A ;
else if(motor_id==4)
angle=90+theta-A1;
else if(motor_id==6)
angle=-90-theta-A1;
}

else
{
if( motor_id==9) // see later
angle=92;
if(motor_id==1 ) // see later
angle=92 + 10;
else if(motor_id==5)
angle=0;
else if(motor_id==3)
angle=0;
else if(motor_id==7)
angle=-pitch_angle;
else if(motor_id==2)
angle=theta+3*A ;//- 6*A*(t-t1-t2-t3-t4)/t5;
else if(motor_id==8)
angle=-theta+3*A ;
else if(motor_id==4)
angle=90+theta-A1;
else if(motor_id==6)
angle=-90-theta-A1;
}

return angle;
}


double angle_gen(uint8_t motor_id, double t)
{
       double angle,w,A,A1,theta;
w=1.5*PI;A1=3;A=20;theta=12;
//  Dance
if(motor_id==1 || motor_id==9)
angle=92;
// else if(motor_id==6)
// angle=-90;
else if(motor_id==3 || motor_id==5 || motor_id==7)
angle=0;
else if(motor_id==2)
angle=theta+A*sin(w*t);
else if(motor_id==8)
angle=-theta+A*sin(w*t);
else if(motor_id==4)
{
//if(A1*sin(w*t)>0)
angle=90+theta-A1*sin(w*t);
//else
// angle=90+theta;
}
else if(motor_id==6)
{
//if(A1*sin(w*t)<0)
angle=-90-theta-A1*sin(w*t);
//else
// angle=-90-theta;
}

/*
// Pitch

if(motor_id==4)
angle=90+10;
else if(motor_id==9)
angle=90;
else if(motor_id==6)
angle=-90+10;
else if(motor_id==5 || motor_id==7)
angle=0;
else if(motor_id==2 || motor_id==8)
angle=0-10;//A*sin(w*t);
else if(motor_id==1)
angle=90+A*sin(w*t);
else if(motor_id==3)
angle=A*sin(w*t);
/*

       if(motor_id%2==0)
               angle = A_x*sin( W_x*t + dir*motor_id*delta_x );
       else
               angle = A_y*sin( W_y*t + dir*motor_id*delta_y + phi);
*/              
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

float pos1[]=POS1ARRAY;

while(ros::ok())
{
for(int i=0; i<nMotor; i++)
               {
msg.motor_id = i;
                       msg.angle_value = pos1[i-1];
gait_pub.publish(msg);
}

ros::spinOnce();
               loop_rate.sleep();

printf("Sleeping");
sleep(2);
break;
}

double cTime;
       double iTime = ros::WallTime::now().toSec();        

       while(ros::ok())
       {
               cTime = ros::WallTime::now().toSec()-iTime;
               for(int i=0; i<nMotor; i++)
               {

                       msg.motor_id = i;
                       msg.angle_value = interpolate(i,cTime);
//msg.torque_off=torque_of;
  /*msg.motor_id = i;
  if(i==3)
{
msg.angle_value = 90;
}
else
{
msg.angle_value = 00;
}*/
                 gait_pub.publish(msg);
               }
               ros::spinOnce();
               loop_rate.sleep();

               ROS_INFO("%f", cTime);
       }

       return 0;
}

