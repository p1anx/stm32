#include "mymain.h"

static void pwm_server_task(void *arg){
    
    // pwm_setFreq(1000);
    while (1)
    {
        pwm_led_brth(500);
    }
    
}
static void led_task(void *arg){
    while(1){
        LED1_TOGGLE();
        
        my_printf("hello mx1\n");
        vTaskDelay(500);
    }
}

static void oled_task(void *arg){
    OLED_ShowStr(0, 0, "good");
    while(1){
    }
}
int mymain(void){
    OLED_Init();

    xTaskCreate(oled_task, "oled", 128, NULL, 1, NULL);
    xTaskCreate(led_task, "led", 128, NULL, 1, NULL);
    xTaskCreate(pwm_server_task, "pwm server", 128, NULL, 1, NULL);
    vTaskStartScheduler();

    while (1)
    {
        // pwm_server_test(600);
        
        // pwm_led_brth(100);
        
    }
    

    return 0;
}