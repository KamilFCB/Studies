#include <avr/io.h>
#include <stdio.h>
#include <inttypes.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>

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

void timer1_init() {
	TCCR1B = _BV(CS12);
	TIMSK1 = _BV(ICIE1);
}

ISR(TIMER1_CAPT_vect) {
	static int8_t edge_flag = 0;
	uint32_t v = ICR1;
	if (edge_flag == 0) {
		TCNT1 = 0;
		edge_flag++;
	} else {
		edge_flag = 0;
		printf("%"PRIu16"\r\n", 62500 / v);
	}
}

FILE uart_file;

int main()
{
	PORTB |= _BV(PB0);
  	// zainicjalizuj UART
  	uart_init();
  	// skonfiguruj strumienie wejścia/wyjścia
  	fdev_setup_stream(&uart_file, uart_transmit, uart_receive, _FDEV_SETUP_RW);
  	stdin = stdout = stderr = &uart_file;
  	timer1_init();
	set_sleep_mode(SLEEP_MODE_IDLE);
  	sei();
	while (1) {
		sleep_mode();
	}
}


