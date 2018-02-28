/*
 * Ultrasonic.h
 *
 * Created: 1/31/2017 10:45:51 PM
 *  Author: Topsykreet
 */ 


////////////////*************************PROGRAM LOGIC***********************************///////////////////

//****AVR controller sends a 10us high signal to transmitter line of the sensor
//****Eight 40 kHz pulses are sent from transmitter transducer of Ultrasonic module after which 'echo' pin transits from low to high.
//****If for some reason, 'echo' pin does not go high, wait for a predetermined time and exit with error status
//****The 40 kHz wave hits the nearest object and bounces back
//****The receiver transducer detects the echo and echo pin will transit back from high to low.
//****The distance between the sensor and detected object is proportional to the length of time echo pin was high
/*****If no object is detected, or if for some reason the echo is not received, the module will stay high for a predetermined time and goes low.
      This generally happens when the distance to nearest obstacle is greater than the range of the sensor*****/
//****Wait until echo pin goes high - i.e. wait until 40kHz wave is sent
//****Start the timer and run until echo pin is high
//****Stop the timer once echo pin is low

//////////////***************************************************************************///////////////////

/*///////////////////////CALCULATION////////////////////////////////////
********************for Finding number of ticks for 1 cm of range***************
=(1/(100*(Speed of sound /2)) * 10^6)    us/cm     because s = ut and ( t in us )
= 60 us/cm

*********************for finding number of ticks in 1 us************************
F_CPU = 16MHz
so clock ticks 16000000 times in a second
i.e clock ticks 16 times in a micro second

*****************OVERALL*******************************************************
for finding 1 cm it should tick 60 * 16 i.e 960 times

******************************************************************************
for not responsing up to 5 meters  it has to tick 960000 times
******************************************************************************/

#ifndef ULTRASONIC_H_
#define ULTRASONIC_H_

#ifndef F_CPU
#define F_CPU 16000000UL
#endif

/*
  Define PORT and PINS as required
*/

#define TRIG_DDR DDRB                  //TRIG PORT
#define TRIG_PORT PORTB
#define TRIG_PIN PINB
#define TRIG_BIT PINB0                  //TRIG PIN
#define ECHO_DDR DDRD                  //ECHO PORT 
#define ECHO_PORT PORTD
#define ECHO_PIN PIND
#define ECHO_BIT PIND6                   //ECHO PIN

#define DELAY_BETWEEN_TEST 500         //Delay of 500us between every test
#define TIMER_MAX 65535                //For 16 bit timer i.e Timer 1 in ATMEGA32
#define TRIG_ERROR -1 
#define ECHO_ERROR -2
#define SENSOR_TIMEOUT 960000
#define SENSOR_CM_TICK 960

#define TRIG_INPUT_MODE() TRIG_DDR &= ~(1<<TRIG_BIT)
#define TRIG_OUTPUT_MODE() TRIG_DDR |= (1<<TRIG_BIT)
#define TRIG_LOW() TRIG_PORT &= ~(1<<TRIG_BIT)
#define TRIG_HIGH() TRIG_PORT |= (1<<TRIG_BIT)

#define ECHO_INPUT_MODE() ECHO_DDR &= ~(1<<ECHO_BIT)
#define ECHO_OUTPUT_MODE() ECHO_BIT |= (1<<ECHO_BIT)
#define ECHO_LOW() ECHO_PORT &= ~(1<<ECHO_BIT)
#define ECHO_HIGH() ECHO_PORT |= (1<<ECHO_BIT)


/*
 @brief Initialize Ports for Echo and Trigger Pins
 @Parameter void
 @return none
*/
void Init_Ultrasonic(void);

/*
 @brief Send 10us Pulse on Trigger pin
 @parameter void
 @return none
*/
void Trigger_Ultrasonic(void);
/*
 @brief calculate and store time and return distance
 @param void
 @return unsigned int
*/
int Read_Ultrasonic();

#endif /* ULTRASONIC_H_ */