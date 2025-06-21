#include "led.h"

void blink(void) {
    LED1_TOGGLE();
    HAL_Delay(1000);
}