#include <avr/io.h>
#include <stdio.h>
#include <inttypes.h>
#include <util/delay.h>

#define LED PB2
#define LED_DDR DDRB
#define LED_PORT PORTB

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
  	ADCSRA |= _BV(ADEN); // włącz ADC
}

void timer_init() {
	TCCR1A = _BV(COM1B1) | _BV(WGM11);
	TCCR1B = _BV(CS10) | _BV(WGM12) | _BV(WGM13);
	// ustaw pin OC1b (PB2) jako wyjscie
	LED_DDR |= _BV(LED);
}

uint16_t time[] = {1, 2, 4, 8, 15, 25, 40, 60, 83, 115, 150, 190, 240, 295, 350, 450};

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
	// zainicjalizuj ADC
  	adc_init();
	while (1) {
		ADCSRA |= _BV(ADSC); // wykonaj konwersję
    	while (!(ADCSRA & _BV(ADIF))); // czekaj na wynik
    	ADCSRA |= _BV(ADIF); // wyczyść bit ADIF (pisząc 1!)
    	uint16_t v = ADC; // weź zmierzoną wartość (0..1023)
		printf("Wartosc: %"PRIu16"\r\n", v);
		uint16_t ledv = v >> 6;
		ICR1 = time[ledv];
		
		_delay_ms(250);
	}

}


