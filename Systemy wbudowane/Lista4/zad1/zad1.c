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

void timer_init() {
	// ustaw tryb licznika
	// WGM1 = 0000 -- normal
	// CS1 = 001 -- prescaler 1
	TCCR1B = _BV(CS10);
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
	volatile int8_t a_8b = 10, b_8b = 5, result_8b;
	volatile int16_t a_16b = 10, b_16b = 5, result_16b;
	volatile int32_t a_32b = 10, b_32b = 5, result_32b;
	volatile int64_t a_64b = 10, b_64b = 5, result_64b;
	volatile float a_flt = 10, b_flt = 5, result_flt;
	uint16_t start, end;
	uint16_t add, mult, div;

	start = TCNT1;
	result_8b = a_8b + b_8b;
	end = TCNT1;
	add = end - start;

	start = TCNT1;
	result_8b = a_8b * b_8b;
	end = TCNT1;
	mult = end - start;

	start = TCNT1;
	result_8b = a_8b / b_8b;
	end = TCNT1;
	div = end - start;

	printf("Zmierzony czas dla int8_t - dodawanie: %"PRIu16" cykli, mnozenie: %"PRIu16" cykli, dzielenie: %"PRIu16" cykli\r\n", add, mult, div);

	start = TCNT1;
	result_16b = a_16b + b_16b;
	end = TCNT1;
	add = end - start;

	start = TCNT1;
	result_16b = a_16b * b_16b;
	end = TCNT1;
	mult = end - start;

	start = TCNT1;
	result_16b = a_16b / b_16b;
	end = TCNT1;
	div = end - start;

	printf("Zmierzony czas dla int16_t - dodawanie: %"PRIu16" cykli, mnozenie: %"PRIu16" cykli, dzielenie: %"PRIu16" cykli\r\n", add, mult, div);

	start = TCNT1;
	result_32b = a_32b + b_32b;
	end = TCNT1;
	add = end - start;

	start = TCNT1;
	result_32b = a_32b * b_32b;
	end = TCNT1;
	mult = end - start;

	start = TCNT1;
	result_32b = a_32b / b_32b;
	end = TCNT1;
	div = end - start;

	printf("Zmierzony czas dla int32_t - dodawanie: %"PRIu16" cykli, mnozenie: %"PRIu16" cykli, dzielenie: %"PRIu16" cykli\r\n", add, mult, div);

	start = TCNT1;
	result_64b = a_64b + b_64b;
	end = TCNT1;
	add = end - start;

	start = TCNT1;
	result_64b = a_64b * b_64b;
	end = TCNT1;
	mult = end - start;

	start = TCNT1;
	result_64b = a_64b / b_64b;
	end = TCNT1;
	div = end - start;

	printf("Zmierzony czas dla int64_t - dodawanie: %"PRIu16" cykli, mnozenie: %"PRIu16" cykli, dzielenie: %"PRIu16" cykli\r\n", add, mult, div);

	start = TCNT1;
	result_flt = a_flt + b_flt;
	end = TCNT1;
	add = end - start;

	start = TCNT1;
	result_flt = a_flt * b_flt;
	end = TCNT1;
	mult = end - start;

	start = TCNT1;
	result_flt = a_flt / b_flt;
	end = TCNT1;
	div = end - start;

	printf("Zmierzony czas dla float - dodawanie: %"PRIu16" cykli, mnozenie: %"PRIu16" cykli, dzielenie: %"PRIu16" cykli\r\n", add, mult, div);
}


