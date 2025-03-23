#ifndef __KEY_H
#define	__KEY_H

#include "stm32f1xx.h"
#include "main.h"
//引脚定义
//野火stm32f103c8t6
//key1: PA0  key2: PC13
/*******************************************************/
#define KEY1_IsAvailable 		1
#define KEY2_IsAvailable 		1
#define KEY1_IT_EXTI_IsAvailable 1
#define KEY2_IT_EXTI_IsAvailable 0
 /** 按键按下标置宏
	* 按键按下为高电平，设置 KEY_ON=1， KEY_OFF=0
	* 若按键按下为低电平，把宏设置成KEY_ON=0 ，KEY_OFF=1 即可
	*/
#define KEY_ON	1
#define KEY_OFF	0

/*******************************************************/
//                     key1
/*******************************************************/

#define KEY1_PIN                  GPIO_PIN_0                 
#define KEY1_GPIO_PORT            GPIOA                      
#define KEY1_GPIO_CLK_ENABLE()    __HAL_RCC_GPIOA_CLK_ENABLE()

#define KEY1_IT_EXTI_IRQn         EXTI0_IRQn 
#define KEY1_IT_IRQHandler        EXTI0_IRQHandler

/*******************************************************/
//                     key2
/*******************************************************/

#define KEY2_PIN                  GPIO_PIN_13                 
#define KEY2_GPIO_PORT            GPIOC                      
#define KEY2_GPIO_CLK_ENABLE()     __HAL_RCC_GPIOC_CLK_ENABLE()

#define KEY2_IT_EXTI_IRQn         EXTI1_IRQn
#define KEY2_IT_IRQHandler        EXTI1_IRQHandler
/*******************************************************/


// uint8_t Key_Scan(GPIO_TypeDef* GPIOx,uint16_t GPIO_Pin);
uint8_t Key_Scan(int key_num);
void KEY_GPIO_Init(void);
void KEY1_GPIO_Init(void);
void KEY2_GPIO_Init(void);
void KEY1_IT_EXTI_Init(void);
void KEY2_IT_EXTI_Init(void);

#endif /* __LED_H */