# PWM输入捕获
## 1.1 method 1 
ref: https://www.cnblogs.com/zxr-blog/p/17966424
![img1](https://github.com/p1anx/stm32/blob/main/example/pwm/asset/2025-03-15_23-12.png)

## 1.2 slave mode trigger
### config image
![img2](https://github.com/p1anx/stm32/blob/main/example/pwm/asset/2025-03-15_23-33.png)
设置从模式为reset模式，触发源为TI1FP1可以实现CNT计数脉冲时，到达上升沿或者下降沿时，CNT置0。
