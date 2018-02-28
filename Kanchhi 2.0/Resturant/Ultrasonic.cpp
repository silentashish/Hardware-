/*
 * Ultrasonic.cpp
 *
 * Created: 1/31/2017 10:46:26 PM
 *  Author: Topsykreet
 */ 
#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "Ultrasonic.h"

volatile uint32_t Ofcounter = 0;
volatile uint32_t trig_counter = 0;
volatile uint32_t no_of_ticks = 0;

/**************Initialises Ultrasonic by setting TRIG pin in AVR as output and ECHO as Input ***************/
void Init_Ultrasonic()
{
	TRIG_OUTPUT_MODE();                   //Set Trig as Output
	ECHO_INPUT_MODE();                    //Set Echo as Input
}


/************** Triggers TRIG PIN for 10us High Signal ************************/
void Trigger_Ultrasonic()   
{
	TRIG_LOW();                       //clear trigger before sending 10 us signal
	_delay_us(1);
	TRIG_HIGH();                      //send 10us high signal
	_delay_us(12);
	TRIG_LOW();                      //clear trigger after sending 10 us signal
	_delay_us(1);
}

/************** Increament timer for each overflow **************************/

ISR(TIMER1_OVF_vect)
{
	Ofcounter++;
	TCNT1 = 0;
}

/**************calculate and store echo time and return distance*************
       Returns : 1. -1       :Indicates Trigger error, couldn't pull trigger high
	             2. -2       :Indicates Echo error, no echo received within range
				 3. Distance :Ultrasonic calculates distance in CM
****************************************************************************/

int Read_Ultrasonic()
{
	uint32_t distance_in_cm = 0;
	uint32_t max_response_time = SENSOR_TIMEOUT;
	Init_Ultrasonic();
	Trigger_Ultrasonic();
	while(!(ECHO_PIN & (1<<ECHO_BIT)))                   //While echo pin is LOW
	{
		trig_counter ++;
		if(trig_counter > max_response_time){
		   return TRIG_ERROR;
		}
	}
	
	TCNT1 = 0;
	TCCR1B |= (1<<CS10);                               //start 16 bit timer with no prescaling
	TIMSK |= (1<<TOIE1);                               //enable overflow interrupt
	Ofcounter = 0;                                     //reset overflow counter
	sei();
	
	while((ECHO_PIN & (1<<ECHO_BIT)))                //while echo pin is still high
	{
		if(((Ofcounter * TIMER_MAX)+TCNT1) > SENSOR_TIMEOUT){
		    return ECHO_ERROR;
		}
	}
	TCCR1B = 0x00;           //stop 16 bit timer with no prescaler
	cli();
	no_of_ticks = ((Ofcounter * TIMER_MAX)+TCNT1);   //counter count
	distance_in_cm = (no_of_ticks/SENSOR_CM_TICK);
	return ((int)distance_in_cm);
}