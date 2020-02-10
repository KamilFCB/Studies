/******************************************************************************
 * Header file inclusions.
 ******************************************************************************/

#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "task.h"
#include "semphr.h"
#include <avr/io.h>
#include <avr/interrupt.h>

#include <stdio.h>
#include "uart.h"

/******************************************************************************
 * Private macro definitions.
 ******************************************************************************/

#define manageADC_TASK_PRIORITY   1

/******************************************************************************
 * Private function prototypes.
 ******************************************************************************/

static void manageADC(void* pvParameters);

/******************************************************************************
 * Public function definitions.
 ******************************************************************************/


SemaphoreHandle_t adc_mutex, read_mutex;

void adc_init() {
	ADMUX = _BV(REFS0);
	DIDR0 = _BV(ADC0D) | _BV(ADC1D) | _BV(ADC2D);
	ADCSRA = _BV(ADEN) | _BV(ADIE) | _BV(ADPS0) | _BV(ADPS1) | _BV(ADPS2);
}

ISR(ADC_vect) {
	xSemaphoreGiveFromISR(adc_mutex, NULL);
}

uint16_t readADC(uint8_t mux) {

	ADMUX = _BV(REFS0) | mux;
	ADCSRA |= _BV(ADSC);
	xSemaphoreTake(adc_mutex, portMAX_DELAY);
	uint16_t result = ADC;
	return result;
	
}

/**************************************************************************//**
 * \fn int main(void)
 *
 * \brief Main function.
 *
 * \return
 ******************************************************************************/
int main(void)
{
	uart_init();
    stdin = stdout = stderr = &uart_file;
	adc_init();
	sei();
	
	// Create task.
    xTaskHandle adc0_handle, adc1_handle, adc2_handle;

	adc_mutex = xSemaphoreCreateMutex();
	read_mutex = xSemaphoreCreateMutex();
	xSemaphoreTake(adc_mutex, portMAX_DELAY);


    xTaskCreate
        (
         manageADC,
         "adc0",
         configMINIMAL_STACK_SIZE,
         0,
         manageADC_TASK_PRIORITY,
         &adc0_handle
        );

	xTaskCreate
        (
         manageADC,
         "adc1",
         configMINIMAL_STACK_SIZE,
         1,
         manageADC_TASK_PRIORITY,
         &adc1_handle
        );

	xTaskCreate
        (
         manageADC,
         "adc2",
         configMINIMAL_STACK_SIZE,
         2,
         manageADC_TASK_PRIORITY,
         &adc2_handle
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

/**************************************************************************//**
 * \fn static void manageADC(void* pvParameters)
 *
 * \brief
 *
 * \param[in]   pvParameters
 ******************************************************************************/

static void manageADC(void* pvParameters)
{
	uint16_t adc_value;
    	uint8_t id = (uint8_t)pvParameters;
	char result[5];
	while (1) {
		xSemaphoreTake(read_mutex, portMAX_DELAY);
		adc_value = readADC(id);
		putchar('0'+id);
		utoa(adc_value, result, 10);
		putchar(':');
		puts(result);
		puts("\r\n");
		xSemaphoreGive(read_mutex);
		vTaskDelay(((id+1)*1000) / portTICK_PERIOD_MS);
	}
}
