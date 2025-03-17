/**
  ******************************************************************************
  * @file    bsp_advance_tim.c
  * @author  STMicroelectronics
  * @version V1.0
  * @date    2015-xx-xx
  * @brief   高级控制定时器定时范例
  ******************************************************************************
  * @attention
  *
  * 实验平台:野火  STM32 F103 开发板  
  * 论坛    :http://www.firebbs.cn
  * 淘宝    :http://firestm32.taobao.com
  *
  ******************************************************************************
  */
  
#include "tim_pwm.h"

TIM_HandleTypeDef htim1;

__IO uint16_t ChannelPulse = 500;

/**
  * @brief  配置TIM复用输出PWM时用到的I/O
  * @param  无
  * @retval 无
  */
// void HAL_TIM_Base_MspInit(TIM_HandleTypeDef* tim_baseHandle)
// {

//   if(tim_baseHandle->Instance==TIM2)
//   {
//     __HAL_RCC_TIM2_CLK_ENABLE();
//   }
// }
static void TIMx_GPIO_Config(void) 
{
	/*定义一个GPIO_InitTypeDef类型的结构体*/
	GPIO_InitTypeDef GPIO_InitStructure;

	/*开启定时器相关的GPIO外设时钟*/
	ADVANCE_OCPWM_GPIO_CLK_ENABLE();
	// ADVANCE_OCNPWM_GPIO_CLK_ENABLE();

	/* 定时器功能引脚初始化 */															   
	GPIO_InitStructure.Pin = ADVANCE_OCPWM_PIN;	
	GPIO_InitStructure.Mode = GPIO_MODE_AF_PP;    
	GPIO_InitStructure.Pull = GPIO_NOPULL;
	GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH; 	
	HAL_GPIO_Init(ADVANCE_OCPWM_GPIO_PORT, &GPIO_InitStructure);	

	GPIO_InitStructure.Pin = ADVANCE_OCNPWM_PIN;	
	HAL_GPIO_Init(ADVANCE_OCNPWM_GPIO_PORT, &GPIO_InitStructure);
	
	
}

/*
 * 注意：TIM_TimeBaseInitTypeDef结构体里面有5个成员，TIM6和TIM7的寄存器里面只有
 * TIM_Prescaler和TIM_Period，所以使用TIM6和TIM7的时候只需初始化这两个成员即可，
 * 另外三个成员是通用定时器和高级定时器才有.
 *-----------------------------------------------------------------------------
 * TIM_Prescaler         都有
 * TIM_CounterMode			 TIMx,x[6,7]没有，其他都有（基本定时器）
 * TIM_Period            都有
 * TIM_ClockDivision     TIMx,x[6,7]没有，其他都有(基本定时器)
 * TIM_RepetitionCounter TIMx,x[1,8]才有(高级定时器)
 *-----------------------------------------------------------------------------
 */
// void MX_TIM1_Init(void)
// {

//   /* USER CODE BEGIN TIM1_Init 0 */

//   /* USER CODE END TIM1_Init 0 */

//   TIM_ClockConfigTypeDef sClockSourceConfig = {0};
//   TIM_MasterConfigTypeDef sMasterConfig = {0};
//   TIM_OC_InitTypeDef sConfigOC = {0};
//   TIM_BreakDeadTimeConfigTypeDef sBreakDeadTimeConfig = {0};

//   /* USER CODE BEGIN TIM1_Init 1 */
//   ADVANCE_TIM_CLK_ENABLE();

//   /* USER CODE END TIM1_Init 1 */
//   htim1.Instance = ADVANCE_TIM;
//   htim1.Init.Prescaler = 71;
//   htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
//   htim1.Init.Period = 1000-1;
//   htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
//   htim1.Init.RepetitionCounter = 0;
//   htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
//   if (HAL_TIM_Base_Init(&htim1) != HAL_OK)
//   {
//     // Error_Handler();
//   }
//   sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
//   if (HAL_TIM_ConfigClockSource(&htim1, &sClockSourceConfig) != HAL_OK)
//   {
//     // Error_Handler();
//   }
//   if (HAL_TIM_PWM_Init(&htim1) != HAL_OK)
//   {
//     // Error_Handler();
//   }
//   sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
//   sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
//   if (HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig) != HAL_OK)
//   {
//     // Error_Handler();
//   }
//   sConfigOC.OCMode = TIM_OCMODE_PWM1;
//   sConfigOC.Pulse = 0;
//   sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
//   sConfigOC.OCNPolarity = TIM_OCNPOLARITY_HIGH;
//   sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
//   sConfigOC.OCIdleState = TIM_OCIDLESTATE_RESET;
//   sConfigOC.OCNIdleState = TIM_OCNIDLESTATE_RESET;
//   if (HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_X) != HAL_OK)
//   {
//     // Error_Handler();
//   }
//   sBreakDeadTimeConfig.OffStateRunMode = TIM_OSSR_DISABLE;
//   sBreakDeadTimeConfig.OffStateIDLEMode = TIM_OSSI_DISABLE;
//   sBreakDeadTimeConfig.LockLevel = TIM_LOCKLEVEL_OFF;
//   sBreakDeadTimeConfig.DeadTime = 0;
//   sBreakDeadTimeConfig.BreakState = TIM_BREAK_DISABLE;
//   sBreakDeadTimeConfig.BreakPolarity = TIM_BREAKPOLARITY_HIGH;
//   sBreakDeadTimeConfig.AutomaticOutput = TIM_AUTOMATICOUTPUT_DISABLE;
//   if (HAL_TIMEx_ConfigBreakDeadTime(&htim1, &sBreakDeadTimeConfig) != HAL_OK)
//   {
//     // Error_Handler();
//   }
//   /* USER CODE BEGIN TIM1_Init 2 */
// 	HAL_TIM_Base_Start(&htim1);
// 	HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_X);

