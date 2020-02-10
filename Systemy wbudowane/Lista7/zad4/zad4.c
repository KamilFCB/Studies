#include <avr/io.h>
#include <stdio.h>
#include <inttypes.h>
#include <util/delay.h>

#define BAUD 9600                          // baudrate
#define UBRR_VALUE ((F_CPU)/16/(BAUD)-1)   // zgodnie ze wzorem

#define MASTER_SS PD4
#define MASTER_MOSI PD5
#define MASTER_MISO PD6
#define MASTER_SCK PD7

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

void spi_init() {
	// ustaw piny MOSI, SCK i ~SS jako wyjscia
	DDRD |= _BV(MASTER_MOSI) | _BV(MASTER_SCK) | _BV(MASTER_SS);
	DDRB |= _BV(PB4);
	PORTD |= _BV(MASTER_MISO);
	// wlacz SPI w trybie slave
	SPCR = _BV(SPE);
}

// transfer jednego bajtu
void spi_transfer(uint8_t data) {
	PORTD &= ~_BV(MASTER_SS);
	for (int8_t i = 7; i >= 0; i--) {
		if (data & (1 << i))
			PORTD |= _BV(MASTER_MOSI);
		else
			PORTD &= ~_BV(MASTER_MOSI);
		
		PORTD |= _BV(MASTER_SCK);
		PORTD &= ~_BV(MASTER_SCK);
	}
	PORTD |= _BV(MASTER_SS);
}

FILE uart_file;

int main()
{
  	// zainicjalizuj UART
  	uart_init();
  	// skonfiguruj strumienie wejścia/wyjścia
  	fdev_setup_stream(&uart_file, uart_transmit, uart_receive, _FDEV_SETUP_RW);
  	stdin = stdout = stderr = &uart_file;
	spi_init();
	uint8_t sent_data = 1;
	uint8_t received = 0;
  	while(1) {
		//spi_transfer(sent_data);
		PORTD &= ~_BV(MASTER_SS);
		for (int8_t i = 7; i >= 0; i--) {
			if (sent_data & (1 << i))
				PORTD |= _BV(MASTER_MOSI);
			else
				PORTD &= ~_BV(MASTER_MOSI);
			PORTD |= _BV(MASTER_SCK);
			PORTD &= ~_BV(MASTER_SCK);
		}
		PORTD |= _BV(MASTER_SS);
		printf("sent: %"PRIu8"\r\n", sent_data);

		while (!(SPSR & _BV(SPIF)));
		SPSR |= _BV(SPIF);
		uint8_t received_data = SPDR;
		printf("received slave: %"PRIu8"\r\n", received_data);
		SPDR = received_data;
		//_delay_ms(100);
		PORTD &= ~_BV(MASTER_SS);
		received = 0;
		for (int8_t i = 7; i >= 0; i--) {
			received |= (!((PIND & _BV(MASTER_MISO)) == 0)) << i;
			PORTD |= _BV(MASTER_SCK);
			PORTD &= ~_BV(MASTER_SCK);
			_delay_ms(10);
		}
		PORTD |= _BV(MASTER_SS);
		printf("received master: %"PRIu8"\r\n", received);
		sent_data++;
		_delay_ms(1000);
  	}
}

