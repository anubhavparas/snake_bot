#ifndef DYNAMIXEL_H_
#define DYNAMIXEL_H_

extern int uart_filestream;
#include "ros/ros.h"
#define SYNC_ID 0xFE

#define POSITION_UNIT 1.7066666666666*2
#define SPEED_UNIT 8.73786407

#define PING 0x01
#define READ_DATA 0x02
#define WRITE_DATA 0x03
#define REG_WRITE 0x04
#define ACTION 0x05
#define RESET 0x06
#define SYNC_WRITE 0x83

#define DYNAMIXEL_ANGLE_ADDRESS 0x1E
/*
#define GPIO_PIN_DDir GPIO_PIN_1
#define GPIO_PORT_BASE GPIO_PORTF_BASE

#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include"inc/hw_uart.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "driverlib/uDMA.h"
#include "driverlib/gpio.h"
*/
void dynamixel_packet_send(unsigned char ID, unsigned char instr, unsigned char *Param, unsigned char nParam);

void dynamixel_ang_set_sync(unsigned char* pID, float *pAng, unsigned char nDynamixel)
{
	unsigned char check_sum = 0;
	unsigned int i;
	float angTemp;
	unsigned int pos_val;
	unsigned char Dynamixel_Packet_Buffer[126];

	Dynamixel_Packet_Buffer[0] = 0xFF;			//Send Start Frame
	Dynamixel_Packet_Buffer[1] = 0xFF;
	Dynamixel_Packet_Buffer[2] = SYNC_ID;			//Send ID
	check_sum += SYNC_ID;
	Dynamixel_Packet_Buffer[3] = (3*nDynamixel + 4);	//Send Length
	check_sum += (3*nDynamixel + 4);
	Dynamixel_Packet_Buffer[4] = SYNC_WRITE;		//Send Instruction
	check_sum += (SYNC_WRITE);
	Dynamixel_Packet_Buffer[5] = DYNAMIXEL_ANGLE_ADDRESS;	//Send Start Adress
	check_sum += (DYNAMIXEL_ANGLE_ADDRESS);
	Dynamixel_Packet_Buffer[6] = 2;				//Send Length of data
	check_sum += 2;

	for(i = 0; i < nDynamixel ; i++)			//Send Parameters
	{
		angTemp = (POSITION_UNIT*(*(pAng+i)));

		Dynamixel_Packet_Buffer[3*i+7] = *(pID+i);
		check_sum += *(pID+i);

		Dynamixel_Packet_Buffer[3*i+8] = (int)(angTemp);
		check_sum += (int)(angTemp);

		Dynamixel_Packet_Buffer[3*i+9] = (int)(angTemp)>>8;
		check_sum += (int)(angTemp)>>8;
	}

	Dynamixel_Packet_Buffer[3*i+7] = ~check_sum;				//Send Check Sum
	
	write(uart_filestream, &Dynamixel_Packet_Buffer, 3*i+8);
	ROS_INFO("%d",3*i+8);
}
void dynamixel_torque_off(unsigned char ID)
{
	unsigned char Dynamixel_Packet_Buffer[126];
	unsigned char check_sum = 0x04 + 0x03 + 0x18;
	
	Dynamixel_Packet_Buffer[0] = 0xFF;
        Dynamixel_Packet_Buffer[1] = 0xFF;
	Dynamixel_Packet_Buffer[2] = ID;
	check_sum += ID;
	Dynamixel_Packet_Buffer[3] = 0x04;
	Dynamixel_Packet_Buffer[4] = 0x03;
	Dynamixel_Packet_Buffer[5] = 0x18;
	Dynamixel_Packet_Buffer[6] = 0x00;
	Dynamixel_Packet_Buffer[7] = ~check_sum;

	write(uart_filestream, &Dynamixel_Packet_Buffer, 8);
}
void dynamixel_ang_Speed_set(unsigned char* pID, unsigned char *pAng, unsigned char *pSpeed, unsigned char nDynamixel);
void dynamixel_ang_set(unsigned char ID, float Ang);
void dynamixel_ang_set(unsigned char ID, float Ang)
{
	//float angTemp;	
	unsigned char Dynamixel_Packet_Buffer[126];	
	unsigned char check_sum =  ID + 4 + WRITE_DATA + 4+3;

	//angTemp = 180 * 11.377777777777778;	
	
	Dynamixel_Packet_Buffer[0] = 0xFF;			//Send Start Frame
	Dynamixel_Packet_Buffer[1] = 0xFF;
	Dynamixel_Packet_Buffer[2] = ID;
	//check_sum += 0x01;
	Dynamixel_Packet_Buffer[3] = 0x04;				//Send Length
	Dynamixel_Packet_Buffer[4] = WRITE_DATA;		//Send Instruction
	Dynamixel_Packet_Buffer[5] = 0x04;
	/*Dynamixel_Packet_Buffer[6]= (int)(angTemp);
	check_sum += (int)(angTemp);
        Dynamixel_Packet_Buffer[7]= (int)(angTemp)>>8;
	check_sum += (int)(angTemp)>>8;*/
	Dynamixel_Packet_Buffer[6]= 0x03;
	Dynamixel_Packet_Buffer[7]=~check_sum;

	write(uart_filestream, &Dynamixel_Packet_Buffer, 8);
	ROS_INFO("Packet Sent");
}
#endif /* DYNAMIXEL_H_ */

