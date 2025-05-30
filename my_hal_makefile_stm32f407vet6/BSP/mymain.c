#include "mymain.h"
int mymain(void){
    float a = 1.2;
    int b = 10;
    while(1){
       led_blink(1000); 
       printf("hello makefile\n");
       printf("hello gcc, %f, %d\n", a, b);
    //    UART_SendStr("hello stm32\n");

    }
}