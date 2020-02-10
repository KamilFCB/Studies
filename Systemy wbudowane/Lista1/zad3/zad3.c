#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

#define LED PIND
#define LED_DDR DDRD
#define LED_PORT PORTD
#define DELAY 75

int main() 
{
	LED_DDR = 0xff;
	UCSR0B &= ~_BV(RXEN0) & ~_BV(TXEN0);
	while(1)
	{
		for(int8_t i = 0; i < 10; i++)
		{
			if(i < 8)
				LED_PORT |= (1 << i);
			if(i-3 >= 0)
				LED_PORT &= ~(1 << i-3);
			if(i < 9)
				_delay_ms(DELAY);
		}
		
		for(int8_t i = 8; i >= -2; i--)
		{
			if(i >= 0)
				LED_PORT |= (1 << i);
			if(i+3 >= 0)
				LED_PORT &= ~(1 << i+3);
			_delay_ms(DELAY);
		}
	}
}
