#include "tim_pwm1.h"

TIM_HandleTypeDef htim_pwm;

void TIM_PWM_GPIO_Init(void)
{

    GPIO_InitTypeDef GPIO_InitStruct = {0};
    TIM_PWM_GPIO_CLK_ENABLE();
    /**TIM2 GPIO Configuration
    PB10     ------> TIM2_CH3
    */
    GPIO_InitStruct.Pin = TIM_PWM_GPIO_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(TIM_PWM_GPIO_PORT, &GPIO_InitStruct);

    // __HAL_AFIO_REMAP_TIM2_PARTIAL_2();

}
void TIM_PWM_Init(void)
{
  TIM_PWM_GPIO_Init();

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};

  TIM_PWM_CLK_ENABLE();

  htim_pwm.Instance = TIM_PWM;
  htim_pwm.Init.Prescaler =TIM_PWM_PSC;
  htim_pwm.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim_pwm.Init.Period = TIM_PWM_ARR;
  htim_pwm.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim_pwm.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
  HAL_TIM_Base_Init(&htim_pwm);

  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  HAL_TIM_ConfigClockSource(&htim_pwm, &sClockSourceConfig);
  HAL_TIM_PWM_Init(&htim_pwm);

  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  HAL_TIMEx_MasterConfigSynchronization(&htim_pwm, &sMasterConfig);

  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  HAL_TIM_PWM_ConfigChannel(&htim_pwm, &sConfigOC, TIM_PWM_CHANNEL_x);

  // HAL_TIM_MspPostInit(&htim_pwm);

  HAL_NVIC_SetPriority(TIM_PWM_IQRn, 5, 0);
  HAL_NVIC_EnableIRQ(TIM_PWM_IQRn);

  HAL_TIM_PWM_Start(&htim_pwm, TIM_PWM_CHANNEL_x);
}

// void HAL_TIM_Base_MspInit(TIM_HandleTypeDef* tim_baseHandle)
// {

//   if(tim_baseHandle->Instance== TIM_PWM)
//   {


//   }
// }


