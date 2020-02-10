#include <avr/io.h>
#include <stdio.h>
#include <inttypes.h>
#include <stdlib.h>
#include <string.h>
#include "i2c.h"

#define BAUD 9600                          // baudrate
#define UBRR_VALUE ((F_CPU)/16/(BAUD)-1)   // zgodnie ze wzorem
#define BUFFER_SIZE 50
#define DATA_SIZE 16

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

const uint8_t eeprom_addr = 0xa0;

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
	uint8_t length = 0;
	uint8_t checksum = 0;
	uint8_t value = 0;
  	#define i2cCheck(code, msg) \
    	if ((TWSR & 0xf8) != (code)) { \
      		printf(msg " failed, status: %.2x\r\n", TWSR & 0xf8); \
      		i2cReset(); \
      		continue; \
    	}
	char buffer[BUFFER_SIZE];
  	while(1) {
		scanf("%s", buffer);
		if (strcmp(buffer, "read") == 0) {
			scanf("%s", buffer);
			addr = strtol(buffer, NULL, 16);
			scanf("%s", buffer);
			length = strtol(buffer, NULL, 10);
			printf("read %04x"PRIu16" %"PRIu8"\r\n", addr, length);
			i2cStart();
			i2cCheck(0x08, "I2C start")
			i2cSend(eeprom_addr | ((addr & 0x100) >> 7));
			i2cCheck(0x18, "I2C EEPROM write request")
			i2cSend(addr & 0xff);
			i2cCheck(0x28, "I2C EEPROM set address")
			i2cStart();
			i2cCheck(0x10, "I2C second start")
			i2cSend(eeprom_addr | 0x1 | ((addr & 0x100) >> 7));
			i2cCheck(0x40, "I2C EEPROM read request")
			uint8_t records = length / DATA_SIZE;
			uint8_t last_record_length = length % DATA_SIZE;

			for (int8_t i = records; i >= 0; i--) {
				char result[40] = {0};
				char byte_count[3] = {0};
				char address[5] = {0};
				char checksum_str[3] = {0};
				char tmp[3];
				uint8_t record_length = i > 0 ? DATA_SIZE : last_record_length;
				checksum = record_length + addr;
				// : record_length addr 00
				for (uint8_t j = 0; j < record_length; j++) {
					uint8_t data = j == record_length - 1 && i == 0 ? i2cReadNoAck() : i2cReadAck(); // ()
					checksum += data;
					sprintf(tmp, "%02x", data);
					//printf("%s\r\n", tmp);
					//printf("%"PRIu16"\r\n", checksum);
					strcat(result, tmp);
				}
				//itoa(checksum & 0xff, tmp, 16);
				//strcat(result, tmp);
				sprintf(checksum_str, "%02x", checksum);
				sprintf(address, "%04x", addr);
				sprintf(byte_count, "%02x", record_length);
				printf(":%s%s00%s%s\r\n", byte_count, address, result, checksum_str);
				addr += DATA_SIZE;
			}			
			i2cStop();
			i2cCheck(0xf8, "I2C stop")
			printf(":00000001ff\r\n");
			
			
		} else if (strcmp(buffer, "write") == 0) {
			printf("write ");
			while (1) {
				buffer[0] = '\0';
				scanf("%s", buffer);
			 	if (strcmp(buffer, ":00000001ff") == 0) 
					break;
				
				char byte_count[3];
				char address[5];
				char checksum_str[3];
				char tmp[3];
				snprintf(byte_count, 3, "%s", &buffer[1]);
				snprintf(address, 5, "%s", &buffer[3]);
				addr = strtol(address, NULL, 16);
				uint8_t record_length = strtol(byte_count, NULL, 16);
				snprintf(checksum_str, 3, "%s", &buffer[9 + (2 * record_length)]);
				checksum = addr + record_length;

				for(uint8_t i = 0; i < record_length; i++) {
					snprintf(tmp, 3, "%s", &buffer[9 + (2 * i)]);
					checksum += strtol(tmp, NULL, 16);
					//printf("%"PRIu16"\r\n", checksum);
				}
				uint16_t tmp_checksum = strtol(checksum_str, NULL, 16);
				
				if ((checksum & 0xff) != tmp_checksum) {
					printf("%s wrong checksum\r\n", buffer);
					break;
				}

				i2cStart();
				i2cCheck(0x08, "I2C start")
				i2cSend(eeprom_addr | ((addr & 0x100) >> 7));
				i2cCheck(0x18, "I2C EEPROM write request");
				i2cSend(addr & 0xff);
				i2cCheck(0x28, "I2C EEPROM set address");
				for(uint8_t i = 0; i < record_length; i++) {
					snprintf(tmp, 3, "%s", &buffer[9 + (2 * i)]);
					value = strtol(tmp, NULL, 16);
					i2cSend(value);
				}
				i2cStop();
				i2cCheck(0xf8, "I2C stop");
				printf("%s\r\n", buffer);
			}
		}
  	}
}

