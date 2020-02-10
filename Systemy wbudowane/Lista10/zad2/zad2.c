#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>

#define BAUD 9600                          // baudrate
#define UBRR_VALUE ((F_CPU)/16/(BAUD)-1)   // zgodnie ze wzorem

int8_t interrupt_type = 0;
uint16_t ovf_val, capt_val;

// inicjalizacja UART
void uart_init()
{
	// ustaw baudrate
	UBRR0 = UBRR_VALUE;
	// wyczyść rejestr UCSR0A
	UCSR0A = 0;
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

void timer_init()
{
	TCCR1A = _BV(COM1A1);
	TCCR1B = _BV(WGM13) | _BV(CS10);
	TIMSK1 = _BV(ICIE1) | _BV(TOIE1);
	ICR1 = 10230; // ADC*10
}

void adc_init()
{
	ADMUX = _BV(REFS0);
	ADCSRA = _BV(ADEN) | _BV(ADPS0) | _BV(ADPS1) | _BV(ADPS2) | _BV(ADIE);
}

ISR(TIMER1_OVF_vect)
{
	ADMUX |= _BV(MUX0);
	ADCSRA |= _BV(ADSC);
	interrupt_type = 1;
}

ISR(TIMER1_CAPT_vect)
{
	interrupt_type = 2;
	ADMUX |= _BV(MUX0);
	ADCSRA |= _BV(ADSC);
}

ISR(ADC_vect)
{
	if (interrupt_type == 1) {
		ovf_val = ADC;
		interrupt_type = 3;
		ADMUX &= ~_BV(MUX0);
		ADCSRA |= _BV(ADSC);
	} else if (interrupt_type == 2) {
		capt_val = ADC;
		interrupt_type = 3;
		ADMUX &= ~_BV(MUX0);
		ADCSRA |= _BV(ADSC);
	} else if (interrupt_type == 3) {
		OCR1A = ADC * 10;
	}
}

FILE uart_file;

int main()
{
  	// zainicjalizuj UART
  	uart_init();
  	// skonfiguruj strumienie wejścia/wyjścia
  	fdev_setup_stream(&uart_file, uart_transmit, uart_receive, _FDEV_SETUP_RW);
  	stdin = stdout = stderr = &uart_file;
	adc_init();
	timer_init();
	DDRB |= _BV(PB1);
	sei();

	while(1) {
		printf("Zmierzono ovf: %"PRIu16"mv | capt: %"PRIu16"mv\r\n", ovf_val * (5000 / 1024), capt_val * (5000 / 1024));
	}
}

