#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>


void timer_init()
{
	TCCR1A = _BV(WGM11) | _BV(COM1A1);
	TCCR1B = _BV(WGM12) | _BV(WGM13) | _BV(CS10);
	ICR1 = 20461; // ADC*20
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
	DDRB |= _BV(PB1);

	while(1) {
		ADCSRA |= _BV(ADSC);
		while (!(ADCSRA & _BV(ADIF)));
		ADCSRA |= _BV(ADIF);
		OCR1A = ADC * 20;
	}
}

