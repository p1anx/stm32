//
// Created by xwj on 10/12/25.
//

#include "test_mt6835.h"
#include "main.h"
// #include "../mt6835.bak.h"
#include "mt6835.h"
#include <stdio.h>
#include "driver_encoder.h"

/* SPI句柄 (由STM32CubeMX自动生成) */
/*
extern SPI_HandleTypeDef hspi2;

/* MT6835设备句柄 #1#
MT6835_Handle mt6835;

void test_init0(void)
{
    MT6835_Init(&mt6835, &hspi2, GPIOB, GPIO_PIN_12);
    /* 主循环 #1#
    while (1)
    {
        /* 方法1: 标准读取方式 #1#
        if (MT6835_ReadAngle(&mt6835))
        {
            printf("angle: %.2f (%.4f rad) [Raw: %lu]\r\n",
                   MT6835_GetAngleDegrees(&mt6835),
                   MT6835_GetAngleRadians(&mt6835),
                   MT6835_GetAngleRaw(&mt6835));
        }

        HAL_Delay(100);  // 100ms读取一次
    }
}
void test_mt_0(void)
{
    uint8_t cmd = 0xc << 4;
    uint8_t dummy = 0x0;
    uint8_t data;
    printf("start mt test\n");
    // MT6835_Init(&mt6835, &hspi2, GPIOB, GPIO_PIN_12);
    HAL_GPIO_WritePin(MT6835_SPI_CS_PORT, MT6835_SPI_CS_PIN, GPIO_PIN_RESET);
    HAL_SPI_Transmit(&hspi2, &cmd, 1, 1000);
    HAL_SPI_Transmit(&hspi2, &dummy, 1, 1000);
    HAL_SPI_Receive(&hspi2, &data, 1, 1000);
    HAL_GPIO_WritePin(MT6835_SPI_CS_PORT, MT6835_SPI_CS_PIN, GPIO_PIN_SET);
    HAL_Delay(6000);
    printf("rx = 0x%xh\n", data);

}

void test_mt5835_init(void)
{
   float last_angle = 0;
    int count = 0;
    while (1)
    {
       const uint32_t MT6835_Angle = ReadMT6835_Angle();


        const float angle = (float)MT6835_Angle/2097152 * 360;
        if ((int)angle-(int)last_angle > 90)
        {
            count++;
        }
        last_angle = angle;
        printf("raw = %d, angle = %f, count = %d\n", MT6835_Angle, angle, count);


        // test_init0();
        // test_mt_0();

    }
}
*/
