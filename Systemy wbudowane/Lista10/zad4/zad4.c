#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>


void timer_init()
{
	TCCR1A = _BV(WGM11) | _BV(COM1B1);
	TCCR1B = _BV(WGM12) | _BV(WGM13) | _BV(CS10) | _BV(CS11);
	ICR1 = 4999; // ADC*20
}

void adc_init()
{
	ADMUX = _BV(REFS0);
	ADCSRA = _BV(ADEN) | _BV(ADPS2) | _BV(ADPS1) | _BV(ADPS0);
}

int main()
{
  	timer_init();
	adc_init();
	DDRB |= _BV(PB2);
	uint32_t old_max = 1023;
	uint32_t new_max = 570;
	uint32_t new_min = 150;
	while(1) {
		ADCSRA |= _BV(ADSC);
		while (!(ADCSRA & _BV(ADIF)));
		ADCSRA |= _BV(ADIF);
		uint32_t adc_value = ADC;
		OCR1B = adc_value * (new_max - new_min) / old_max + new_min;
	}
}

