#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>

int main (void)
{   /////////////// Slave 1 initialization////////
    DDRB &= ~((1<<3)|(1<<5)|(1<<2));   // SCK, MOSI and SS as inputs
    DDRB |= (1<<4);                    // MISO as output

    SPCR &= ~(1<<MSTR);                // Set as slave 
    SPCR |= (1<<SPR0)|(1<<SPR1);       // divide clock by 128
    SPCR |= (1<<SPE);                  // Enable SPI

//////////////// servo (PWM)
	TCCR1A|=(1<<COM1A1)|(1<<COM1B1)|(1<<WGM11);        //NON Inverted PWM
    TCCR1B|=(1<<WGM13)|(1<<WGM12)|(1<<CS11)|(1<<CS10); //PRESCALER=64 MODE 14(FAST PWM)

   ICR1=2499;  //fPWM=50Hz (Period = 20ms Standard).

   DDRB|=(1<<PB1);

////////////
	DDRC=0xFF;
	DDRD=0XFF;
	char speed1;
	char speed2;
	char ack1=0XFF;
	char ack2;

     int i=0;
    
         
		 SPDR=ack1;
		while(!(SPSR & (1<<SPIF)));    // wait until all data is received
		speed2=SPDR;
	                  
		
		 SPDR=speed2;
		while(!(SPSR & (1<<SPIF)));    // wait until all data is received
		speed1=SPDR;
		    
			PORTD =speed1;
			PORTC =speed2; 
		while(1)
		{

			OCR1A=speed1*10;
			_delay_ms(100);
			
		}          
            
 }
