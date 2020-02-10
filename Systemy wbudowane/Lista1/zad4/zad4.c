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
	uint8_t digit[10] = {0b11000000, 0b11111001, 0b10100100, 0b10110000, 0b10011001, 0b10010010, 0b10000010, 0b11111000, 0b10000000, 0b10010000};
	while(1)
	{
		for(int8_t i = 0; i < 10; i++)
		{
			LED_PORT = digit[i];
			_delay_ms(1000);
		}
	}
}
