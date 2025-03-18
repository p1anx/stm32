# PWM输入捕获
## 1.1 method 1 
ref: https://www.cnblogs.com/zxr-blog/p/17966424
![img1](https://github.com/p1anx/stm32/blob/main/example/pwm/asset/2025-03-15_23-12.png)

## 1.2 slave mode trigger
### config image
![img2](https://github.com/p1anx/stm32/blob/main/example/pwm/asset/2025-03-15_23-33.png)
设置从模式为reset模式，触发源为TI1FP1可以实现CNT计数脉冲时，到达上升沿或者下降沿时，CNT置0。
### 1.3 同时测占空比和频率
![img3](https://github.com/p1anx/stm32/blob/main/example/pwm/asset/2025-03-16_00-11.png)
设置如上图
示例：
```c
uint32_t cap_val; //frequency
uint32_t cap_val1;//duty
HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_3);
HAL_TIM_IC_Start_IT(&htim1, TIM_CHANNEL_1);
HAL_TIM_IC_Start_IT(&htim1, TIM_CHANNEL_2);

int main(){
  while (1)
  {
    // printf("cap = %0.2f\n", cap_val/1000.0);
    // printf("cap1 = %0.2f\n", cap_val1/1000.0);
    // printf("cap_diff = %0.2f\n", (cap_val1-cap_val)/1000.0);
    printf("cap = %d\n", cap_val);
    printf("cap1 = %d\n", cap_val1);
  }

}
  //回调函数
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim){
  if(htim->Instance == TIM1){
//获得频率的cnt值，具体计算需要根据psc的值，如时钟为72M，psc为71,cap_val is 1000, then real frequency is 72M/(71+1)/cap_val
    cap_val = HAL_TIM_ReadCapturedValue(&htim1, TIM_CHANNEL_1);
    //duty is cap_val/cap_val1 * 100
    cap_val1 = HAL_TIM_ReadCapturedValue(&htim1, TIM_CHANNEL_2);
  }

}

```
