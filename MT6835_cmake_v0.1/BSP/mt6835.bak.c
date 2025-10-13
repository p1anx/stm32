// /**
//  * @file    mt6835.c
//  * @brief   MT6835磁性编码器驱动实现
//  * @author
//  * @date    2025
//  */
//
// #include "mt6835.bak.h"
// #include <math.h>
//
// #define MT6835_ANGLE_MAX    0x1FFFFF  // 21位最大值 (2097151)
// #define PI                  3.14159265358979323846f
//
// /* 私有函数 */
// static inline void MT6835_CS_Low(MT6835_Handle *mt6835)
// {
//     HAL_GPIO_WritePin(mt6835->cs_port, mt6835->cs_pin, GPIO_PIN_RESET);
// }
//
// static inline void MT6835_CS_High(MT6835_Handle *mt6835)
// {
//     HAL_GPIO_WritePin(mt6835->cs_port, mt6835->cs_pin, GPIO_PIN_SET);
// }
//
// /**
//  * @brief  初始化MT6835
//  * @param  mt6835: MT6835句柄
//  * @param  hspi: SPI句柄
//  * @param  cs_port: CS引脚端口
//  * @param  cs_pin: CS引脚编号
//  */
// void MT6835_Init(MT6835_Handle *mt6835, SPI_HandleTypeDef *hspi,
//                  GPIO_TypeDef *cs_port, uint16_t cs_pin)
// {
//     mt6835->hspi = hspi;
//     mt6835->cs_port = cs_port;
//     mt6835->cs_pin = cs_pin;
//     mt6835->angle_raw = 0;
//     mt6835->angle_deg = 0.0f;
//     mt6835->angle_rad = 0.0f;
//
//     // CS引脚设置为高电平(未选中)
//     MT6835_CS_High(mt6835);
//
//     // 短暂延时等待芯片就绪
//     HAL_Delay(10);
// }
//
// /**
//  * @brief  读取MT6835寄存器
//  * @param  mt6835: MT6835句柄
//  * @param  reg_addr: 寄存器地址(12位)
//  * @return 寄存器值(8位)
//  */
// uint8_t MT6835_ReadRegister(MT6835_Handle *mt6835, uint16_t reg_addr)
// {
//     uint8_t tx_data[3];
//     uint8_t rx_data[3];
//
//     // 构建24位SPI帧: [命令4位][地址12位][数据8位]
//     tx_data[0] = (MT6835_CMD_READ << 4) | ((reg_addr >> 8) & 0x0F);
//     tx_data[1] = reg_addr & 0xFF;
//     tx_data[2] = 0x00;  // 占位字节
//
//     MT6835_CS_Low(mt6835);
//     HAL_SPI_TransmitReceive(mt6835->hspi, tx_data, rx_data, 3, HAL_MAX_DELAY);
//     MT6835_CS_High(mt6835);
//
//     return rx_data[2];  // 返回的数据在第3个字节
// }
//
// /**
//  * @brief  写入MT6835寄存器
//  * @param  mt6835: MT6835句柄
//  * @param  reg_addr: 寄存器地址(12位)
//  * @param  data: 要写入的数据(8位)
//  */
// void MT6835_WriteRegister(MT6835_Handle *mt6835, uint16_t reg_addr, uint8_t data)
// {
//     uint8_t tx_data[3];
//
//     // 构建24位SPI帧: [命令4位][地址12位][数据8位]
//     tx_data[0] = (MT6835_CMD_WRITE << 4) | ((reg_addr >> 8) & 0x0F);
//     tx_data[1] = reg_addr & 0xFF;
//     tx_data[2] = data;
//
//     MT6835_CS_Low(mt6835);
//     HAL_SPI_Transmit(mt6835->hspi, tx_data, 3, HAL_MAX_DELAY);
//     MT6835_CS_High(mt6835);
// }
//
// /**
//  * @brief  读取角度(标准方式,分3次读取3个寄存器)
//  * @param  mt6835: MT6835句柄
//  * @return true: 成功, false: 失败
//  */
// bool MT6835_ReadAngle(MT6835_Handle *mt6835)
// {
//     uint8_t angle_h, angle_m, angle_l;
//
//     // 读取3个角度寄存器
//     angle_h = MT6835_ReadRegister(mt6835, MT6835_REG_ANGLE_H);
//     angle_m = MT6835_ReadRegister(mt6835, MT6835_REG_ANGLE_M);
//     angle_l = MT6835_ReadRegister(mt6835, MT6835_REG_ANGLE_L);
//
//     // 组合成21位角度值
//     mt6835->angle_raw = ((uint32_t)angle_h << 16) |
//                         ((uint32_t)angle_m << 8) |
//                         ((uint32_t)angle_l);
//     mt6835->angle_raw &= MT6835_ANGLE_MAX;  // 确保是21位
//
//     // 转换为角度(度)
//     mt6835->angle_deg = (float)mt6835->angle_raw * 360.0f / (MT6835_ANGLE_MAX + 1);
//
//     // 转换为弧度
//     mt6835->angle_rad = mt6835->angle_deg * PI / 180.0f;
//
//     return true;
// }
//
// /**
//  * @brief  快速读取角度(使用连续读取模式)
//  * @param  mt6835: MT6835句柄
//  * @return true: 成功, false: 失败
//  */
// bool MT6835_ReadAngleFast(MT6835_Handle *mt6835)
// {
//     uint8_t tx_data[6];
//     uint8_t rx_data[6];
//
//     // 使用连续读取命令
//     // 第一帧: 读0x003
//     tx_data[0] = (MT6835_CMD_READ << 4) | 0x00;
//     tx_data[1] = 0x03;
//     tx_data[2] = 0x00;
//
//     // 第二帧: 读0x004
//     tx_data[3] = (MT6835_CMD_READ << 4) | 0x00;
//     tx_data[4] = 0x04;
//     tx_data[5] = 0x00;
//
//     MT6835_CS_Low(mt6835);
//     HAL_SPI_TransmitReceive(mt6835->hspi, tx_data, rx_data, 6, HAL_MAX_DELAY);
//     MT6835_CS_High(mt6835);
//
//     // 读取第三个寄存器
//     uint8_t angle_l = MT6835_ReadRegister(mt6835, MT6835_REG_ANGLE_L);
//
//     // 组合角度值
//     mt6835->angle_raw = ((uint32_t)rx_data[2] << 16) |
//                         ((uint32_t)rx_data[5] << 8) |
//                         ((uint32_t)angle_l);
//     mt6835->angle_raw &= MT6835_ANGLE_MAX;
//
//     // 转换为角度
//     mt6835->angle_deg = (float)mt6835->angle_raw * 360.0f / (MT6835_ANGLE_MAX + 1);
//     mt6835->angle_rad = mt6835->angle_deg * PI / 180.0f;
//
//     return true;
// }
//
// /**
//  * @brief  获取角度值(度)
//  * @param  mt6835: MT6835句柄
//  * @return 角度值(0-360度)
//  */
// float MT6835_GetAngleDegrees(MT6835_Handle *mt6835)
// {
//     return mt6835->angle_deg;
// }
//
// /**
//  * @brief  获取角度值(弧度)
//  * @param  mt6835: MT6835句柄
//  * @return 角度值(0-2π弧度)
//  */
// float MT6835_GetAngleRadians(MT6835_Handle *mt6835)
// {
//     return mt6835->angle_rad;
// }
//
// /**
//  * @brief  获取原始角度值
//  * @param  mt6835: MT6835句柄
//  * @return 21位原始角度值(0-2097151)
//  */
// uint32_t MT6835_GetAngleRaw(MT6835_Handle *mt6835)
// {
//     return mt6835->angle_raw;
// }
//
// /**
//  * @brief  设置零位
//  * @param  mt6835: MT6835句柄
//  * @param  zero_pos: 零位值(12位)
//  */
// void MT6835_SetZeroPosition(MT6835_Handle *mt6835, uint16_t zero_pos)
// {
//     uint8_t zero_h = (zero_pos >> 8) & 0x0F;
//     uint8_t zero_l = zero_pos & 0xFF;
//
//     MT6835_WriteRegister(mt6835, MT6835_REG_ZERO_POS_H, zero_h);
//     MT6835_WriteRegister(mt6835, MT6835_REG_ZERO_POS_L, zero_l);
// }