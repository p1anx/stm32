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
void KEY1_GPIO_Init(void)

{

    GPIO_InitTypeDef GPIO_InitStruct;

    /*开启按键GPIO口的时钟*/
    KEY1_GPIO_CLK_ENABLE();

    /*选择按键的引脚*/	
    GPIO_InitStruct.Pin = KEY1_PIN; 
    /*设置引脚为输入模式*/
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT; 
    /*设置引脚不上拉也不下拉*/
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    /*使用上面的结构体初始化按键*/
    HAL_GPIO_Init(KEY1_GPIO_PORT, &GPIO_InitStruct);

    /*选择按键KEY2的引脚*/
    // GPIO_InitStruct.Pin = KEY2_PIN; 
    // /*使用上面的结构体初始化按键*/
    // HAL_GPIO_Init(KEY2_GPIO_PORT, &GPIO_InitStruct);
}

void KEY2_GPIO_Init(void)
{

    GPIO_InitTypeDef GPIO_InitStruct;

    /*开启按键GPIO口的时钟*/
    KEY2_GPIO_CLK_ENABLE();

    /*选择按键的引脚*/	
    GPIO_InitStruct.Pin = KEY2_PIN; 
    /*设置引脚为输入模式*/
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT; 
    /*设置引脚不上拉也不下拉*/
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    /*使用上面的结构体初始化按键*/
    HAL_GPIO_Init(KEY2_GPIO_PORT, &GPIO_InitStruct);

}

// set interrupt
void KEY1_IT_EXTI_Init(void)
{
    HAL_NVIC_SetPriority(KEY1_IT_EXTI_IRQn, 5, 0);
    /* 使能中断 */
    HAL_NVIC_EnableIRQ(KEY1_IT_EXTI_IRQn);

}
void KEY2_IT_EXTI_Init(void)
{
    HAL_NVIC_SetPriority(KEY2_IT_EXTI_IRQn, 5, 0);
    /* 使能中断 */
    HAL_NVIC_EnableIRQ(KEY2_IT_EXTI_IRQn);

}

uint8_t Key_Scan(int key_num)
{			
	/*检测是否有按键按下 */
  if(key_num == 1){
    if(HAL_GPIO_ReadPin(KEY1_GPIO_PORT,KEY1_PIN) == KEY_ON )  
    {	 
      /*等待按键释放 */
      while(HAL_GPIO_ReadPin(KEY1_GPIO_PORT,KEY1_PIN) == KEY_ON);   
      return 	KEY_ON;	 
    }
    else
      return KEY_OFF;

  }
  else if(key_num == 2)
  {
    if(HAL_GPIO_ReadPin(KEY2_GPIO_PORT,KEY2_PIN) == KEY_ON )  
    {	 
      /*等待按键释放 */
      while(HAL_GPIO_ReadPin(KEY2_GPIO_PORT,KEY2_PIN) == KEY_ON);   
      return 	KEY_ON;	 
    }
    else
      return KEY_OFF;

  }
}

void KEY_GPIO_Init(void){
  // key1 init
  if(KEY1_IsAvailable)
  {
    KEY1_GPIO_Init();
    if(KEY1_IT_EXTI_IsAvailable)
    {
      KEY1_IT_EXTI_Init();
    }
  }
  // key2 init
  if(KEY2_IsAvailable)
  {
    KEY2_GPIO_Init();
    if(KEY2_IT_EXTI_IsAvailable)
    {
      KEY2_IT_EXTI_Init();
    }
  }
}
/*********************************************END OF FILE**********************/