/*
 * uart.h
 *
 * Created: 1/30/2018 1:12:02 PM
 *  Author: sagar
 */ 

#ifndef UART_H_
#define UART_H_


#define F_CPU 16000000
#define BAUD 38400
#define BAUDPRESCALE ((F_CPU/(16UL*BAUD))-1)

void uart_init(void)
{
	
	UBRRH=(8>>BAUDPRESCALE);
	UBRRL= (BAUDPRESCALE);
	UCSRB= (1<<RXEN)|(1<<TXEN)|(1<<RXCIE);
	UCSRC=(1<<URSEL)|(3<<UCSZ0);
	
}
unsigned char uart_receive()
{
	while(!(UCSRA & (1<<RXC)));
	return(UDR);
}
void print_char(char data)
{
	while(!(UCSRA &(1<<UDRE)));
	UDR = data;
}
void print_num(int num)
{
	int numberArray[5];
	int c = 0;
	int n = num;
	/* extract each digit */
	while (n != 0)
	{
		numberArray[c] = n % 10;
		n /= 10;
		c++;
	}
	while(c>0)
	{
		print_char(numberArray[--c]+'0');
	}
}

void print_ulong(unsigned long long num)
{
	unsigned long long numberArray[10];
	int c = 0;
	unsigned long long n = num;
	/* extract each digit */
	while (n != 0)
	{
		numberArray[c] = n % 10;
		n /= 10;
		c++;
	}
	while(c>0)
	{
		print_char(numberArray[--c]+'0');
	}
}

void print_string(char* str)
{
	for(int i=0;str[i]!='\0';i++)
	{
		print_char(str[i]);
	}
}


#endif /* UART_H_ */