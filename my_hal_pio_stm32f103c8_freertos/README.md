## Issues
### (1) if freertos is used, GPIO exti can't work


## change the `time base source`
1. The modified content is as shown in `stm32f1xx_hal_timebase_tim.c` and `stm32f1xx_hal_timebase_tim.c`
2. The most important thing is below.
In `stm32f1xx_it.c` file, add the following content
```c
void TIM_TIMEBASE_IRQHandler(void)
{
  HAL_TIM_IRQHandler(&htim_timebase);
}
// callback function adds `HAL_IncTick()`
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  if (htim->Instance == TIM_TIMEBASE) {
    HAL_IncTick();
  }
}
```
3. In `main.c`, place `HAL_Init()` at the beginning of `main` function,
```c
int main(void)
{
    HAL_Init();
    /* 系统时钟初始化成72 MHz */
    SystemClock_Config();
}
```

# FreeRTOS 
