#include "test_gpio.h"
#include "unity.h"

extern void test_uart_transmit(void);
void unity_test(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_gpio_output_high);
    RUN_TEST(test_uart_transmit);
    UNITY_END();
}