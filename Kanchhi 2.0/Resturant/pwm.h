#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#include <avr/io.h>
#include<util/delay.h>

#define ICRValue 255

void pwm_init(){
	TCCR1A = (1 << COM1A0)|(1 << COM1A1)|(1 << WGM11);
	TCCR1B = (1 << WGM12)|(1 << WGM13)|(1 << CS10);
	ICR1 = ICRValue;
}

void pwm_writeA(int speed)
{
	OCR1A = 255 - speed;
}

