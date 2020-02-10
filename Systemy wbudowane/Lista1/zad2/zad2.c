#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

#define LED PB5
#define LED_DDR DDRB
#define LED_PORT PORTB

#define SHORT_SIGNAL 200
#define LONG_SIGNAL  500
#define SPACE		 750
#define SEPARATOR	 300

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


void light_up_long()
{
	LED_PORT |= _BV(LED);
	_delay_ms(LONG_SIGNAL);
}

void light_up_short()
{
	LED_PORT |= _BV(LED);
	_delay_ms(SHORT_SIGNAL);
}

void turn_off_space()
{
	LED_PORT &= ~_BV(LED);
    _delay_ms(SPACE);
}

void turn_off_separator()
{
	LED_PORT &= ~_BV(LED);
    _delay_ms(SEPARATOR);
}

void encode_character(char c)
{
	switch(c) 
	{
		case 'a':
			light_up_short();
			turn_off_separator();
			light_up_long();
			turn_off_space();
			return;
		case 'b':
			light_up_long();
			turn_off_separator();
			light_up_short();
			turn_off_separator();
			light_up_short();
			turn_off_separator();
			light_up_short();
			turn_off_space();
			return;
		case 'c':
			light_up_long();
			turn_off_separator();
			light_up_short();
			turn_off_separator();
			light_up_long();
			turn_off_separator();
			light_up_short();
			turn_off_space();
			return;
		case 'd':
			light_up_long();
			turn_off_separator();
			light_up_short();
			turn_off_separator();
			light_up_short();
			turn_off_space();
			return;
		case 'e':
			light_up_short();
			turn_off_space();
			return;
		case 'f':
			light_up_short();
			turn_off_separator();
			light_up_short();
			turn_off_separator();
			light_up_long();
			turn_off_separator();
			light_up_short();
			turn_off_space();
			return;
		case 'g':
			light_up_long();
			turn_off_separator();
			light_up_long();
			turn_off_separator();
			light_up_short();
			turn_off_space();
			return;
		case 'h':
			light_up_short();
			turn_off_separator();
			light_up_short();
			turn_off_separator();
			light_up_short();
			turn_off_separator();
			light_up_short();
			turn_off_space();
			return;
		case 'i':
			light_up_short();
			turn_off_separator();
			light_up_short();
			turn_off_space();
			return;
		case 'j':
			light_up_short();
			turn_off_separator();
			light_up_long();
			turn_off_separator();
			light_up_long();
			turn_off_separator();
			light_up_long();
			turn_off_space();
			return;
		case 'k':
			light_up_long();
			turn_off_separator();
			light_up_short();
			turn_off_separator();
			light_up_long();
			turn_off_space();
			return;
		case 'l':
			light_up_short();
			turn_off_separator();
			light_up_long();
			turn_off_separator();
			light_up_short();
			turn_off_separator();
			light_up_short();
			turn_off_space();
			return;
		case 'm':
			light_up_long();
			turn_off_separator();
			light_up_long();
			turn_off_space();
			return;
		case 'n':
			light_up_long();
			turn_off_separator();
			light_up_short();
			turn_off_space();
			return;
		case 'o':
			light_up_long();
			turn_off_separator();
			light_up_long();
			turn_off_separator();
			light_up_long();
			turn_off_space();
			return;
		case 'p':
			light_up_short();
			turn_off_separator();
			light_up_long();
			turn_off_separator();
			light_up_long();
			turn_off_separator();
			light_up_short();
			turn_off_space();
			return;
		case 'q':
			light_up_long();
			turn_off_separator();
			light_up_long();
			turn_off_separator();
			light_up_short();
			turn_off_separator();
			light_up_long();
			turn_off_space();
			return;
		case 'r':
			light_up_short();
			turn_off_separator();
			light_up_long();
			turn_off_separator();
			light_up_short();
			turn_off_space();
			return;
		case 's':
			light_up_short();
			turn_off_separator();
			light_up_short();
			turn_off_separator();
			light_up_short();
			turn_off_space();
			return;
		case 't':
			light_up_long();
			turn_off_space();
			return;
		case 'u':
			light_up_short();
			turn_off_separator();
			light_up_short();
			turn_off_separator();
			light_up_long();
			turn_off_space();
			return;
		case 'v':
			light_up_short();
			turn_off_separator();
			light_up_short();
			turn_off_separator();
			light_up_short();
			turn_off_separator();
			light_up_long();
			turn_off_space();
			return;
		case 'w':
			light_up_short();
			turn_off_separator();
			light_up_long();
			turn_off_separator();
			light_up_long();
			turn_off_space();
			return;
		case 'x':
			light_up_long();
			turn_off_separator();
			light_up_short();
			turn_off_separator();
			light_up_short();
			turn_off_separator();
			light_up_long();
			turn_off_space();
			return;
		case 'y':
			light_up_long();
			turn_off_separator();
			light_up_short();
			turn_off_separator();
			light_up_long();
			turn_off_separator();
			light_up_long();
			turn_off_space();
			return;
		case 'z':
			light_up_long();
			turn_off_separator();
			light_up_long();
			turn_off_separator();
			light_up_short();
			turn_off_separator();
			light_up_short();
			turn_off_space();
			return;
		case ' ':
			turn_off_space();
	}
}

void encode_string(char* s, uint8_t length)
{
	for(uint8_t i = 0; i < length; i++)
	{
		encode_character(s[i]);
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

  	char text[255];
	char ch;
	uint8_t i = 0;
	while(1)
	{
		i = 0;
		while(scanf("%c", &ch))
		{
			if((ch < 'a' || ch > 'z') && ch != ' ') break;
			text[i++] = ch;
			printf("%c", ch);
		}
		printf("\r\n");
		encode_string(text, i);
	}
}

