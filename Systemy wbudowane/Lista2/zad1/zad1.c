#include <avr/io.h>
#include <util/delay.h>

#define LED PB5
#define LED_DDR DDRB
#define LED_PORT PORTB

#define BTN PB4
#define BTN_PIN PINB
#define BTN_PORT PORTB

#define DELAY_TIME 10

int main() {
  	BTN_PORT |= _BV(BTN);
  	LED_DDR |= _BV(LED);
	int8_t cyclic_list[100];

	while (1) {
		for (int8_t i = 0; i < 100; i++) {
			if (cyclic_list[i]) {
				LED_PORT |= _BV(LED);
				cyclic_list[i] = 0;
			} else {
				LED_PORT &= ~_BV(LED);
			}

			if (BTN_PIN & _BV(BTN)) {
				cyclic_list[i] = 0;
			} else {
				cyclic_list[i] = 1;
			}
			

			_delay_ms(DELAY_TIME);
		}
	}
}
