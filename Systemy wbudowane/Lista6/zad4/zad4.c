#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <stdio.h>

#define LA PB1
#define OE PB2


void spi_init() {
	// ustaw piny MOSI, SCK i ~SS jako wyjscia
	DDRB |= _BV(DDB3) | _BV(DDB5) | _BV(DDB2);
	// wlacz SPI w trybie master z zegarem 250 kHz
	SPCR = _BV(SPE) | _BV(MSTR) | _BV(SPR1);
}

// transfer jednego bajtu
void spi_transfer(uint8_t data) {
	SPDR = data;
	// czekaj na ukonczenie transmisji
	while (!(SPSR & _BV(SPIF)));
	// wyczysc flage przerwania
	SPSR |= _BV(SPIF);
}

int main() {
	DDRB |= _BV(LA) | _BV(OE);
	spi_init();
	uint8_t digit[10] = {0b00111111, 0b00000110, 0b01011011, 0b01001111, 0b01100110, 0b01101101, 0b01111101, 0b00000111, 0b01111111, 0b01101111};
	while (1) {
		for(uint8_t i = 0; i < 10; i++) {
			PORTB = _BV(LA) | _BV(OE);
			spi_transfer(digit[i]);
			PORTB = 0;
			_delay_ms(1000);
		}
	}
}
