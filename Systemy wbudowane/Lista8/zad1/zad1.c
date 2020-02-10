/******************************************************************************
 * Header file inclusions.
 ******************************************************************************/

#include "FreeRTOS.h"
#include "task.h"

#include <avr/io.h>


#include <stdio.h>
#include "uart.h"

/******************************************************************************
 * Private macro definitions.
 ******************************************************************************/

#define mainLED_TASK_PRIORITY   1

#define mainSERIAL_TASK_PRIORITY 1

#define LED PIND
#define LED_DDR DDRD
#define LED_PORT PORTD

#define BTN PB4
#define BTN_PIN PINB
#define BTN_PORT PORTB

/******************************************************************************
 * Private function prototypes.
 ******************************************************************************/

static void vBlinkLed(void* pvParameters);

static void vSerial(void* pvParameters);

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
    xTaskHandle blink_handle;
    xTaskHandle serial_handle;

    xTaskCreate
        (
         vBlinkLed,
         "blink",
         configMINIMAL_STACK_SIZE,
         NULL,
         mainLED_TASK_PRIORITY,
         &blink_handle
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

/**************************************************************************//**
 * \fn static void vBlinkLed(void* pvParameters)
 *
 * \brief
 *
 * \param[in]   pvParameters
 ******************************************************************************/

static void vBlinkLed(void* pvParameters)
{
    DDRB |= _BV(PB5);
	BTN_PORT |= _BV(BTN);
	int8_t cyclic_list[100];    
	while (1) {
		for (int8_t i = 0; i < 100; i++) {
			if (cyclic_list[i]) {
				PORTB |= _BV(PB5);
				cyclic_list[i] = 0;
			} else {
				PORTB &= ~_BV(PB5);
			}

			if (BTN_PIN & _BV(BTN)) {
				cyclic_list[i] = 0;
			} else {
				cyclic_list[i] = 1;
			}
			vTaskDelay(10 / portTICK_PERIOD_MS);
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
    LED_DDR = 0xff;
	UCSR0B &= ~_BV(RXEN0) & ~_BV(TXEN0);
	while (1) {
		for(int8_t i = 0; i < 10; i++)
		{
			if(i < 8)
				LED_PORT |= (1 << i);
			if(i-3 >= 0)
				LED_PORT &= ~(1 << i-3);
			if(i < 9)
				vTaskDelay(75 / portTICK_PERIOD_MS);
		}
		
		for(int8_t i = 8; i >= -2; i--)
		{
			if(i >= 0)
				LED_PORT |= (1 << i);
			if(i+3 >= 0)
				LED_PORT &= ~(1 << i+3);
			vTaskDelay(75 / portTICK_PERIOD_MS);
		}
	}
}
