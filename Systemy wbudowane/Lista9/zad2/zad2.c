#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <inttypes.h>
#include <stdlib.h>
#include <string.h>
#include "hd44780.h"

int hd44780_transmit(char data, FILE *stream)
{
  	LCD_WriteData(data);
  	return 0;
}

void add_characters()
{
	uint8_t sign = 0x0;
	for(uint8_t i = 0; i < 5; i++) {
		LCD_WriteCommand(HD44780_CGRAM_SET | (8 * i));
		sign |= (1 << (4 - i));
		for(uint8_t j = 0; j < 8; j++) {
			LCD_WriteData(sign);
		}
	}
}

void print(int8_t counter)
{
	LCD_Clear();
	while (counter >= 5) {
		LCD_WriteData(0x04);
		counter -= 5;
	}

	if (counter > 0) {
		counter -= 1;
		LCD_WriteData(counter);
	}

}

FILE hd44780_file;

int main()
{
  	// skonfiguruj wyświetlacz
  	LCD_Initialize();
  	LCD_Clear();
  	// skonfiguruj strumienie wyjściowe
  	fdev_setup_stream(&hd44780_file, hd44780_transmit, NULL, _FDEV_SETUP_WRITE);
  	stdout = stderr = &hd44780_file;
	add_characters();
	LCD_GoTo(0, 0);
	int8_t counter = 0;
	while(1) {
		print(counter);
		_delay_ms(250);
		counter = counter == 80 ? 0 : counter+1;
	}
}

