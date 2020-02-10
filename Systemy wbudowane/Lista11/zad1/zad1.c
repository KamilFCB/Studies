#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <stdlib.h>
#include "pid.h"

#define BAUD 9600                          // baudrate
#define UBRR_VALUE ((F_CPU)/16/(BAUD)-1)   // zgodnie ze wzorem

#define K_P 0.75
#define K_I 0.33
#define K_D 0.02

struct PID_DATA pid_data;
int8_t interrupt_type = 0;
uint8_t pid_timer = 1;
uint32_t ovf_val, reference_value=1, potentiometer_value=1;
uint16_t set_temperature = 1;
uint32_t current_temperature = 1;

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
	TIMSK1 = _BV(TOIE1);
	ICR1 = MAX_INT; // ADC*10
}

void adc_init()
{
	ADMUX = _BV(REFS0) | _BV(REFS1);
	ADCSRA = _BV(ADEN) | _BV(ADPS0) | _BV(ADPS1) | _BV(ADPS2) | _BV(ADIE);
	DIDR0 = _BV(ADC0D) | _BV(ADC2D);
}


ISR(TIMER1_OVF_vect)
{
	ADMUX |= _BV(MUX1);
	ADCSRA |= _BV(ADSC);
	interrupt_type = 1;
}


ISR(ADC_vect)
{
	if (interrupt_type == 1) {
		reference_value = ADC;
		current_temperature = (reference_value * 1100) / 1024 - 500;
		interrupt_type = 3;
		ADMUX &= ~_BV(MUX1);
		ADCSRA |= _BV(ADSC);
	} else if (interrupt_type == 2) {
		reference_value = ADC;
		current_temperature = (reference_value * 1100) / 1024 - 500;
		interrupt_type = 3;
		ADMUX &= ~_BV(MUX1);
		ADCSRA |= _BV(ADSC);
	} else if (interrupt_type == 3) {
		potentiometer_value = ADC;
		set_temperature = (potentiometer_value >> 5) + 20;
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
	pid_Init(K_P * SCALING_FACTOR, K_I * SCALING_FACTOR, K_D * SCALING_FACTOR, &pid_data);
	sei();
	int32_t input_value = 0;
	while(1) {
		
		if (pid_timer == 1) {
			input_value = pid_Controller(set_temperature * 10, current_temperature, &pid_data);
			OCR1A = input_value < 0 ? 0 : input_value;
		}
		printf("Zmierzona temperatura: %"PRIu32".%"PRIu32"	ustawiona: %"PRIu16"	input: %"PRId32"\r\n", 
				current_temperature / 10, current_temperature % 10, set_temperature, input_value);
		
	}
}

