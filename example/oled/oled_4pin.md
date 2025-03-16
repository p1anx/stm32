## 1 cubemx setting
![img1](https://github.com/p1anx/stm32/blob/main/example/oled/asset/2025-03-16_21-26.png)
## 2 code 
for HAL, rewrite code as follow
```c 
void OLED_W_SCL(uint8_t BitValue)
{
	/*根据BitValue的值，将SCL置高电平或者低电平*/
	// GPIO_WriteBit(GPIOB, GPIO_Pin_8, (BitAction)BitValue);
 	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, BitValue); 
	
	/*如果单片机速度过快，可在此添加适量延时，以避免超出I2C通信的最大速度*/
	//...
}

/**
  * 函    数：OLED写SDA高低电平
  * 参    数：要写入SDA的电平值，范围：0/1
  * 返 回 值：无
  * 说    明：当上层函数需要写SDA时，此函数会被调用
  *           用户需要根据参数传入的值，将SDA置为高电平或者低电平
  *           当参数传入0时，置SDA为低电平，当参数传入1时，置SDA为高电平
  */
void OLED_W_SDA(uint8_t BitValue)
{
	/*根据BitValue的值，将SDA置高电平或者低电平*/
	// GPIO_WriteBit(GPIOB, GPIO_Pin_9, (BitAction)BitValue);
 	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, BitValue); 
	
	/*如果单片机速度过快，可在此添加适量延时，以避免超出I2C通信的最大速度*/
	//...
}

```
