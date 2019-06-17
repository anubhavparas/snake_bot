#include <avr/io.h>
#include <util/delay.h>
#define F_CPU 8000000UL

int main (void)
{	
	///////master initialization ////
	DDRB |= (1<<3)|(1<<2)|(1<<5);    // SCK, MOSI and SS as outputs
    DDRB &= ~(1<<4);                 // MISO as input
    
    SPCR |= (1<<MSTR);               // Set as Master
    SPCR |= (1<<SPR0)|(1<<SPR1);     // divided clock by 128
    SPCR |= (1<<SPE);				// Enable SPI
	
	
	DDRC=0XFF;						// slave 1 data output
	 
	DDRD=0xFF;						// slave 2 data output
    char ack1;						// slave 1 acknowledgment
	char ack2;						// slave 2 acknowledgment
	char data1;
	char data2; 
	int i=0;
	char speed1=50;
	char speed2=100;
	
	PORTB|=0B00000100;               
	_delay_ms(2000);
	
///////////////////     SLAVE 2    ////////////	
	
		PORTB&=0B11111011; 
//		for(i=0;i<2;i++)
//		{
		   SPDR = speed2;                 // send the data
            while(!(SPSR & (1<<SPIF)));  // wait until transmission is complete
		    
	        data1=SPDR;	
//		}	  
	 	PORTB|=0B00000100;

//////////////////     SLAVE 1	  ////////////	 
		 
	    _delay_ms(10);						// latch
	  
	    PORTB&=0B11111011; 
//		for(i=0;i<2;i++)
//		{
		   SPDR = speed1;                 // send the data
            while(!(SPSR & (1<<SPIF)));  // wait until transmission is complete
		    data2=SPDR;	
//		}	  
	 	
	  PORTB|=0B00000100;
///////////////////////////////////////////////	  
    while(1)
    {
		PORTD=data1;
		PORTC=data2;	
	}
}