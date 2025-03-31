#include "mymain.h"

SemaphoreHandle_t keySemphrHandle;
//control the pwm by key exti,  using binary semaphore 
static void pwm_server_task(void *arg){
    const int pwm_angle_base = 1650; //1650 pulses = 0 degree; //910 pulses = 90 degree
    int degree = 90;
    int pwm_1degree = (1650 - 910)/90;
    int pwm_angle;

    HAL_TIM_PWM_Start(&htim_pwm_server, TIM_PWM_SERVER_CHANNELx);
    while(1)
    {
        pwm_angle = pwm_angle_base - degree * pwm_1degree; 
        __HAL_TIM_SetAutoreload(&htim_pwm_server, 10000); //pulse circle = 10ms 
        __HAL_TIM_SetCompare(&htim_pwm_server, TIM_PWM_SERVER_CHANNELx, pwm_angle);
        if(xSemaphoreTake(keySemphrHandle, portMAX_DELAY) == pdPASS)
        {
            degree = degree + 10;
            my_printf("degree = %d\n", degree);
            if (degree > 90){
                degree = 0;
            }
            key_flag =0;
        }
    }
    
}

int mymain(void){

    keySemphrHandle = xSemaphoreCreateBinary();

    // taskENTER_CRITICAL();
    xTaskCreate(led_task, "led", 128, NULL, 1, NULL);
    xTaskCreate(pwm_server_task, "pwm server", 128, NULL, 1, NULL);
    // taskEXIT_CRITICAL();
    vTaskStartScheduler();

    return 0;
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin){
    if(GPIO_Pin == GPIO_PIN_0){

        if(xSemaphoreGiveFromISR(keySemphrHandle, NULL) == pdPASS) 
        {
            my_printf("key is pressed\n");
        }
    }
}
