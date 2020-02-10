#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hd44780.h"

#define BAUD 9600                          // baudrate
#define UBRR_VALUE ((F_CPU)/16/(BAUD)-1)   // zgodnie ze wzorem

int hd44780_transmit(char data, FILE *stream)
{
  	LCD_WriteData(data);
  	return 0;
}

// inicjalizacja UART
void uart_init()
{
	// ustaw baudrate
	UBRR0 = UBRR_VALUE;
	// wyczyść rejestr UCSR0A
	UCSR0A = 0;
	// włącz odbiornik i nadajnik
	UCSR0B = _BV(RXEN0) | _BV(RXCIE0);
	// ustaw format 8n1
	UCSR0C = _BV(UCSZ00) | _BV(UCSZ01);
}

ISR(USART_RX_vect)
{
	static char line[16];
	static int8_t line_position = 0;

	line[line_position] = UDR0;

	if (line[line_position] == '\r') {
		line[line_position] = '\0';
		LCD_Clear();
		LCD_GoTo(0, 0);
		printf("%s", line);
		LCD_GoTo(0, 1);
		line_position = 0;
		memset(line, '\0', 16);
		return;
	} else {
		LCD_WriteData(line[line_position]);
	}

	line_position++;
	if (line_position == 16) {
		LCD_Clear();
		LCD_GoTo(0, 0);
		printf("%s", line);
		LCD_GoTo(0, 1);
		line_position = 0;
		memset(line, '\0', 16);
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
	sei();
	uart_init();
	set_sleep_mode(SLEEP_MODE_IDLE);
	LCD_WriteCommand(HD44780_DISPLAY_ONOFF | HD44780_DISPLAY_ON | HD44780_CURSOR_ON | HD44780_CURSOR_BLINK);
	LCD_GoTo(0, 0);
	while(1) {
		sleep_mode();
	}
}

