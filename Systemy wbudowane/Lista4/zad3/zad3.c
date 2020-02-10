#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <util/delay.h>

#define LED_B PB3
#define LED_B_DDR DDRB
#define LED_B_PORT PORTB

#define LED_G PD6
#define LED_R PD5
#define LED_RG_DDR DDRD
#define LED_RG_PORT PORTD

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
	TCCR0A = _BV(COM0B1) | _BV(COM0A1) | _BV(WGM00) | _BV(WGM01);
	TCCR0B = _BV(CS00);
	TCCR2A = _BV(COM2A1) | _BV(WGM20) | _BV(WGM21);
	TCCR2B = _BV(CS20);

	LED_RG_DDR |= _BV(LED_R) | _BV(LED_G);
	LED_B_DDR |= _BV(LED_B);
}

struct RGB {
	uint8_t r, g, b;
};

struct RGB HSV_to_RGB(uint16_t h) {
	struct RGB color;
	uint8_t i = h/60;
	uint8_t f = h - (i * 60);
	uint8_t s = 1;
	uint8_t v = 1;
	uint8_t p = 0;
	uint8_t q = 60 - f;
	uint8_t t = 60 - ( 60 - f);

	if (i == 0) {
		color.r = v * 255;
		color.g = (t * 255) / 60;
		color.b = p * 255;
	} else if ( i == 1) {
		color.r = (q * 255) / 60;
		color.g = v * 255;
		color.b = p * 255;
	} else if ( i == 2) {
		color.r = p * 255;
		color.g = v * 255;
		color.b = (t * 255) / 60;
	} else if ( i == 3) {
		color.r = p * 255;
		color.g = (q * 255) / 60;
		color.b = v * 255;
	} else if ( i == 4) {
		color.r = (t * 255) / 60;
		color.g = p * 255;
		color.b = v * 255;
	} else if ( i == 5) {
		color.r = v * 255;
		color.g = p * 255;
		color.b = (q * 255) / 60;
	}
	return color;
}

//uint8_t time[] = {1, 2, 4, 8, 15, 25, 40, 60, 83, 115, 140, 170, 210, 235, 245, 255};
uint8_t time[] = {255, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 253, 253, 253, 253, 252, 252, 252, 251, 251, 251, 250, 250, 249, 249, 249, 248, 248, 247, 246, 246, 245, 245, 244, 243, 243, 242, 241, 241, 240, 239, 239, 238, 237, 236, 235, 235, 234, 233, 232, 231, 230, 229, 228, 227, 226, 225, 224, 223, 222, 221, 220, 219, 218, 217, 216, 215, 213, 212, 211, 210, 209, 208, 206, 205, 204, 203, 201, 200, 199, 197, 196, 195, 193, 192, 191, 189, 188, 187, 185, 184, 182, 181, 180, 178, 177, 175, 174, 172, 171, 169, 168, 166, 165, 163, 162, 160, 159, 157, 156, 154, 153, 151, 150, 148, 147, 145, 143, 142, 140, 139, 137, 136, 134, 132, 131, 129, 128, 126, 125, 123, 122, 120, 118, 117, 115, 114, 112, 111, 109, 107, 106, 104, 103, 101, 100, 98, 97, 95, 94, 92, 91, 89, 88, 86, 85, 83, 82, 80, 79, 77, 76, 74, 73, 72, 70, 69, 67, 66, 65, 63, 62, 61, 59, 58, 57, 55, 54, 53, 51, 50, 49, 48, 46, 45, 44, 43, 42, 41, 39, 38, 37, 36, 35, 34, 33, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 19, 18, 17, 16, 15, 15, 14, 13, 13, 12, 11, 11, 10, 9, 9, 8, 8, 7, 6, 6, 5, 5, 5, 4, 4, 3, 3, 3, 2, 2, 2, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

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
	srand(4);
	while (1) {
		// OCR2A - Blue | OCR0B - Red | OCR0A - Green
		uint16_t random = rand() % 360;
		struct RGB color = HSV_to_RGB(random);
		printf("random: %"PRIu16" R: %"PRIu8" G: %"PRIu8" B: %"PRIu8"\r\n", random, color.r, color.g, color.b);
		
		for (int16_t i = 0; i < 256; i++) {
			OCR0B = color.r < i ? time[color.r] : time[i];
			OCR0A = color.g < i ? time[color.g] : time[i];
			OCR2A = color.b < i ? time[color.b] : time[i];
			_delay_ms(15);
		}
		for (int16_t i = 255; i >= 0; i--) {
			OCR0B = color.r < i ? time[color.r] : time[i];
			OCR0A = color.g < i ? time[color.g] : time[i];
			OCR2A = color.b < i ? time[color.b] : time[i];
			_delay_ms(15);
		}		
	}

}


