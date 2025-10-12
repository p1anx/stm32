// Tests/test_uart.c
#include "unity.h"
#include "stm32f1xx_hal.h"

extern UART_HandleTypeDef huart2;

// void setUp(void)
// {
// }
// void tearDown(void)
// {
// }

// 测试 UART 发送
void test_uart_transmit(void)
{
    uint8_t data[] = "\nTEST\n";
    HAL_StatusTypeDef status;

    status = HAL_UART_Transmit(&huart2, data, 6, 1000);

    TEST_ASSERT_EQUAL(HAL_OK, status);
}

// 测试 UART 回环（需要V TX 和 RX 短接）
// void test_uart_loopback(void)
// {
//     uint8_t tx_data = 0x55;
//     uint8_t rx_data = 0x00;

//     // 发送数据
//     HAL_UART_Transmit(&huart2, &tx_data, 1, 1000);

//     // 接收数据
//     HAL_StatusTypeDef status = HAL_UART_Receive(&huart2, &rx_data, 1, 1000);

//     TEST_ASSERT_EQUAL(HAL_OK, status);
//     TEST_ASSERT_EQUAL(tx_data, rx_data);
// }

// // 测试 UART 超时
// void test_uart_receive_timeout(void)
// {
//     uint8_t rx_data;

//     // 应该超时（没有数据接收）
//     HAL_StatusTypeDef status = HAL_UART_Receive(&huart2, &rx_data, 1, 100);

//     TEST_ASSERT_EQUAL(HAL_TIMEOUT, status);
// }

// // 测试 UAkkkkkkkkkkRT 多字节传输
// void test_uart_transmit_buffer(void)
// {
//     uint8_t data[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

//     HAL_StatusTypeDef status = HAL_UART_Transmit(&huart2, data, 10, 1000);

//     TEST_ASSERT_EQUAL(HAL_OK, status);
// }