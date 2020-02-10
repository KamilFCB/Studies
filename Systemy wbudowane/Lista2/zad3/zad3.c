#include <avr/io.h>
#include <util/delay.h>

#define LED PIND
#define LED_DDR DDRD
#define LED_PORT PORTD

#define BTN_L PB2 // RESET
#define BTN_M PB3 // PREV
#define BTN_R PB4 // NEXT
#define BTN_PIN PINB
#define BTN_PORT PORTB

#define DEBOUNCE_TIME 300
#define MAX_NUMBER 15

uint8_t binary_to_gray(uint8_t number) {
	return number ^ (number >> 1);
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

int main() {
  	BTN_PORT |= _BV(BTN_L);
	BTN_PORT |= _BV(BTN_M);
	BTN_PORT |= _BV(BTN_R);
	
  	LED_DDR = 0xff;
	UCSR0B &= ~_BV(RXEN0) & ~_BV(TXEN0);
	LED_PORT = binary_to_gray(0);
	uint8_t current_number = 0;
	uint8_t mid_pushed = 0, right_pushed = 0;
	while (1) {
		if (debounce(BTN_L)) {
			LED_PORT = 0b00000000;
			current_number = 0;
		}
		if (debounce(BTN_M)) {
			if (mid_pushed == 0) {
				mid_pushed = 1;
				if (current_number > 0)
					current_number--;
				else
					current_number = MAX_NUMBER;

				LED_PORT = binary_to_gray(current_number);
			}
			continue;
		}
		if (debounce(BTN_R)) {
			if (right_pushed == 0) {
				right_pushed = 1;
				if (current_number < MAX_NUMBER)
					current_number++;
				else
					current_number = 0;

				LED_PORT = binary_to_gray(current_number);
			}
			continue;
		}
		mid_pushed = 0;
		right_pushed = 0;
	}
}
