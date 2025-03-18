/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
TaskHandle_t startTaskHandle;
TaskHandle_t ledTaskHandle;
TaskHandle_t printTaskHandle;


void led_task(void *param){
  while (1)
  {
    LEDx_TOGGLE();
    // HAL_Delay(1000);
    vTaskDelay(500);
  }
  
}
void print_task(void *arg){
  while (1)
  {
    my_printf("hello freertos\n");
    // HAL_Delay(1000);
    vTaskDelay(500);
  }

}
void start_task(void *arg){
  taskENTER_CRITICAL();
  xTaskCreate(led_task, "led", 128, NULL, 1, ledTaskHandle);
  xTaskCreate(print_task, "print", 128, NULL, 1, printTaskHandle);




  vTaskDelete(startTaskHandle);
  taskEXIT_CRITICAL();

}

void FREERTOS_Init(void){
  xTaskCreate(start_task, "start freertos", 128, NULL, 1, startTaskHandle);
  vTaskStartScheduler();
}
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */