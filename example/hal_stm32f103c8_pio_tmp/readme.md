## TIM BASE
### main.c
```c
#include "led.h"
#include "tim_base.h"
volatile uint32_t time ; // ms 计时变量
int main(void){
    LED_GPIO_Init();
    TIMx_Base_Init();
    HAL_TIM_Base_Start_IT(&htimx);
    while(1){
      if(time == 500){
        time = 0;
        LEDx_TOGGLE;
      }

    }

} 
```

### stm32xxxx.it
```c
#include "tim_base.h"
void BASIC_TIM_INT_FUN(void)
{
  HAL_TIM_IRQHandler(&htimx);
}
```

