#include <avr/io.h>
#include <stdio.h>
#include <inttypes.h>
#include <util/delay.h>

#define LED PB5
#define IR_RCV PB1

#define BAUD 9600                          // baudrate
#define UBRR_VALUE ((F_CPU)/16/(BAUD)-1)   // zgodnie ze wzorem

// inicjalizacja UART
void uart_init()
{
  	// ustaw baudrate
  	UBRR0 = UBRR_VALUE;
 	 // włącz odbiornik i nadajnik
  	UCSR0B = _BV(RXEN0) | _BV(TXEN0);
  	// ustaw format 8n1
  	UCSR0C = _BV(UCSZ00) | _BV(UCSZ01);
}

// transmisja jednego znaku
int uart_transmit(char data, FILE *stream)
{
  	// czekaj aż transmiter gotowy
  	while(!(UCSR0A & _BV(UDRE0)));
  	UDR0 = data;
  	return 0;
}

// odczyt jednego znaku
int uart_receive(FILE *stream)
{
  	// czekaj aż znak dostępny
  	while (!(UCSR0A & _BV(RXC0)));
  	return UDR0;
}

void timer_init() {
	TCCR1A = _BV(COM1A0);
	TCCR1B = _BV(CS10) | _BV(WGM12);
	OCR1A = 210;
}

FILE uart_file;

int main()
{
  	// zainicjalizuj UART
  	uart_init();
  	// skonfiguruj strumienie wejścia/wyjścia
  	fdev_setup_stream(&uart_file, uart_transmit, uart_receive, _FDEV_SETUP_RW);
  	stdin = stdout = stderr = &uart_file;
	// zainicjalizuj licznik
	timer_init();
	DDRB &= ~_BV(PB0);
	PORTB |= _BV(PB0);
	while (1) {
		PORTB &= ~_BV(LED);
		DDRB |= _BV(PB1);
		_delay_us(600);
		DDRB &= ~_BV(PB1);
		if ((PINB & _BV(PB0)) == 0)
			PORTB |= _BV(LED);
		_delay_us(600);
	}

}


