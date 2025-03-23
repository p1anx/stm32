#ifndef __MAIN_H
#define __MAIN_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"
#include "led.h"
#include "usart.h"
#include "tim_pwm.h"
#include "OLED.h"
#include "key.h"

static void SystemClock_Config(void);
void Error_Handler(void);

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
