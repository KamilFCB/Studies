#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>

#define LED PB5
#define LED_DDR DDRB
#define LED_PORT PORTB

#define BTN PD2
#define BTN_PIN PIND
#define BTN_PORT PORTD

void timer_init() {
	// prescaler 256 - 16000000Hz/256 = 62500Hz
	TCCR2B = _BV(CS22) | _BV(CS21);
	TIMSK2 |= _BV(TOIE2);
}

int8_t cyclic_list[244];

ISR(TIMER2_OVF_vect) {
	static uint8_t counter = 0;
	if (cyclic_list[counter]) {
		LED_PORT |= _BV(LED);
		cyclic_list[counter] = 0;
	} else {
		LED_PORT &= ~_BV(LED);
	}

	if (BTN_PIN & _BV(BTN)) {
		cyclic_list[counter] = 0;
	} else {
		cyclic_list[counter] = 1;
	}

	counter++;
	if (counter == 244) {
		counter = 0;
	}
}

int main() {
  	BTN_PORT |= _BV(BTN);
  	LED_DDR |= _BV(LED);
	timer_init();
	set_sleep_mode(SLEEP_MODE_PWR_SAVE);
	sei();
	while (1) {
		sleep_mode();
	}
}
