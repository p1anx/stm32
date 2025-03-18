/**
  ******************************************************************************
  * @file    bsp_key.c
  * @author  fire
  * @version V1.0
  * @date    2015-xx-xx
  * @brief   按键应用bsp（扫描模式）
  ******************************************************************************
  * @attention
  *
  * 实验平台:野火  STM32 F103 开发板 
  * 论坛    :http://www.firebbs.cn
  * 淘宝    :http://firestm32.taobao.com
  *
  ******************************************************************************
  */ 

#include "key.h" 

/**
  * @brief  配置按键用到的I/O口
  * @param  无
  * @retval 无
  */
void Key_GPIO_Init(void)

{

    GPIO_InitTypeDef GPIO_InitStruct;

    /*开启按键GPIO口的时钟*/
    KEYx_GPIO_CLK_ENABLE();

    /*选择按键的引脚*/	
    GPIO_InitStruct.Pin = KEYx_PIN; 
    /*设置引脚为输入模式*/
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT; 
    /*设置引脚不上拉也不下拉*/
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    /*使用上面的结构体初始化按键*/
    HAL_GPIO_Init(KEYx_GPIO_PORT, &GPIO_InitStruct);

    /*选择按键KEY2的引脚*/
    // GPIO_InitStruct.Pin = KEY2_PIN; 
    // /*使用上面的结构体初始化按键*/
    // HAL_GPIO_Init(KEY2_GPIO_PORT, &GPIO_InitStruct);
 
}



/**
  * @brief   检测是否有按键按下
  * @param   具体的端口和端口位
  *		@arg GPIOx: x可以是（A...G） 
  *		@arg GPIO_PIN 可以是GPIO_PIN_x（x可以是1...16）
  * @retval  按键的状态
  *		@arg KEY_ON:按键按下
  *		@arg KEY_OFF:按键没按下
  */

uint8_t Key_Scan(GPIO_TypeDef* GPIOx,uint16_t GPIO_Pin)
{			
	/*检测是否有按键按下 */
	if(HAL_GPIO_ReadPin(GPIOx,GPIO_Pin) == KEY_ON )  
	{	 
		/*等待按键释放 */
		while(HAL_GPIO_ReadPin(GPIOx,GPIO_Pin) == KEY_ON);   
		return 	KEY_ON;	 
	}
	else
		return KEY_OFF;
}

/*********************************************END OF FILE**********************/