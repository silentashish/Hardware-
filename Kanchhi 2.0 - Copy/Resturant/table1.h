
#define F_CPU 16000000UL


#include <avr/io.h>

#include "lcd.h"
#include "motordriver.h"
#include "ultrasonic[312].h"
#include "TWI.h"
#include "compass.h"
#include "uart.h"

  int dist=0;
  int stopdist=0;
  int angle;
  unsigned char sensor_value=0;
 
  int distances=0;
  int count1=0;
int countDist()
{     
	if(sensor_value==0)
	{
		count++;
		count1=count/5.5;
	}
	distances=(int)3.14*11*count1;
	return (distances);
}

int Table1(void)
{    
	int count=0;
    

         DDRA=0xff;
         PORTA=0x00;
	  
	   forward(); 
	  
		
		while(dist!=300)
		{    
			
		
			stopdist= (int)ultra_dist();
			if(stopdist<50)
			{   
				 print_string(("excuse me"));
				stop();
				//space left for buzzercall
			}
			
			
				
				forward();
				sensor_value=PINB1 & 0x01;
				
				 dist=countDist();
				if(dist==300)
				print_string("left");
				
			
		}
	
	
	
}