/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   测试led
  ******************************************************************************
  * @attention
  *
  * 实验平台:野火 F103-霸道 STM32 开发板 
  * 论坛    :http://www.firebbs.cn
  * 淘宝    :https://fire-stm32.taobao.com
  *
  ******************************************************************************
  */ 

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f1xx.h"
#include "led.h"
#include "key.h"
#include "exti.h"
#include "usart.h"
// #include "tim_base.h"
// #include "tim_pwm.h"
#include "tim.h"

/**
  * @brief  主函数
  * @param  无
  * @retval 无
  */
volatile uint32_t time ; // ms 计时变量
int main(void)
{
    /* 系统时钟初始化成72 MHz */
    SystemClock_Config();
    /* LED 端口初始化 */
    LED_GPIO_Init();
    // Key_GPIO_Init();
    // Key_EXTI_Init();
    // DEBUG_USART_Init();
    
    // TIMx_Base_Init();
    // HAL_TIM_Base_Start_IT(&htimx);
    MX_TIM2_Init();
    HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_3);

    // TIMx_Configuration();
    

    /* 控制LED灯 */
    while (1)
    {
      /***************LED****************/
      // LEDx_TOGGLE;
      // HAL_Delay(1000);

      /***************KEY****************/
      // if(Key_Scan(KEYx_GPIO_PORT, KEYx_PIN) == KEY_ON){
      //   LEDx_TOGGLE;
      // }

      /***************USART****************/
      // uint8_t a = 1;
      // uint32_t b = 11;
      // UART_SendStr("hello printf\n");
      // HAL_UART_Transmit(&huart1, "11\n", sizeof("11\n"), HAL_MAX_DELAY);
      // HAL_UART_Transmit(&huart1, &b, 4, HAL_MAX_DELAY);
      // printf("hello stm32\n");

      /***************USART sprintf****************/
      // uint8_t a = 1;
      // float c = 2.2;
      // char buff[10];
      // sprintf(buff, "a = %d, c = %.2f\n", a, c);
      // UART_SendStr(buff);
      // HAL_Delay(500);
      /*
      ...............platformio.ini...................
      build_flags = 
            -Wl,-u,_printf_float
      ................................................
      this is used to print float type data
      */

      /***************USART my_printf****************/
      // uint8_t a = 1;
      // float c = 2.2;
      // my_printf("hello a = %d, c = %.2f\n", a, c);
      // HAL_Delay(500);

      /***************TIM BASE****************/
      // if(time == 500){
      //   time = 0;
      //   LEDx_TOGGLE;
      // }

      /***************TIM BASE****************/
      // int pwm_n = 100;
      // for(int pwm = 0; pwm <pwm_n; pwm++){
      //   TIM2->CCR3 = pwm;
      //   HAL_Delay(10);
      // }
      // for(int pwm = pwm_n; pwm > 0; pwm--){
      //   TIM2->CCR3 = pwm;
      //   HAL_Delay(10);
      // }
        TIM2->CCR3 = 200;
    }
}
/**
  * @brief  System Clock Configuration
  *         The system Clock is configured as follow : 
  *            System Clock source            = PLL (HSE)
  *            SYSCLK(Hz)                     = 72000000
  *            HCLK(Hz)                       = 72000000
  *            AHB Prescaler                  = 1
  *            APB1 Prescaler                 = 2
  *            APB2 Prescaler                 = 1
  *            HSE Frequency(Hz)              = 8000000
  *            HSE PREDIV1                    = 2
  *            PLLMUL                         = 9
  *            Flash Latency(WS)              = 0
  * @param  None
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_ClkInitTypeDef clkinitstruct = {0};
  RCC_OscInitTypeDef oscinitstruct = {0};
  
  /* Enable HSE Oscillator and activate PLL with HSE as source */
  oscinitstruct.OscillatorType  = RCC_OSCILLATORTYPE_HSE;
  oscinitstruct.HSEState        = RCC_HSE_ON;
  oscinitstruct.HSEPredivValue  = RCC_HSE_PREDIV_DIV1;
  oscinitstruct.PLL.PLLState    = RCC_PLL_ON;
  oscinitstruct.PLL.PLLSource   = RCC_PLLSOURCE_HSE;
  oscinitstruct.PLL.PLLMUL      = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&oscinitstruct)!= HAL_OK)
  {
    /* Initialization Error */
    while(1); 
  }

  /* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2 
     clocks dividers */
  clkinitstruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
  clkinitstruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  clkinitstruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  clkinitstruct.APB2CLKDivider = RCC_HCLK_DIV1;
  clkinitstruct.APB1CLKDivider = RCC_HCLK_DIV2;  
  if (HAL_RCC_ClockConfig(&clkinitstruct, FLASH_LATENCY_2)!= HAL_OK)
  {
    /* Initialization Error */
    while(1); 
  }
}
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/