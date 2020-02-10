#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>
#include "pid.h"

#define BAUD 9600                          // baudrate
#define UBRR_VALUE ((F_CPU)/16/(BAUD)-1)   // zgodnie ze wzorem

#define K_P 0.9
#define K_I 0.4
#define K_D 0.2

struct PID_DATA pid_data;

int8_t interrupt_type = 0;
uint8_t pid_timer = 1;
uint32_t ovf_val, reference_value=1, potentiometer_value=1;

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
	DIDR0 = _BV(ADC0D) | _BV(ADC1D);
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
		reference_value = ADC;
		interrupt_type = 3;
		ADMUX &= ~_BV(MUX0);
		ADCSRA |= _BV(ADSC);
	} else if (interrupt_type == 3) {
		potentiometer_value = ADC;
		pid_timer = 1;
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
	DDRB |= _BV(PB2);
	int32_t input_value = 1;
	sei();
	pid_Init(K_P * SCALING_FACTOR, K_I * SCALING_FACTOR, K_D * SCALING_FACTOR, &pid_data);
	while(1) {
		printf("Zmierzono ovf: %"PRIu32"mv		capt: %"PRIu32"mv		input: %"PRIu32"\r\n", 
				(ovf_val * 5000) / 1024, (reference_value * 5000) / 1024, input_value);
		if (pid_timer == 1) {
			input_value = pid_Controller(reference_value, potentiometer_value, &pid_data);
			input_value = (input_value * 10230) / MAX_INT;
			OCR1A = input_value;
			pid_timer = 0;
		}
	}
}

