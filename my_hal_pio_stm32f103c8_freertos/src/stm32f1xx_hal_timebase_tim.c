#include "stm32f1xx_hal_timebase_tim.h"

TIM_HandleTypeDef        htim_timebase;
/**
  * @brief  This function configures the TIM3 as a time base source.
  *         The time source is configured  to have 1ms time base with a dedicated
  *         Tick interrupt priority.
  * @note   This function is called  automatically at the beginning of program after
  *         reset by HAL_Init() or at any time when clock is configured, by HAL_RCC_ClockConfig().
  * @param  TickPriority: Tick interrupt priority.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_InitTick(uint32_t TickPriority)
{
  RCC_ClkInitTypeDef    clkconfig;
  uint32_t              uwTimclock, uwAPB1Prescaler = 0U;

  uint32_t              uwPrescalerValue = 0U;
  uint32_t              pFLatency;
  HAL_StatusTypeDef     status = HAL_OK;

  /* Enable TIM3 clock */
  TIM_TIMEBASE_CLK_ENABLE();
  /* Get clock configuration */
  HAL_RCC_GetClockConfig(&clkconfig, &pFLatency);
  /* Get APB1 prescaler */
  uwAPB1Prescaler = clkconfig.APB1CLKDivider;
  /* Compute TIM3 clock */
  if (uwAPB1Prescaler == RCC_HCLK_DIV1)
  {
    uwTimclock = HAL_RCC_GetPCLK1Freq();
  }
  else
  {
    uwTimclock = 2UL * HAL_RCC_GetPCLK1Freq();
  }

  /* Compute the prescaler value to have TIM3 counter clock equal to 1MHz */
  uwPrescalerValue = (uint32_t) ((uwTimclock / 1000000U) - 1U);

  /* Initialize TIM3 */
  htim_timebase.Instance = TIM_TIMEBASE;

  /* Initialize TIMx peripheral as follow:

  + Period = [(TIM3CLK/1000) - 1]. to have a (1/1000) s time base.
  + Prescaler = (uwTimclock/1000000 - 1) to have a 1MHz counter clock.
  + ClockDivision = 0
  + Counter direction = Up
  */
  htim_timebase.Init.Period = (1000000U / 1000U) - 1U;
  htim_timebase.Init.Prescaler = uwPrescalerValue;
  htim_timebase.Init.ClockDivision = 0;
  htim_timebase.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim_timebase.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;

  status = HAL_TIM_Base_Init(&htim_timebase);
  if (status == HAL_OK)
  {
    /* Start the TIM time Base generation in interrupt mode */
    status = HAL_TIM_Base_Start_IT(&htim_timebase);
    if (status == HAL_OK)
    {
    /* Enable the TIM3 global Interrupt */
        HAL_NVIC_EnableIRQ(TIM_TIMEBASE_IRQn);
      /* Configure the SysTick IRQ priority */
      if (TickPriority < (1UL << __NVIC_PRIO_BITS))
      {
        /* Configure the TIM IRQ priority */
        HAL_NVIC_SetPriority(TIM_TIMEBASE_IRQn, TickPriority, 0U);
        uwTickPrio = TickPriority;
      }
      else
      {
        status = HAL_ERROR;
      }
    }
  }

 /* Return function status */
  return status;
}

/**
  * @brief  Suspend Tick increment.
  * @note   Disable the tick increment by disabling TIM3 update interrupt.
  * @param  None
  * @retval None
  */
void HAL_SuspendTick(void)
{
  /* Disable TIM3 update Interrupt */
  __HAL_TIM_DISABLE_IT(&htim_timebase, TIM_IT_UPDATE);
}

/**
  * @brief  Resume Tick increment.
  * @note   Enable the tick increment by Enabling TIM3 update interrupt.
  * @param  None
  * @retval None
  */
void HAL_ResumeTick(void)
{
  /* Enable TIM3 Update interrupt */
  __HAL_TIM_ENABLE_IT(&htim_timebase, TIM_IT_UPDATE);
}

