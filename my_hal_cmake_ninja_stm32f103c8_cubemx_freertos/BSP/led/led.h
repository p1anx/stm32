#ifndef __LED_H
#define __LED_H

#include "mymain.h"

#define LED1_GPIO_PIN  GPIO_PIN_1
#define LED1_GPIO_PORT GPIOA

#define LED1_TOGGLE() HAL_GPIO_TogglePin(LED1_GPIO_PORT, LED1_GPIO_PIN)

#define LED2_GPIO_PIN  GPIO_PIN_2
#define LED2_GPIO_PORT GPIOA

#define LED2_TOGGLE() HAL_GPIO_TogglePin(LED2_GPIO_PORT, LED2_GPIO_PIN)

void blink(void);


#endif // ! __LED_H
