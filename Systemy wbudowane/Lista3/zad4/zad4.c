#include <avr/io.h>
#include <stdio.h>
#include <inttypes.h>
#include <util/delay.h>

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
void adc_init_thermistor()
{
  	ADMUX   = _BV(REFS0); // referencja AVcc, wejście ADC0
  	DIDR0   = _BV(ADC0D); // wyłącz wejście cyfrowe na ADC0
  	// częstotliwość zegara ADC 125 kHz (16 MHz / 128)
  	ADCSRA  = _BV(ADPS0) | _BV(ADPS1) | _BV(ADPS2); // preskaler 128
  	ADCSRA |= _BV(ADEN); // włącz ADC
}

void adc_init_temperature()
{
  	ADMUX   = _BV(REFS0) | _BV(REFS1) | _BV(MUX3); // referencja AVcc, wejście ADC0
  	DIDR0   = _BV(ADC0D); // wyłącz wejście cyfrowe na ADC0
  	// częstotliwość zegara ADC 125 kHz (16 MHz / 128)
  	ADCSRA  = _BV(ADPS0) | _BV(ADPS1) | _BV(ADPS2); // preskaler 128
  	ADCSRA |= _BV(ADEN); // włącz ADC
}

FILE uart_file;

int main()
{
  	// zainicjalizuj UART
  	uart_init();
  	// skonfiguruj strumienie wejścia/wyjścia
  	fdev_setup_stream(&uart_file, uart_transmit, uart_receive, _FDEV_SETUP_RW);
  	stdin = stdout = stderr = &uart_file;
	adc_init_temperature();
  	while(1) {
		
    	ADCSRA |= _BV(ADSC); // wykonaj konwersję
    	while (!(ADCSRA & _BV(ADIF))); // czekaj na wynik
    	ADCSRA |= _BV(ADIF); // wyczyść bit ADIF (pisząc 1!)
		float temperature = (1.1 * 1024) / ADC;
		float ad = ADC;
		/*adc_init_thermistor();
		ADCSRA |= _BV(ADSC); // wykonaj konwersję
    	while (!(ADCSRA & _BV(ADIF))); // czekaj na wynik
    	ADCSRA |= _BV(ADIF); // wyczyść bit ADIF (pisząc 1!)
    	float v_in = (ADC * 5) / 1024.0; // weź zmierzoną wartość (0..1023)
		float thermistor_r = (10000 * v_in) / (5 - v_in);
		T = B / (log(r/r0) + B/t0)*/

		
    	printf("%f Temperatura: %f Rezystancja termistora: %f\r\n",ad, temperature, temperature);
		_delay_ms(1000);
  	}
}


