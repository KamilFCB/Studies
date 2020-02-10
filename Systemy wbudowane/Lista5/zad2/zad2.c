#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <stdio.h>

#define BTN PD2
#define BTN_PIN PIND
#define BTN_PORT PORTD

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

// inicjalizacja ADC
void adc_init()
{
  	ADMUX   = _BV(REFS0); // referencja AVcc, wejście ADC0
  	DIDR0   = _BV(ADC0D); // wyłącz wejście cyfrowe na ADC0
  	// częstotliwość zegara ADC 125 kHz (16 MHz / 128)
  	ADCSRA  = _BV(ADPS0) | _BV(ADPS1) | _BV(ADPS2); // preskaler 128
	ADCSRA |= _BV(ADIE); // ADC interrupt enable
	ADCSRA |= _BV(ADATE); //ADC trigger enable
	ADCSRB  = _BV(ADTS1); // INT0 as source
	ADCSRA |= _BV(ADEN); // włącz ADC 
}

void io_init() {
	EICRA |= _BV(ISC00) | _BV(ISC01);
	EIMSK |= _BV(INT0);
}

uint32_t result;
FILE uart_file;

ISR(INT0_vect) {
}

ISR(ADC_vect) {
	ADCSRA |= _BV(ADIF);
	uint32_t v_out = ADC * (5000 / 1024);
	result = (10000 * 5000.0 / v_out) - 10000;
}

int main() {
  	BTN_PORT |= _BV(BTN);
	// zainicjalizuj UART
  	uart_init();
  	// skonfiguruj strumienie wejścia/wyjścia
  	fdev_setup_stream(&uart_file, uart_transmit, uart_receive, _FDEV_SETUP_RW);
  	stdin = stdout = stderr = &uart_file;
	adc_init();
	io_init();
	sei();
	while (1) {
		printf("Rezystancja: %"PRIu32"omow\r\n", result);
		_delay_ms(100);
	}
}
