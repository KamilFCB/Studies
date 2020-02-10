/******************************************************************************
 * Header file inclusions.
 ******************************************************************************/

#include "FreeRTOS.h"
#include "task.h"

#include <avr/io.h>


#include <stdio.h>
#include <stdlib.h>
#include "uart.h"

/******************************************************************************
 * Private macro definitions.
 ******************************************************************************/

#define mainHEATER_PRIORITY   1

#define mainSERIAL_TASK_PRIORITY 1

#define LED PB5
#define LED_DDR DDRB
#define LED_PORT PORTB

/******************************************************************************
 * Private function prototypes.
 ******************************************************************************/

static void vHeater(void* pvParameters);

static void vSerial(void* pvParameters);

uint16_t temperature, T = 30;

/******************************************************************************
 * Public function definitions.
 ******************************************************************************/

/**************************************************************************//**
 * \fn int main(void)
 *
 * \brief Main function.
 *
 * \return
 ******************************************************************************/
int main(void)
{
    // Create task.
    xTaskHandle heater_handle;
    xTaskHandle serial_handle;

    xTaskCreate
        (
         vHeater,
         "heater",
         configMINIMAL_STACK_SIZE,
         NULL,
         mainHEATER_PRIORITY,
         &heater_handle
        );

    xTaskCreate
        (
         vSerial,
         "serial",
         configMINIMAL_STACK_SIZE,
         NULL,
         mainSERIAL_TASK_PRIORITY,
         &serial_handle
        );

    // Start scheduler.
    vTaskStartScheduler();

    return 0;
}

/**************************************************************************//**
 * \fn static vApplicationIdleHook(void)
 *
 * \brief
 ******************************************************************************/
void vApplicationIdleHook(void)
{

}

/******************************************************************************
 * Private function definitions.
 ******************************************************************************/
// inicjalizacja ADC
void adc_init()
{
  	ADMUX   = _BV(REFS0) | _BV(REFS1); // referencja AVcc, wejście ADC0
  	DIDR0   = _BV(ADC0D); // wyłącz wejście cyfrowe na ADC0
  	// częstotliwość zegara ADC 125 kHz (16 MHz / 128)
  	ADCSRA  = _BV(ADPS0) | _BV(ADPS1) | _BV(ADPS2); // preskaler 128
	ADCSRA |= _BV(ADEN); // włącz ADC 
}



uint16_t get_temperatureX10()
{
	ADCSRA |= _BV(ADSC);
	while((ADCSRA & _BV(ADSC)));
	return (ADC * (1100 / 1024)) - 500;
}

/**************************************************************************//**
 * \fn static void vBlinkLed(void* pvParameters)
 *
 * \brief
 *
 * \param[in]   pvParameters
 ******************************************************************************/
static void vHeater(void* pvParameters)
{
    LED_DDR |= _BV(LED);
	adc_init();
    for ( ;; )
    {
		temperature = get_temperatureX10();
        LED_PORT |= _BV(LED);
		while (temperature / 10 < T) {
			vTaskDelay(100 / portTICK_PERIOD_MS);
			temperature = get_temperatureX10();
		}
		LED_PORT &= ~_BV(LED);
		temperature = get_temperatureX10();
		while ((temperature / 10) >= T - 1) {
			vTaskDelay(100 / portTICK_PERIOD_MS);
			temperature = get_temperatureX10();
		}
    }
}


/**************************************************************************//**
 * \fn static void vSerial(void* pvParameters)
 *
 * \brief
 *
 * \param[in]   pvParameters
 ******************************************************************************/
static void vSerial(void* pvParameters)
{
    uart_init();
    stdin = stdout = stderr = &uart_file;

    char c;
	uint16_t value;
	char buffer[5];

    for ( ;; )
    {
        c = getchar();
		if (c == 'g') {
			utoa(temperature / 10, buffer, 10);
			puts("Temperatura: ");
			puts(buffer);
			puts("\r\n");
		}
		else if (c == 's') {
			value = 0;
			c = getchar();
			while (c >= '0' && c <= '9') {
				value = value * 10 + (c - '0');
				c = getchar();
			}
			T = value;
			utoa(T, buffer, 10);
			puts("Ustawiono temperature: ");
			puts(buffer);
			puts("\r\n");
		}
		else {
			puts("Zla komenda\r\n");
		}
		vTaskDelay(250 / portTICK_PERIOD_MS);
    }
}
