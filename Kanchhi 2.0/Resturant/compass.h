/*
 * compass.h
 *
 * Created: 12/24/2017 1:00:45 AM
 *  Author: sagar
 */ 
#ifndef COMPASS_H_
#define COMPASS_H_

// Library for 3 axis magnetometer with QMC5883L chip i.e Chinese sensor
#include <avr/io.h>
#include <math.h>
#include "TWI.h"
#define QMC5883L_WRITE 0x1a // write address  //7-bit address=0x0d
#define QMC5883L_READ 0x1b // read address

#define X_OFFSET -200
#define Y_OFFSET 100
int16_t raw_x = 0;
int16_t raw_y = 0;
int16_t raw_z = 0;

void init_QMC5883L(void)
{
	i2c_init();
	//Set reset period register
	i2c_start(QMC5883L_WRITE);
	i2c_write(0x0B); //control register 3
	i2c_write(0x01);
	i2c_stop();

	//Configure mode of data
	i2c_start(QMC5883L_WRITE);
	i2c_write(0x09); // set pointer to control register 1
	i2c_write(0x1d); // write 0x1D to CRA  Number of samples per output=256  ,data output rate=10Hz
	i2c_stop();
}

void read_Compass(void)
{
	i2c_start(QMC5883L_WRITE);
	i2c_write(0x00); //set pointer to X-axis LSB
	i2c_stop();
	
	i2c_rep_start(QMC5883L_READ);
	// Read the registers one by one
	raw_x = i2c_readAck();
	raw_x |=((uint8_t)i2c_readAck())<<8;
	raw_x += X_OFFSET;
	raw_y = i2c_readAck();
	raw_y |= ((uint8_t)i2c_readAck())<<8;
	raw_y += Y_OFFSET;
	raw_z = i2c_readAck();
	raw_z |=((uint8_t)i2c_readNak())<<8;
	
	i2c_stop();	
}

int calculateAngle()
{
	return (atan2((double)raw_y,(double)raw_x)* 180 / 3.14159265 +180.0);
}

#endif /* COMPASS_H_ */