#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>

#define LEFT PD2
#define RIGHT PD3

void timer_init()
{
	TCCR1A = _BV(WGM11) | _BV(COM1A1);
	TCCR1B = _BV(WGM12) | _BV(WGM13) | _BV(CS10);
	ICR1 = 20461;
}

void adc_init()
{
	ADMUX = _BV(REFS0);
	ADCSRA = _BV(ADEN) | _BV(ADPS2) | _BV(ADPS1) | _BV(ADPS0);
	DIDR0 = _BV(ADC0D);
}

int main()
{
  	timer_init();
	adc_init();
	DDRB |= _BV(PB1);
	DDRD |= _BV(LEFT) | _BV(RIGHT);

	while(1) {
		ADCSRA |= _BV(ADSC);
		while (!(ADCSRA & _BV(ADIF)));
		ADCSRA |= _BV(ADIF);
		uint16_t adc_value = ADC;
		if (adc_value < 512) {
			OCR1A = (512 - adc_value) * 40;
			PORTD &= ~_BV(RIGHT);
			PORTD |= _BV(LEFT);
		}
		else {
			OCR1A = (adc_value - 512) * 40;
			PORTD &= ~_BV(LEFT);
			PORTD |= _BV(RIGHT);
		}
	}
}

