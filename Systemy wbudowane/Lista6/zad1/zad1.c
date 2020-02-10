#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <stdio.h>

#define BAUD 9600                          // baudrate
#define UBRR_VALUE ((F_CPU)/16/(BAUD)-1)   // zgodnie ze wzorem

// inicjalizacja UART
void uart_init()
{
  	// ustaw baudrate
  	UBRR0 = UBRR_VALUE;
 	 // włącz odbiornik i nadajnik oraz obsluge przerwan
  	UCSR0B = _BV(RXEN0) | _BV(TXEN0) | _BV(RXCIE0);
  	// ustaw format 8n1
  	UCSR0C = _BV(UCSZ00) | _BV(UCSZ01);
}

ISR(USART_RX_vect) {
	UDR0 = UDR0;
}

int main() {
	// zainicjalizuj UART
  	uart_init();
	set_sleep_mode(SLEEP_MODE_IDLE);
	sei();
	while (1) {
		sleep_mode();
	}
}
