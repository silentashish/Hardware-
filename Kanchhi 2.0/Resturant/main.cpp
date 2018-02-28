/*
 * Resturant.cpp
 *
 * Created: 1/30/2018 4:48:21 PM
 * Author : silentashish
 */ 
#define F_CPU 16000000UL

#include <avr/io.h>
#include <stdlib.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "motordriver.h"
#include "uart.h"
#include "Ultrasonic.h"
unsigned volatile int isa;

int main(void)
{
	DDRA = (0<<PINA1);
	DDRC=(1<<PORTC7)|(1<<PORTC6)|(1<<PORTC5)|(1<<PORTC4)|(1<<PORTC3);
	PORTC=(0<<PORTC7)|(0<<PORTC6)|(0<<PORTC5)|(0<<PORTC4)|(0<<PORTC3);
	DDRB=(1<<PORTB0)|(1<<PORTB6)|(1<<PORTB7)|(1<<PORTB3);
	PORTB=(0<<PORTB1)|(0<<PORTB2)|(0<<PORTB3)|(0<<PORTB7);
	
	GICR=(1<<INT0)|(1<<INT1);
	MCUCSR=(0<<ISC01)|(1<<ISC00)|(1<<ISC11)|(0<<ISC10);
	uart_init();
	init_QMC5883L();
	
	DDRD &= 0xFF;
	PORTD |= 0x0C;
	

	
	MCUCSR=(1<<JTD);
	MCUCSR=(1<<JTD);
	
while(1)
 {
   unsigned char  c= uart_receive();
	switch(c)
	{
	 case '1':
	 		forward(100);
			rotate(-90);
			forward(100);
			while(1)
			{
			if (PIND & 0x04)
			{
				print_string("switch released");
				rotate(180);
				forward(100);
				rotate(60);
				forward(100);
				break;
			}
			else
			{
				print_string("switch not released");
				stop();
			}
			}
			break;
			
	case '2':
		
		break;
	case '3':
		rotate(-90);
		rotate(-180);
		break;
	case '4':
	
		forward(100);
		rotate(90);
		forward(100);
		while(isa==0)
		{
			stop();
		}
		
		_delay_ms(2000);
		
		break;
	case '5':
		//dist = Read_Ultrasonic();
		//print_num(dist);
		print_char('\n');
		break;
	}
stop();
}
}
