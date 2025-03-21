#ifndef __TIM_TIMEBASE_H
#define __TIM_TIMEBASE_H

#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_tim.h"

extern TIM_HandleTypeDef        htim_timebase;
// void TIM3_IRQHandler(void);
/*************time base source config*************/
#define TIM_TIMEBASE                      TIM3
#define TIM_TIMEBASE_CLK_ENABLE()         __HAL_RCC_TIM3_CLK_ENABLE()
#define TIM_TIMEBASE_IRQHandler(void)     TIM3_IRQHandler(void)
#define TIM_TIMEBASE_IRQn                 TIM3_IRQn

#endif
