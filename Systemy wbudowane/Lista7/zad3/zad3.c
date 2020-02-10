#include <avr/io.h>
#include <stdio.h>
#include <inttypes.h>
#include <stdlib.h>
#include <string.h>
#include "i2c.h"

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

FILE uart_file;

const uint8_t eeprom_addr = 0xd0;

int main()
{
  	// zainicjalizuj UART
  	uart_init();
  	// skonfiguruj strumienie wejścia/wyjścia
  	fdev_setup_stream(&uart_file, uart_transmit, uart_receive, _FDEV_SETUP_RW);
  	stdin = stdout = stderr = &uart_file;
  	// zainicjalizuj I2C
  	i2cInit();
  	// program testowy
  	uint16_t addr = 0;
  	#define i2cCheck(code, msg) \
    	if ((TWSR & 0xf8) != (code)) { \
      		printf(msg " failed, status: %.2x\r\n", TWSR & 0xf8); \
      		i2cReset(); \
      		continue; \
    	}

	char buffer[20];
  	while(1) {
		scanf("%s", buffer);
		if (strcmp(buffer, "date") == 0) {
			i2cStart();
			i2cCheck(0x08, "I2C start");
			i2cSend(eeprom_addr | ((addr & 0x100) >> 7));
			i2cCheck(0x18, "I2C EEPROM write request");
			addr = 0x04;
			i2cSend(addr & 0xff);
			i2cCheck(0x28, "I2C EEPROM set address");
			i2cStart();
			i2cCheck(0x10, "I2C second start");
			i2cSend(eeprom_addr | 0x1 | ((addr & 0x100) >> 7));
			i2cCheck(0x40, "I2C EEPROM read request");
			uint8_t date = i2cReadAck();
			uint8_t month = i2cReadAck();
			uint16_t year = i2cReadNoAck();
			i2cCheck(0x58, "I2C EEPROM read");
			i2cStop();
			i2cCheck(0xf8, "I2C stop");
			date = (date >> 4) * 10 + (date & 0x0f);
			month = ((month & 0x10) >> 4) * 10 + (month & 0x0f);
			year = 2000 + ((year & 0xf0) >> 4) * 10 + (year & 0x0f);
			printf("date %02"PRIu8"-%02"PRIu8"-%04"PRIu16"\r\n", date, month, year);
		} else if (strcmp(buffer, "time") == 0) {
			i2cStart();
			i2cCheck(0x08, "I2C start");
			i2cSend(eeprom_addr | ((addr & 0x100) >> 7));
			i2cCheck(0x18, "I2C EEPROM write request");
			addr = 0x00;
			i2cSend(addr & 0xff);
			i2cCheck(0x28, "I2C EEPROM set address");
			i2cStart();
			i2cCheck(0x10, "I2C second start");
			i2cSend(eeprom_addr | 0x1 | ((addr & 0x100) >> 7));
			i2cCheck(0x40, "I2C EEPROM read request");
			uint8_t seconds = i2cReadAck();
			uint8_t minutes = i2cReadAck();
			uint8_t hours = i2cReadNoAck();
			i2cCheck(0x58, "I2C EEPROM read");
			i2cStop();
			i2cCheck(0xf8, "I2C stop");
			seconds = (seconds >> 4) * 10 + (seconds & 0x0f);
			minutes = (minutes >> 4) * 10 + (minutes & 0x0f);
			hours = ((hours & 0x30) >> 4) * 10 + (hours & 0x0f);
			printf("time %02"PRIu8":%02"PRIu8":%02"PRIu8"\r\n", hours, minutes, seconds);
		} else if (strcmp(buffer, "set") == 0) {
			scanf("%s", buffer);
			if (strcmp(buffer, "date") == 0) {
				scanf("%s", buffer);
				uint8_t full_date = atoi(&buffer[0]);
				uint8_t full_month = atoi(&buffer[3]);
				uint16_t full_year = atoi(&buffer[6]);
				uint8_t date = ((full_date / 10) << 4) + (full_date % 10);
				uint8_t month = ((full_month / 10) << 4) + (full_month % 10);
				uint8_t year = (((full_year % 100) / 10) << 4) + (full_year % 10);
				addr = 0x04;
				i2cStart();
				i2cCheck(0x08, "I2C start");
				i2cSend(eeprom_addr | ((addr & 0x100) >> 7));
				i2cCheck(0x18, "I2C EEPROM write request");
				i2cSend(addr & 0xff);
				i2cCheck(0x28, "I2C EEPROM set address");
				i2cSend(date);
				i2cSend(month);
				i2cSend(year);
				i2cStop();
				i2cCheck(0xf8, "I2C stop");
				printf("set date %02"PRIu8"-%02"PRIu8"-%04"PRIu16"\r\n", full_date, full_month, full_year);
			} else if (strcmp(buffer, "time") == 0) {
				scanf("%s", buffer);
				uint8_t full_seconds = atoi(&buffer[6]);
				uint8_t full_minutes = atoi(&buffer[3]);
				uint8_t full_hours = atoi(&buffer[0]);
				uint8_t seconds = ((full_seconds / 10) << 4) + (full_seconds % 10);
				uint8_t minutes = ((full_minutes / 10) << 4) + (full_minutes % 10);
				uint8_t hours = ((full_hours / 10) << 4) + (full_hours % 10);
				addr = 0x00;
				i2cStart();
				i2cCheck(0x08, "I2C start");
				i2cSend(eeprom_addr | ((addr & 0x100) >> 7));
				i2cCheck(0x18, "I2C EEPROM write request");
				i2cSend(addr & 0xff);
				i2cCheck(0x28, "I2C EEPROM set address");
				i2cSend(seconds);
				i2cSend(minutes);
				i2cSend(hours);
				i2cStop();
				i2cCheck(0xf8, "I2C stop");
				printf("set time %02"PRIu8":%02"PRIu8":%02"PRIu8"\r\n", full_hours, full_minutes, full_seconds);

			}

		}
  	}
}

