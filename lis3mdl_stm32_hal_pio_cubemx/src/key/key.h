#ifndef __KEY_IT_H
#define __KEY_IT_H

#include "mymain.h"

#define KEY_ON  1    
#define KEY_OFF 0    

#define KEY1_GPIO_PORT   GPIOA
#define KEY1_GPIO_PIN    GPIO_PIN_0

#define KEY2_GPIO_PORT   GPIOC
#define KEY2_GPIO_PIN    GPIO_PIN_13

#define KEY3_GPIO_PORT   GPIOA
#define KEY3_GPIO_PIN    GPIO_PIN_4
uint8_t Key_Scan(int key);

#endif
