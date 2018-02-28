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
	DDRA =(0<<PINA1);
	DDRB=(1<<PORTB0)|(1<<PORTB6)|(1<<PORTB7)|(1<<PORTB3);
	PORTB=(0<<PORTB1)|(0<<PORTB2)|(0<<PORTB3)|(0<<PORTB7);
	DDRC=(1<<PORTC7)|(1<<PORTC6)|(1<<PORTC5)|(1<<PORTC4)|(1<<PORTC3);
	PORTC=(0<<PORTC7)|(0<<PORTC6)|(0<<PORTC5)|(0<<PORTC4)|(0<<PORTC3);
	
	GICR=(1<<INT0)|(1<<INT1);
	MCUCSR=(0<<ISC01)|(1<<ISC00)|(1<<ISC11)|(0<<ISC10);
	uart_init();
	init_QMC5883L();
	
	DDRD &= 0xFF;
	PORTD |= 0x0C;
	MCUCSR=(1<<JTD);
	MCUCSR=(1<<JTD);
	lcd_init();
	lcd_clear();
	lcd_puts("*_* Hello");
	lcd_goto(64);
	lcd_puts("I am Kanchhi *_*");
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
				lcd_clear();
				lcd_puts("*_* Moving back");
				lcd_goto(64);
				lcd_puts("to order *_*");
				print_string("switch released");
				_delay_ms(1500);
				rotate(180);
				forward(100);
				rotate(90);
				forward(100);
				break;
			}
			else
			{
				lcd_clear();
				lcd_puts("^_^ Please lift");
				lcd_goto(64);
				lcd_puts("your food ^_^");
				print_string("switch not released");
				stop();
			}
			}
			break;
			
	case '2':
	 		forward(150);
	 		rotate(90);
	 		forward(150);
	 		while(1)
	 		{
		 		if (PIND & 0x04)
		 		{
			 		lcd_clear();
			 		lcd_puts("*_* Moving back");
			 		lcd_goto(64);
			 		lcd_puts("to order *_*");
			 		print_string("switch released");
			 		_delay_ms(1500);
			 		rotate(180);
			 		forward(150);
			 		rotate(-90);
			 		forward(150);
			 		break;
		 		}
		 		else
		 		{
			 		lcd_clear();
			 		lcd_puts("^_^ Please lift");
			 		lcd_goto(64);
			 		lcd_puts("your food ^_^");
			 		print_string("switch not released");
			 		stop();
		 		}
	 		}
		break;
	case '3':
		rotate(-180);
		break;
	case '4':
	while(1)
	{
		if (PIND & 0x04)
		{
			lcd_clear();
			lcd_puts("*_* Moving back");
			lcd_goto(64);
			lcd_puts("to order *_*");
			print_string("switch released");
			_delay_ms(1500);
			break;
		}
		else
		{
			lcd_clear();
			lcd_puts("^_^ Please lift");
			lcd_goto(64);
			lcd_puts("your food ^_^");
			print_string("switch not released");
			stop();
		}
	}
		break;
	case '5':
		break;
	}
stop();
}
}