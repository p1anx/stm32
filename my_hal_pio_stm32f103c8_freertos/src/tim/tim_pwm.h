#ifndef __TIM_H__
#define __TIM_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

extern TIM_HandleTypeDef htim_pwm;

#define TIM2_CH3_ON             1 //PA2

#define TIM_PWM_PSC             72-1
#define TIM_PWM_ARR             1000-1

#if TIM2_CH3_ON
#define TIM_PWM                         TIM2
#define TIM_PWM_CLK_ENABLE()            __HAL_RCC_TIM2_CLK_ENABLE()
#define TIM_PWM_CHANNEL_x               TIM_CHANNEL_3
#define TIM_PWM_IQRn                    TIM2_IRQn

#define TIM_PWM_GPIO_PIN                GPIO_PIN_2
#define TIM_PWM_GPIO_PORT               GPIOA
#define TIM_PWM_GPIO_CLK_ENABLE()       __HAL_RCC_GPIOA_CLK_ENABLE();
#endif


void TIM_PWM_Init(void);
void pwm_led_brth(int brth_time);


#ifdef __cplusplus
}
#endif

#endif /* __TIM_H__ */

