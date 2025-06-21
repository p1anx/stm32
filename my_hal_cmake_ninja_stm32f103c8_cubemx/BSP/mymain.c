#include "mymain.h"
int mymain(void){
    float a = 1.2;
    int b = 10;
    while(1){
        LED1_TOGGLE();
        HAL_Delay(1000);
        LED2_TOGGLE();
        LED1_TOGGLE();
        HAL_Delay(1000);
        LED2_TOGGLE();
        
       printf("hello makefile\n");
       printf("hello gcc, %.2f, %d\n", a, b);

    }
}
