#include <avr/io.h>
#include <util/delay.h>
#include <string.h>
#include <stdio.h>
#include <inttypes.h>


#define LED PB5
#define LED_DDR DDRB
#define LED_PORT PORTB

#define BTN PB4
#define BTN_PIN PINB
#define BTN_PORT PORTB

#define DEBOUNCE_TIME 250
#define SHORT_SIGNAL 500
#define LONG_SIGNAL	1000
#define SEPARATOR 1500
#define SPACE 2000
#define LIGHT_TIME 30

#define BAUD 9600                          // baudrate
#define UBRR_VALUE ((F_CPU)/16/(BAUD)-1)   // zgodnie ze wzorem

char alphabet[26][5];

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

uint8_t button_pushed(int8_t btn) {
	return (BTN_PIN & _BV(btn)) == 0;
}

uint8_t debounce(int8_t btn) {
	if (button_pushed(btn)) {
		_delay_us(DEBOUNCE_TIME);
		if (button_pushed(btn)) {
			return 1;
		}
	}
	return 0;
}

char find_char(char sequence[5]) {
	for (int8_t i = 0; i < 26; i++) {
		int8_t flag = 1;
		for (int8_t j = 0; j < 4; j++) {
			if (sequence[j] == ' ' && (int8_t)strlen(alphabet[i]) == j)
				return (int)'a' + i;
			if (sequence[j] != alphabet[i][j] || sequence[j] == ' ') {
				flag = 0;
				break;
			}
		}
		if (flag) {
			return (int)'a' + i;
		}
	}
	return ' ';
}


FILE uart_file;

int main() {
	// zainicjalizuj UART
 	uart_init();
  	// skonfiguruj strumienie wejścia/wyjścia
  	fdev_setup_stream(&uart_file, uart_transmit, uart_receive, _FDEV_SETUP_RW);
  	stdin = stdout = stderr = &uart_file;
	BTN_PORT |= _BV(BTN);
	strcpy(alphabet[0], ".-");
	strcpy(alphabet[1], "-...");
	strcpy(alphabet[2], "-.-.");
	strcpy(alphabet[3], "-..");
	strcpy(alphabet[4], ".");
	strcpy(alphabet[5], "..-.");
	strcpy(alphabet[6], "--.");
	strcpy(alphabet[7], "....");
	strcpy(alphabet[8], "..");
	strcpy(alphabet[9], ".---");
	strcpy(alphabet[10], "-.-");
	strcpy(alphabet[11], ".-..");
	strcpy(alphabet[12], "--");
	strcpy(alphabet[13], "-.");
	strcpy(alphabet[14], "---");
	strcpy(alphabet[15], ".--.");
	strcpy(alphabet[16], "--.-");
	strcpy(alphabet[17], ".-.");
	strcpy(alphabet[18], "...");
	strcpy(alphabet[19], "-");
	strcpy(alphabet[20], "..-");
	strcpy(alphabet[21], "...-");
	strcpy(alphabet[22], ".--");
	strcpy(alphabet[23], "-..-");
	strcpy(alphabet[24], "-.--");
	strcpy(alphabet[25], "--..");

	int32_t counter = 0;
	char sequence[5];
	int8_t letter_counter = 0;
	int8_t btn_pushed = 0;
	while (1) {
		if (debounce(BTN)) {
			btn_pushed = 1;
			if (counter == SHORT_SIGNAL)
				LED_PORT |= _BV(LED);
			if (counter == SHORT_SIGNAL + LIGHT_TIME)
				LED_PORT &= ~_BV(LED);
			if (counter == LONG_SIGNAL)
				LED_PORT |= _BV(LED);
			if (counter == LONG_SIGNAL + LIGHT_TIME)
				LED_PORT &= ~_BV(LED);
			if (counter == SEPARATOR)
				LED_PORT |= _BV(LED);
			if (counter == SEPARATOR + LIGHT_TIME)
				LED_PORT &= ~_BV(LED);
			if (counter == SPACE)
				LED_PORT |= _BV(LED);
			if (counter == SPACE + LIGHT_TIME)
				LED_PORT &= ~_BV(LED);
			_delay_ms(10);
			counter += 10;
			continue;
		} 
		if (btn_pushed) {
			LED_PORT &= ~_BV(LED);

			if (counter <= SHORT_SIGNAL) {
				sequence[letter_counter] = '.';
				letter_counter++;
			}
			else if (counter <= LONG_SIGNAL) {
				sequence[letter_counter] = '-';
				letter_counter++;
			}
			else if (counter <= SEPARATOR) {
				for(int8_t i = letter_counter; i < 4; i++)
					sequence[i] = ' ';
				printf("%c", find_char(sequence));
				strcpy(sequence, "");
				letter_counter = 0;
			}
			else {
				for(int8_t i = letter_counter; i < 4; i++)
					sequence[i] = ' ';
				printf("%c ", find_char(sequence));
				strcpy(sequence, "");
				letter_counter = 0;
			}
			counter = 0;
			btn_pushed = 0;
		}
		
	}
}
