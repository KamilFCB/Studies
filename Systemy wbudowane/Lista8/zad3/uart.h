#ifndef _UART_H
#define _UART_H

#include "queue.h"

void uart_init(void);

FILE uart_file;
QueueHandle_t buffer_in, buffer_out;
xTaskHandle blink_handle;
xTaskHandle serial_handle;

#endif
