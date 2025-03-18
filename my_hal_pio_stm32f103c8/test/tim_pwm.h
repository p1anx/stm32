#ifndef __ADVANCE_TIM_H
#define	__ADVANCE_TIM_H

#include "stm32f1xx.h"

/* 定时器 */
#define ADVANCE_TIM           				    TIM2
#define ADVANCE_TIM_CLK_ENABLE()  			  __HAL_RCC_TIM2_CLK_ENABLE()
 
/* TIM1通道1输出引脚 */
#define ADVANCE_OCPWM_PIN           		  GPIO_PIN_10             
#define ADVANCE_OCPWM_GPIO_PORT     		  GPIOB                    
#define ADVANCE_OCPWM_GPIO_CLK_ENABLE() 	__HAL_RCC_GPIOB_CLK_ENABLE()

#define TIM_CHANNEL_X                       TIM_CHANNEL_3

#define TIM_PSC                             72-1
#define TIM_ARR                             1000-1

/* TIM1通道1互补输出引脚 */
#define ADVANCE_OCNPWM_PIN            		GPIO_PIN_7              
#define ADVANCE_OCNPWM_GPIO_PORT      		GPIOA                     
#define ADVANCE_OCNPWM_GPIO_CLK_ENABLE()	__HAL_RCC_GPIOA_CLK_ENABLE()

extern TIM_HandleTypeDef htim1;

void TIMx_Configuration(void);

#endif /* __ADVANCE_TIM_H */