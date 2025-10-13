/*/**
 * @file    mt6835.h
 * @brief   MT6835磁性编码器驱动头文件
 * @author
 * @date    2025
 #1#

#ifndef __MT6835_H
#define __MT6835_H

#include "stm32f1xx_hal.h"  // 根据你的STM32系列修改
#include <stdint.h>
#include <stdbool.h>

/*gpio define#1#
#define  MT6835_SPI_CS_PORT GPIOB
#define  MT6835_SPI_CS_PIN GPIO_PIN_12

/* MT6835 SPI命令定义 #1#
#define MT6835_CMD_READ         0x03    // 读寄存器命令
#define MT6835_CMD_WRITE        0x06    // 写寄存器命令
#define MT6835_CMD_PROG_EEPROM  0x0C    // 编程EEPROM命令
#define MT6835_CMD_BURST_READ   0x0A    // 连续读角度命令

/* MT6835 寄存器地址定义 #1#
#define MT6835_REG_ANGLE_H      0x003   // 角度寄存器高字节
#define MT6835_REG_ANGLE_M      0x004   // 角度寄存器中字节
#define MT6835_REG_ANGLE_L      0x005   // 角度寄存器低字节
#define MT6835_REG_ZERO_POS_H   0x000   // 零位高字节
#define MT6835_REG_ZERO_POS_L   0x001   // 零位低字节
#define MT6835_REG_ABZ_RES_H    0x002   // ABZ分辨率高字节
#define MT6835_REG_ABZ_RES_L    0x009   // ABZ分辨率低字节

/* MT6835 数据结构 #1#
typedef struct {
    SPI_HandleTypeDef *hspi;    // SPI句柄
    GPIO_TypeDef *cs_port;      // CS引脚端口
    uint16_t cs_pin;            // CS引脚编号
    uint32_t angle_raw;         // 原始角度值(21位)
    float angle_deg;            // 角度值(度)
    float angle_rad;            // 角度值(弧度)
} MT6835_Handle;

/* 函数声明 #1#
void MT6835_Init(MT6835_Handle *mt6835, SPI_HandleTypeDef *hspi,
                 GPIO_TypeDef *cs_port, uint16_t cs_pin);
uint8_t MT6835_ReadRegister(MT6835_Handle *mt6835, uint16_t reg_addr);
void MT6835_WriteRegister(MT6835_Handle *mt6835, uint16_t reg_addr, uint8_t data);
bool MT6835_ReadAngle(MT6835_Handle *mt6835);
bool MT6835_ReadAngleFast(MT6835_Handle *mt6835);
float MT6835_GetAngleDegrees(MT6835_Handle *mt6835);
float MT6835_GetAngleRadians(MT6835_Handle *mt6835);
uint32_t MT6835_GetAngleRaw(MT6835_Handle *mt6835);
void MT6835_SetZeroPosition(MT6835_Handle *mt6835, uint16_t zero_pos);

void test_mt_0(void);
//endif /* __MT6835_H */