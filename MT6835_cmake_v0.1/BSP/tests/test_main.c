//
// Created by xwj on 10/12/25.
//

#include "test_main.h"
#include "unity.h"
#include "test_mt6835.h"
#include "motor_example.h"



extern void test_uart_transmit(void);
void test_main_unity(void)
{
    UNITY_BEGIN();
   // RUN_TEST(test_uart_transmit);
   // RUN_TEST(test_mt5835_init);
   // RUN_TEST(Example1_BasicUsage);
   RUN_TEST(Example2_BasicUsage);
    UNITY_END();
}

