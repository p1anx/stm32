```c
  HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_2);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  int pwn = 250;
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
    // HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_2);
    // HAL_Delay(500);
    while(pwn--){
     TIM2->CCR2 = pwn;
     HAL_Delay(1);

    }
    while(pwn <499) {
      TIM2->CCR2 = pwn;
      pwn++;
      HAL_Delay(1);
    }

  }
  /* USER CODE END 3 */
}

```
ref: https://blog.csdn.net/as480133937/article/details/99231677
