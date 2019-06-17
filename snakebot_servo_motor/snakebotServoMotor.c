/*
 * AVRGCC13.c
 *
 * Created: 15-05-2014 16:20:14
 *  Author: JONE
 / 

#include <avr/io.h>

int main(void)
{DDRA =0XFF;
    while(1)
    {PORTA=0XFF;
        //TODO:: Please write your application code 
    }
	*/
	
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>


int servo1=200;
	
int main(void)
{
	DDRA= 0B11111111;
	TCCR1A |=1<<WGM11;
	TCCR1B |=1<<WGM12 | 1<<WGM13 | 1<<CS10 | 1<<CS11;
	TIMSK |=1<<OCIE1A;
	ICR1 = 4999;
	sei();
	int c1,c2,c3,c4,c5,c6,c7,c8;c1=0;c2=0;c3=0;c4=0;c5=0;c6=0;c7=0;c8=0;
	DDRC=0xFF;
	TCNT1 = 0;
	double i=0.0;
	
	int servo1=510;
	int max1=510;
	int min1=230;
	
	int servo2=350;
	int max2=460;
	int min2=270;
	
	int servo3=350;
	int max3=510;
	int min3=230;
	
	int servo4=340;
	int max4=500;
	int min4=250;
	
	int servo5=230;
	int max5=510;
	int min5=230;
	
	int servo6=340;
	int max6=500;
	int min6=250;
	
	int servo7=380;
	int max7=540;
	int min7=200;
	
	int servo8=380;
	int max8=540;
	int min8=200;
	
    
	while(1)
    {   
		/*if(servo2<450)
		{*/
			
		
		//if(servo1<400)
		//i=0;
        PORTC=0x00; 
		while(i<=3000.0)
		{		 
		   if(TCNT1>=160 && TCNT1<599)
		  { 
		 	  if(TCNT1>= servo1 && bit_is_set(PORTA,PINA0) ) PORTA &=~(1<<PINA0);
			  if(TCNT1>= servo2 && bit_is_set(PORTA,PINA1) ) PORTA &=~(1<<PINA1);
			  if(TCNT1>= servo3 && bit_is_set(PORTA,PINA2) ) PORTA &=~(1<<PINA2);
			  if(TCNT1>= servo4 && bit_is_set(PORTA,PINA3) ) PORTA &=~(1<<PINA3);
			  if(TCNT1>= servo5 && bit_is_set(PORTA,PINA4) ) PORTA &=~(1<<PINA4);
			  if(TCNT1>= servo6 && bit_is_set(PORTA,PINA5) ) PORTA &=~(1<<PINA5);
			  if(TCNT1>= servo7 && bit_is_set(PORTA,PINA6) ) PORTA &=~(1<<PINA6);
		      if(TCNT1>= servo8 && bit_is_set(PORTA,PINA7) ) PORTA &=~(1<<PINA7);
		  }			 
			
		  
			
          i+=1.0;
		}	
		
		PORTC=0b01000000;	
        
		
		i=0.0;
        if(servo1==max1)
	      c1=1;
		if (c1==1)  
		  servo1-=10;
		else
		  servo1+=10;
		 
        if(servo1==min1) 
		    c1=0;
		    
		

         if(servo2==max2 )
	      c2=1;
		 if (c2==1)  
		  servo2-=10;
		 else
		  servo2+=10;
		 
		 if(servo2==min2) 
		    c2=0;
			
			
		
		if(servo3==max3 )
	      c3=1;
		if (c3==1)  
		  servo3-=10;
		else
		  servo3+=10;
		    
		if(servo3==min3) 
		    c3=0;
		
		
		

         if(servo4==max4 )
	      c4=1;
		 if (c4==1)  
		  servo4-=10;
		 else
		  servo4+=10;
		
         if(servo4==min4) 
		    c4=0;
			
			
		if(servo5==max5)
	      c5=1;
		if (c5==1)  
		  servo5-=10;
		else
		  servo5+=10;
		    
		if(servo5==min5) 
		    c5=0;
		

 

         if(servo6==max6)
	      c6=1;
		 if (c6==1)  
		  servo6-=10;
		 else
		  servo6+=10;
		
 		 if(servo6==min6) 
		    c6=0;
			
		
		
		
		if(servo7==max7)
	      c7=1;
		if (c7==1)  
		  servo7-=10;
		else
		  servo7+=10;
		    
		if(servo7==min7) 
		    c7=0;
		
		
		
		
		
         if(servo8==max8)
	      c8=1;
		 if (c8==1)  
		  servo8-=10;
		 else
		  servo8+=10;
		
         if(servo8==min8) 
		    c8=0;
			
		
	
	}
	
}

ISR (TIMER1_COMPA_vect)
		{
			
			PORTA =0xFF;
			//servo1++;
			//if(servo1>=450)
			//servo1=200;
			//sPORTC=0b01000000;
		}
