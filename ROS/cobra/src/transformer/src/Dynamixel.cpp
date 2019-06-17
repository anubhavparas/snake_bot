#include"Dynamixel.h"
/*
 * Dynamixel.cpp
 *
 *  Created on: 04-Sep-2013
 *      Author: AJINKYA KAMAT
 */

void dynamixel_packet_send(unsigned char ID, unsigned char instr, unsigned char *pParam, unsigned char nParam)
{
	unsigned char Dynamixel_Packet_Buffer[126];	
	unsigned char check_sum;
	unsigned long i;


	Dynamixel_Packet_Buffer[0] = 0xFF;			//Send Start Frame
	Dynamixel_Packet_Buffer[1] = 0xFF;
	Dynamixel_Packet_Buffer[2] = ID;			//Send ID
	check_sum = ID;
	Dynamixel_Packet_Buffer[3] = (nParam + 2);	//Send Length
	check_sum += (nParam + 2);
	Dynamixel_Packet_Buffer[4] = instr;	//Send Instruction
	check_sum += (instr);

	if(nParam != 0)
	{
		for(i = 0; i < nParam ; i++)			//Send Parameters
		{
			Dynamixel_Packet_Buffer[5+i] = *(pParam+i);
			check_sum += *(pParam+i);
		}
	}

	Dynamixel_Packet_Buffer[5+i] = ~check_sum;				//Send Check Sum

}

void dynamixel_ang_set(unsigned char ID, float Ang)
{
	float angTemp;	
	unsigned char Dynamixel_Packet_Buffer[126];	
	unsigned char check_sum = WRITE_DATA + 5 + DYNAMIXEL_ANGLE_ADDRESS;

	angTemp = Ang * POSITION_UNIT;	
	
	Dynamixel_Packet_Buffer[0] = 0xFF;			//Send Start Frame
	Dynamixel_Packet_Buffer[1] = 0xFF;
	Dynamixel_Packet_Buffer[2] = ID;
	check_sum += ID;
	Dynamixel_Packet_Buffer[3] = 5;	//Send Length
	Dynamixel_Packet_Buffer[4] = WRITE_DATA;	//Send Instruction
	Dynamixel_Packet_Buffer[5] = DYNAMIXEL_ANGLE_ADDRESS;
	Dynamixel_Packet_Buffer[6]=(int)(angTemp);
	check_sum += (int)(angTemp);
        Dynamixel_Packet_Buffer[7]=(int)(angTemp)>>8;
	check_sum += (int)(angTemp)>>8;
	Dynamixel_Packet_Buffer[8]=~check_sum;

	write(uart_filestream, &Dynamixel_Packet_Buffer, 9);
}

void dynamixel_ang_set_sync(unsigned char* pID, float *pAng, unsigned char nDynamixel)
{
	unsigned char check_sum = 0xFE;
	unsigned long i;
	float angTemp;
	unsigned int pos_val;
	unsigned char Dynamixel_Packet_Buffer[126];

	GPIOPinWrite(GPIO_PORT_BASE, GPIO_PIN_DDir, 7);

	Dynamixel_Packet_Buffer[0] = 0xFF;			//Send Start Frame
	Dynamixel_Packet_Buffer[1] = 0xFF;
	Dynamixel_Packet_Buffer[2] = 0xFE;			//Send ID
	Dynamixel_Packet_Buffer[3] = (3*nDynamixel + 4);	//Send Length
	check_sum += (3*nDynamixel + 4);
	Dynamixel_Packet_Buffer[4] = SYNC_WRITE;	//Send Instruction
	check_sum += (SYNC_WRITE);

	for(i = 0; i < nDynamixel ; i++)			//Send Parameters
	{
		angTemp = (POSITION_UNIT*(*(pAng+i)));

		Dynamixel_Packet_Buffer[3*i+5] = *(pID+i);
		check_sum += *(pID+i);

		Dynamixel_Packet_Buffer[3*i+6] = (int)(angTemp);
		check_sum += (int)(angTemp);

		Dynamixel_Packet_Buffer[3*i+7] = (int)(angTemp)>>8;
		check_sum += (int)(angTemp)>>8;
	}

	Dynamixel_Packet_Buffer[3*i+5] = ~check_sum;				//Send Check Sum
}

/*void dynamixel_ang_speed_set(unsigned char* pID, unsigned char *pAng, unsigned char *pSpeed, unsigned char nDynamixel)
{
	unsigned char check_sum;
	unsigned long i;
	unsigned int pos_val, spd_val;

	GPIOPinWrite(GPIO_PORT_BASE, GPIO_PIN_DDir, 7);

	Dynamixel_Packet_Buffer[0] = 0xFF;			//Send Start Frame
	Dynamixel_Packet_Buffer[1] = 0xFF;
	Dynamixel_Packet_Buffer[2] = 0xFE;			//Send ID
	check_sum = SYNC_WRITE;
	Dynamixel_Packet_Buffer[3] = (3*nDynamixel + 4);	//Send Length
	check_sum += (5*nDynamixel + 4);
	Dynamixel_Packet_Buffer[4] = SYNC_WRITE;	//Send Instruction
	check_sum += (SYNC_WRITE);

	for(i = 0; i < nDynamixel ; i++)			//Send Parameters
	{
		pos_val = (POSITION_UNIT*(*(pAng+i)));
		spd_val = (SPEED_UNIT*(*(pSpeed+i)));

		Dynamixel_Packet_Buffer[5*i+5] = *(pID+i);
		check_sum += *(pID+i);

		Dynamixel_Packet_Buffer[5*i+6] = (char)pos_val;
		check_sum += (char)pos_val;

		Dynamixel_Packet_Buffer[5*i+7] = (char)(pos_val>>8);
		check_sum += (char)(pos_val>>8);

		Dynamixel_Packet_Buffer[5*i+6] = (char)spd_val;
		check_sum += (char)pos_val;

		Dynamixel_Packet_Buffer[5*i+7] = (char)(spd_val>>8);
		check_sum += (char)(spd_val>>8);
	}

	Dynamixel_Packet_Buffer[3*i+5] = ~check_sum;				//Send Check Sum

	GPIOPinWrite(GPIO_PORT_BASE, GPIO_PIN_DDir, 0);	//Set Recieve Mode
}
*/

