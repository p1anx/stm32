
// Tests/unity_uart.c
// #include "unity_config.h"
// #include <string.h>

// extern UART_HandleTypeDef huart2;
// #define unity_uart huart2

// void uart_init(void)
// {
//     // UART 已经在 main 中初始化
// }

// void uart_putchar(char c)
// {
//     HAL_UART_Transmit(&unity_uart, (uint8_t *)&c, 1, 1000);
// }

// void uart_flush(void)
// {
//     // 等待发送完成
//     while (__HAL_UART_GET_FLAG(&unity_uart, UART_FLAG_TC) == RESET)
//         ;
// }

// void uart_complete(void)
// {
//     uart_flush();
// }