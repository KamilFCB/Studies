#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <stdio.h>

#define BAUD 9600                          // baudrate
#define UBRR_VALUE ((F_CPU)/16/(BAUD)-1)   // zgodnie ze wzorem

#define LED PB5
#define LED_DDR DDRB
#define LED_PORT PORTB

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
  	ADMUX   = _BV(REFS0) | _BV(REFS1); // referencja AVcc, wejście ADC0
  	DIDR0   = _BV(ADC0D); // wyłącz wejście cyfrowe na ADC0
  	// częstotliwość zegara ADC 125 kHz (16 MHz / 128)
  	ADCSRA  = _BV(ADPS0) | _BV(ADPS1) | _BV(ADPS2); // preskaler 128
	ADCSRA |= _BV(ADEN); // włącz ADC 
}

uint16_t get_temperatureX10()
{
	ADCSRA |= _BV(ADSC);
	while((ADCSRA & _BV(ADSC)));
	return (ADC * (1100 / 1024)) - 500;
}

FILE uart_file;
//uint32_t temperature;

int main() {
	LED_DDR |= _BV(LED);
	uint8_t T = 30;
	adc_init();
	// zainicjalizuj UART
  	uart_init();
  	// skonfiguruj strumienie wejścia/wyjścia
  	fdev_setup_stream(&uart_file, uart_transmit, uart_receive, _FDEV_SETUP_RW);
  	stdin = stdout = stderr = &uart_file;
	while (1) {
		/*ADCSRA |= _BV(ADSC);
		while((ADCSRA & _BV(ADSC)));
		temperature = (ADC * (1100 / 1024)) - 500; */
		uint16_t temperature = get_temperatureX10();
		LED_PORT |= _BV(LED);
		while (temperature / 10 < T) {
			_delay_ms(100);
			temperature = get_temperatureX10();
			printf("Nagrzewam! Temperatura: %"PRIu16".%"PRIu16" stopni\r\n", temperature / 10, temperature % 10);
		}
		LED_PORT &= ~_BV(LED);
		temperature = get_temperatureX10();
		printf("Po nagrzaniu temperatura: %"PRIu16".%"PRIu16" stopni\r\n", temperature / 10, temperature % 10);
		while ((temperature / 10) >= T - 5) {
			_delay_ms(10);
			temperature = get_temperatureX10();
			printf("Ochladzam! Temperatura: %"PRIu16".%"PRIu16" stopni\r\n", temperature / 10, temperature % 10);
		}
	}
}
