#include <avr/io.h>
#include <stdio.h>
#include <inttypes.h>

#define BAUD 9600                          // baudrate
#define UBRR_VALUE ((F_CPU)/16/(BAUD)-1)   // zgodnie ze wzorem

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

void calculate_int8()
{
	printf("int8_t\r\n");
	int8_t a, b;
	printf("Podaj 8-bitowa liczbe: ");
	scanf("%"SCNd8, &a);
	printf("\r\nPodaj 8-bitowa liczbe: ");
	scanf("%"SCNd8, &b);
	printf("\r\n%"PRId8" + %"PRId8" = %"PRId8"\r\n", a, b, a+b);
	printf("%"PRId8" * %"PRId8" = %"PRId8"\r\n", a, b, a*b);
	if(b != 0)
		printf("%"PRId8" / %"PRId8" = %"PRId8"\r\n", a, b, a/b);
}

void calculate_int16()
{
	printf("int16_t\r\n");
	int16_t a, b;
	printf("Podaj 16-bitowa liczbe: ");
	scanf("%" SCNd16, &a);
	printf("\r\nPodaj 16-bitowa liczbe: ");
	scanf("%" SCNd16, &b);
	printf("\r\n%"PRId16" + %"PRId16" = %"PRId16"\r\n", a, b, a+b);
	printf("%"PRId16" * %"PRId16" = %"PRId16"\r\n", a, b, a*b);
	if(b != 0)
		printf("%"PRId16" / %"PRId16" = %"PRId16"\r\n", a, b, a/b);
}

void calculate_int32()
{
	printf("int32_t\r\n");
	int32_t a, b;
	printf("Podaj 32-bitowa liczbe: ");
	scanf("%" SCNd32, &a);
	printf("\r\nPodaj 32-bitowa liczbe: ");
	scanf("%" SCNd32, &b);
	printf("\r\n%"PRId32" + %"PRId32" = %"PRId32"\r\n", a, b, a+b);
	printf("%"PRId32" * %"PRId32" = %"PRId32"\r\n", a, b, a*b);
	if(b != 0)
		printf("%"PRId32" / %"PRId32" = %"PRId32"\r\n", a, b, a/b);
}
/*
void calculate_int64()
{
	printf("int64_t\r\n");
	int64_t a, b;
	printf("Podaj 64-bitowa liczbe: ");
	scanf("%"SCNd64, &a);
	printf("\r\nPodaj 64-bitowa liczbe: ");
	scanf("%"SCNd64, &b);
	printf("\r\n%"PRId64" + %"PRId64" = %"PRId64"\r\n", a, b, a+b);
	printf("\r\n%"PRId64" * %"PRId64" = %"PRId64"\r\n", a, b, a*b);
	if(b != 0)
		printf("%"PRId64" / %"PRId64" = %"PRId64"\r\n", a, b, a/b);
}
*/
void calculate_float()
{
	printf("float\r\n");
	float a, b;
	printf("Podaj liczbe: ");
	scanf("%f", &a);
	printf("\r\nPodaj liczbe: ");
	scanf("%f", &b);
	printf("\r\n%f + %f = %f\r\n", a, b, a+b);
	printf("%f * %f = %f\r\n", a, b, a*b);
	if(b != 0)
		printf("%f / %f = %f\r\n", a, b, a/b);
}

FILE uart_file;

int main()
{
  	// zainicjalizuj UART
 	uart_init();
  	// skonfiguruj strumienie wejścia/wyjścia
  	fdev_setup_stream(&uart_file, uart_transmit, uart_receive, _FDEV_SETUP_RW);
  	stdin = stdout = stderr = &uart_file;
	calculate_int8();
  	calculate_int16();
	calculate_int32();
	//calculate_int64();
	calculate_float();
}


