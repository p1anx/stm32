// Tests/test_gpio.c
#include "./unity/unity.h"
#include "stm32f1xx_hal.h"
#include "main.h"

void setUp(void)
{
    // 每个测试前执行
}

void tearDown(void)
{
    // 每个测试后执行
}

// 测试 GPIO 输出
void test_gpio_output_high(void)
{
    // 设置 GPIO 为高电平

    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);
    // 读取状态验证
    // GPIO_PinState state = HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13);
    // TEST_ASSERT_EQUAL(GPIO_PIN_SET, state);
}

// void test_gpio_output_low(void)
// {
//     HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);

//     GPIO_PinState state = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_5);
//     TEST_ASSERT_EQUAL(GPIO_PIN_RESET, state);
// }

// // 测试 GPIO 切换
// void test_gpio_toggle(void)
// {
//     // 先设置为低
//     HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
//     GPIO_PinState initial = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_5);

//     // 切换
//     HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
//     GPIO_PinState toggled = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_5);

//     // 验证状态改变
//     TEST_ASSERT_NOT_EQUAL(initial, toggled);
// }

// // 测试 GPIO 输入（需要外部连接）
// void test_gpio_input_with_pullup(void)
// {
//     GPIO_InitTypeDef GPIO_InitStruct = {0};

//     // 配置为输入，上拉
//     GPIO_InitStruct.Pin = GPIO_PIN_0;
//     GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
//     GPIO_InitStruct.Pull = GPIO_PULLUP;
//     HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

//     // 读取状态（应该是高，因为上拉）
//     GPIO_PinState state = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0);
//     TEST_ASSERT_EQUAL(GPIO_PIN_SET, state);
// }

// // 测试 GPIO 输入下拉
// void test_gpio_input_with_pulldown(void)
// {
//     GPIO_InitTypeDef GPIO_InitStruct = {0};

//     GPIO_InitStruct.Pin = GPIO_PIN_0;
//     GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
//     GPIO_InitStruct.Pull = GPIO_PULLDOWN;
//     HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

//     GPIO_PinState state = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0);
//     TEST_ASSERT_EQUAL(GPIO_PIN_RESET, state);
// }

// // 测试多个引脚同时操作
// void test_gpio_multiple_pins(void)
// {
//     uint16_t pins = GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7;

//     HAL_GPIO_WritePin(GPIOA, pins, GPIO_PIN_SET);

//     TEST_ASSERT_EQUAL(GPIO_PIN_SET, HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_5));
//     TEST_ASSERT_EQUAL(GPIO_PIN_SET, HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_6));
//     TEST_ASSERT_EQUAL(GPIO_PIN_SET, HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_7));
// }