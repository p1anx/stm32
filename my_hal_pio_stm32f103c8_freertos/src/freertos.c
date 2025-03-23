#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
TaskHandle_t startTaskHandle;
TaskHandle_t ledTaskHandle;
TaskHandle_t oledTaskHandle;
TaskHandle_t printTaskHandle;


static void key_task(void *param){
  int i = 0;
  int j = 0;
  // OLED_Printf(0, 0, "hello ollo");
  while (1)
  {
    if(Key_Scan(1) == KEY_ON){
      LED1_TOGGLE();
      OLED_ShowNumInt(0, 0, j);
      j = j + 1000;
      if(j == 4000)
      {
        j = 0;
      }
      
    }
    else if(Key_Scan(2) == KEY_ON)
    {
      OLED_ShowStr(0, 16, "i = ");
      OLED_ShowNumInt(4*8, 16, i++);
      if(i > 5)
      {
        i = 0;
      }

    }
  }
}

void led_task(void *param){
  while (1)
  {
    LED2_TOGGLE();
    vTaskDelay(500);
  }
}

void oled_task(void *param){
  // OLED_ShowString(0, 16, "hahah", OLED_8X16);
  while (1)
  {
    // for (int i = 0; i < 10; i++)
    // {
    //   OLED_Printf(0, 0, "hello = %d", i);
    //   vTaskDelay(1000);

    // }
  }
}

void print_task(void *arg){
  while (1)
  {
    my_printf("hello freertos22\n");
    // HAL_Delay(1000);
    vTaskDelay(500);
  }

}
void start_task(void *arg){
  // taskENTER_CRITICAL();
  xTaskCreate(led_task, "led", 128, NULL, 1, ledTaskHandle);
  // xTaskCreate(oled_task, "oled", 128, NULL, 1, oledTaskHandle);
  xTaskCreate(print_task, "print", 128, NULL, 1, printTaskHandle);
  // xTaskCreate(key_task, "key", 128, NULL, 1, NULL);


  vTaskDelete(startTaskHandle);
  // taskEXIT_CRITICAL();

}

void FREERTOS_Init(void){
  xTaskCreate(start_task, "start freertos", 128, NULL, 1, startTaskHandle);
  vTaskStartScheduler();
}
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */