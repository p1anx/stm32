/** 
  ******************************************************************************
  * @file    GPIO/GPIO_IOToggle/Src/stm32f1xx_it.c
  * @author  MCD Application Team
  * @version V1.5.0
  * @date    14-April-2017
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and
  *          peripherals interrupt service routine.
  ******************************************************************************

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f1xx_it.h"
#include "led.h"
#include "stm32f1xx_hal_timebase_tim.h"
#include "key.h"
// #include "tim_base.h"
// #include "tim_ic.h"



/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

void KEY1_IT_IRQHandler(void)
{
  //确保是否产生了EXTI Line中断
	// if(__HAL_GPIO_EXTI_GET_IT(KEY1_PIN) != RESET) 
	// {
	// 	// LED1 取反		
	// 	LED1_TOGGLE();
  //       //清除中断标志位
	// 	__HAL_GPIO_EXTI_CLEAR_IT(KEY1_PIN);     
	// }  
  HAL_GPIO_EXTI_IRQHandler(KEY1_PIN);

}        

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  if(GPIO_Pin == KEY1_PIN)
  {
    LED1_TOGGLE();
  }
}
/******************************************************************************/
/*                time base source handler                                   */
/******************************************************************************/

void TIM_TIMEBASE_IRQHandler(void)
{
  HAL_TIM_IRQHandler(&htim_timebase);
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  if (htim->Instance == TIM_TIMEBASE) {
    HAL_IncTick();
  }
}



/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
// void SVC_Handler(void)
// {
// }

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
// void PendSV_Handler(void)
// {
// }

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
// void SysTick_Handler(void)
// {
//   HAL_IncTick();
// }

/******************************************************************************/
/*                 STM32F1xx Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f1xx.s).                                               */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/


/**
  * @}
  */

/**
  * @}
  */
/**********************EXTI*****************************/
// void KEY1_IRQHandler(void)
// {
//   //确保是否产生了EXTI Line中断
// 	if(__HAL_GPIO_EXTI_GET_IT(KEY1_INT_GPIO_PIN) != RESET) 
// 	{
// 		// LED1 取反		
// 		LEDx_TOGGLE;
//     //清除中断标志位
// 		__HAL_GPIO_EXTI_CLEAR_IT(KEY1_INT_GPIO_PIN);     
// 	}  
// }

// void KEY2_IRQHandler(void)
// {
//   //确保是否产生了EXTI Line中断
// 	if(__HAL_GPIO_EXTI_GET_IT(KEY2_INT_GPIO_PIN) != RESET) 
// 	{
// 		// LED2 取反		
// 		LED2_TOGGLE;
//     //清除中断标志位
// 		__HAL_GPIO_EXTI_CLEAR_IT(KEY2_INT_GPIO_PIN);     
// 	}  
// }



/**********************UART RX interrupt*****************************/
//uart中断回显实验
// extern uint8_t Rxflag;
// void  DEBUG_USART_IRQHandler(void)
// {
//   uint8_t ch=0; 
  
// 	if(__HAL_UART_GET_FLAG( &huart1, UART_FLAG_RXNE ) != RESET)
// 	{		
//     ch=( uint16_t)READ_REG(huart1.Instance->DR);
//     WRITE_REG(huart1.Instance->DR,ch); 
 
// 	}
// }

/**********************TIM BASE interrupt*****************************/
// extern volatile uint32_t time ; // ms 计时变量
// void BASIC_TIM_INT_FUN(void)
// {
//   HAL_TIM_IRQHandler(&htimx);
// }
// void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
// {
//   time++;
// }


/**********************TIM IC interrupt*****************************/
// void GENERAL_TIM_IRQHANDLER(void)
// { 
//   HAL_TIM_IRQHandler(&TIM_TimeBase); 
// }
// // update interrupt
// void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
// {
//   TIM_ICUserValueStructure .usPeriod ++;
// }

// // input capture interrupt
// void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
// {
//   TIM_IC_InitTypeDef IC_Config;
  
//   if ( TIM_ICUserValueStructure .ucStartFlag == 0 )
//   {
//     LEDx_TOGGLE;       
    
//     __HAL_TIM_SET_COUNTER(htim,0); // 清零定时器计数
//     TIM_ICUserValueStructure .usPeriod = 0;			
//     TIM_ICUserValueStructure .usCtr = 0;
    
//     // 配置输入捕获参数，主要是修改触发电平
//     IC_Config.ICPolarity = GENERAL_TIM_END_ICPolarity;
//     IC_Config.ICSelection = TIM_ICSELECTION_DIRECTTI;
//     IC_Config.ICPrescaler = TIM_ICPSC_DIV1;
//     IC_Config.ICFilter = 0;
//     HAL_TIM_IC_ConfigChannel(&TIM_TimeBase, &IC_Config, GENERAL_TIM_CHANNELx);
//     // 清除中断标志位
//     __HAL_TIM_CLEAR_IT(htim, GENERAL_TIM_IT_CCx);
//     // 启动输入捕获并开启中断
//     HAL_TIM_IC_Start_IT(&TIM_TimeBase,GENERAL_TIM_CHANNELx);    
//     TIM_ICUserValueStructure .ucStartFlag = 1;			
//   }		
  
//   else
//   {
//     LEDx_TOGGLE;
    
//     // 获取定时器计数值
//     TIM_ICUserValueStructure .usCtr = HAL_TIM_ReadCapturedValue(&TIM_TimeBase,GENERAL_TIM_CHANNELx);
//     // 配置输入捕获参数，主要是修改触发电平
//     IC_Config.ICPolarity = GENERAL_TIM_STRAT_ICPolarity;
//     IC_Config.ICSelection = TIM_ICSELECTION_DIRECTTI;
//     IC_Config.ICPrescaler = TIM_ICPSC_DIV1;
//     IC_Config.ICFilter = 0;
//     HAL_TIM_IC_ConfigChannel(&TIM_TimeBase, &IC_Config, GENERAL_TIM_CHANNELx);
    
//     // 清除中断标志位
//     __HAL_TIM_CLEAR_IT(htim, GENERAL_TIM_IT_CCx); 
//     // 启动输入捕获并开启中断
//     HAL_TIM_IC_Start_IT(&TIM_TimeBase,GENERAL_TIM_CHANNELx);    
//     TIM_ICUserValueStructure .ucStartFlag = 0;			
//     TIM_ICUserValueStructure .ucFinishFlag = 1;    
//   }
// }

/**********************TIM IC interrupt*****************************/


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/