//   /* USER CODE END TIM1_Init 2 */
// //   HAL_TIM_MspPostInit(&htim1);

// }


/******************************************************************************/
static void TIM_Mode_Config(void){
	TIM_ClockConfigTypeDef sClockSourceConfig = {0};
	TIM_MasterConfigTypeDef sMasterConfig = {0};
	TIM_OC_InitTypeDef sConfigOC = {0};
	TIM_BreakDeadTimeConfigTypeDef TIM_BDTRInitStructure;

	// 开启TIMx_CLK,x[1,8] 
	ADVANCE_TIM_CLK_ENABLE(); 
	/* 定义定时器的句柄即确定定时器寄存器的基地址*/
	htim1.Instance = ADVANCE_TIM;
	/* 累计 TIM_Period个后产生一个更新或者中断*/		
	//当定时器从0计数到999，即为1000次，为一个定时周期
	htim1.Init.Period = TIM_ARR;
	// 高级控制定时器时钟源TIMxCLK = HCLK=168MHz 
	// 设定定时器频率为=TIMxCLK/(TIM_Prescaler+1)=1MHz
	htim1.Init.Prescaler = TIM_PSC;	
	// 采样时钟分频
	htim1.Init.ClockDivision=TIM_CLOCKDIVISION_DIV1;
	// 计数方式
	htim1.Init.CounterMode=TIM_COUNTERMODE_UP;
	// 重复计数器
	htim1.Init.RepetitionCounter=0;	
	htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
	// 初始化定时器TIMx, x[1,8]
	HAL_TIM_PWM_Init(&htim1);

	/*PWM模式配置*/
	//配置为PWM模式1
	// TIM_OCInitStructure.OCMode = TIM_OCMODE_PWM1;
	// TIM_OCInitStructure.Pulse = ChannelPulse;
	// TIM_OCInitStructure.OCPolarity = TIM_OCPOLARITY_HIGH;
	// TIM_OCInitStructure.OCNPolarity = TIM_OCNPOLARITY_HIGH;
	// TIM_OCInitStructure.OCIdleState = TIM_OCIDLESTATE_SET;
	// TIM_OCInitStructure.OCNIdleState = TIM_OCNIDLESTATE_RESET;
	//初始化通道1输出PWM 
	// HAL_TIM_PWM_ConfigChannel(&htim1,&TIM_OCInitStructure,TIM_CHANNEL_X);

	// sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
	if (HAL_TIM_ConfigClockSource(&htim1, &sClockSourceConfig) != HAL_OK)
	{
		Error_Handler();
	}
	// if (HAL_TIM_PWM_Init(&htim1) != HAL_OK)
	// {
	// 	Error_Handler();
	// }
	sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
	sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
	if (HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig) != HAL_OK)
	{
		Error_Handler();
	}
	sConfigOC.OCMode = TIM_OCMODE_PWM1;
	sConfigOC.Pulse = ChannelPulse;
	// sConfigOC.OCIdleState = TIM_OCIDLESTATE_SET;
	sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
	sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
	if (HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_X) != HAL_OK)
	{
		Error_Handler();
	}
	/* 自动输出使能，断路、死区时间和锁定配置 */
	TIM_BDTRInitStructure.OffStateRunMode = TIM_OSSR_ENABLE;
	TIM_BDTRInitStructure.OffStateIDLEMode = TIM_OSSI_ENABLE;
	TIM_BDTRInitStructure.LockLevel = TIM_LOCKLEVEL_1;
	TIM_BDTRInitStructure.DeadTime = 11;
	TIM_BDTRInitStructure.BreakState = TIM_BREAK_ENABLE;
	TIM_BDTRInitStructure.BreakPolarity = TIM_BREAKPOLARITY_LOW;
	TIM_BDTRInitStructure.AutomaticOutput = TIM_AUTOMATICOUTPUT_ENABLE;
	HAL_TIMEx_ConfigBreakDeadTime(&htim1, &TIM_BDTRInitStructure);

	/* 定时器通道1输出PWM */
	HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_X);
	/* 定时器通道1互补输出PWM */
	HAL_TIMEx_PWMN_Start(&htim1,TIM_CHANNEL_X);
}

/**
  * @brief  初始化高级控制定时器定时，1s产生一次中断
  * @param  无
  * @retval 无
  */
void TIMx_Configuration(void)
{
	TIMx_GPIO_Config();	

	TIM_Mode_Config();
    // MX_TIM1_Init();
}
/*********************************************END OF FILE**********************/