//
// Created by xwj on 12/6/25.
//

#ifndef __MMC5983_H
#define __MMC5983_H

#include "main.h" // 包含 HAL 库和项目特定的头文件

// --- 硬件连接配置 ---
// 请根据您的实际连接修改 SPI 句柄和 CS 引脚定义
extern SPI_HandleTypeDef hspi1; // 假设使用 SPI1
#define MMC5983_SPI_HANDLE hspi1
#define MMC5983_CS_GPIO_Port GPIOA // 假设 CS 连接到 GPIOA
#define MMC5983_CS_Pin GPIO_PIN_4  // 假设 CS 连接到 PA4
#define MMC5983_18BITS_RESOLUTION 16384 // counts/gauss

#define MMC5983_CONFIG_BW_800HZ 0x03
#define MMC5983_CONFIG_BW_400HZ 0x02
#define MMC5983_CONFIG_BW_200HZ 0x01
#define MMC5983_CONFIG_BW_100HZ 0x00
// --- MMC5983 寄存器地址 ---
#define MMC5983_XOUT0_ADDR        0x00
#define MMC5983_XOUT1_ADDR        0x01
#define MMC5983_YOUT0_ADDR        0x02
#define MMC5983_YOUT1_ADDR        0x03
#define MMC5983_ZOUT0_ADDR        0x04
#define MMC5983_ZOUT1_ADDR        0x05
#define MMC5983_XYZOUT2_ADDR      0x06
#define MMC5983_TOUT_ADDR         0x07
#define MMC5983_STATUS_ADDR       0x08
#define MMC5983_CONTROL_0_ADDR    0x09
#define MMC5983_CONTROL_1_ADDR    0x0A
#define MMC5983_CONTROL_2_ADDR    0x0B
#define MMC5983_CONTROL_3_ADDR    0x0C
#define MMC5983_PRODUCT_ID1_ADDR  0x2F

// --- MMC5983 状态寄存器位 ---
#define MMC5983_STATUS_MEAS_M_DONE    0x01 // 磁场测量完成
#define MMC5983_STATUS_MEAS_T_DONE    0x02 // 温度测量完成

// --- MMC5983 内部控制寄存器 0 位 ---
#define MMC5983_CONTROL_0_TM_M        0x01 // 启动磁场测量
#define MMC5983_CONTROL_0_TM_T        0x02 // 启动温度测量
#define MMC5983_CONTROL_0_INT_EN      0x04 // 中断使能
#define MMC5983_CONTROL_0_SET         0x08 // SET 操作
#define MMC5983_CONTROL_0_RESET       0x10 // RESET 操作
#define MMC5983_CONTROL_0_AUTO_SR_EN  0x20 // 自动 SET/RESET 使能
#define MMC5983_CONTROL_0_OTP_READ    0x40 // OTP 读取

// --- 函数返回值定义 ---
typedef enum {
    MMC5983_OK = 0,
    MMC5983_ERROR,
    MMC5983_TIMEOUT
} mmc5983_status_t;

// --- 数据结构 ---
typedef struct {
    int32_t x; // 18位数据
    int32_t y;
    int32_t z;
} mmc5983_raw_data_t;
typedef struct {
    mmc5983_raw_data_t raw_data;
    float x; // 18位数据
    float y;
    float z;
} mmc5983_Gauss_t;

// --- API 函数声明 ---

/**
 * @brief  初始化 MMC5983 传感器
 * @return mmc5983_status_t
 */
mmc5983_status_t mmc5983_init(void);

/**
 * @brief  软件复位传感器
 * @return mmc5983_status_t
 */
mmc5983_status_t mmc5983_software_reset(void);

/**
 * @brief  读取产品 ID
 * @param  id: 指向存储 ID 的变量指针
 * @return mmc5983_status_t
 */
mmc5983_status_t mmc5983_read_product_id(uint8_t *id);

/**
 * @brief  执行 SET 操作
 * @return mmc5983_status_t
 */
mmc5983_status_t mmc5983_set(void);

/**
 * @brief  执行 RESET 操作
 * @return mmc5983_status_t
 */
mmc5983_status_t mmc5983_reset(void);

/**
 * @brief  启动一次磁场测量
 * @return mmc5983_status_t
 */
mmc5983_status_t mmc5983_start_measurement(void);

/**
 * @brief  读取磁场原始数据 (18位)
 * @param  data: 指向存储数据的结构体指针
 * @return mmc5983_status_t
 */
mmc5983_status_t mmc5983_read_raw_data(mmc5983_raw_data_t *data);

/**
 * @brief  启动一次温度测量
 * @return mmc5983_status_t
 */
mmc5983_status_t mmc5983_start_temperature_measurement(void);

/**
 * @brief  读取温度原始数据
 * @param  temp_raw: 指向存储温度原始值的变量指针
 * @return mmc5983_status_t
 */
mmc5983_status_t mmc5983_read_raw_temperature(uint8_t *temp_raw);

/**
 * @brief  读取状态寄存器
 * @param  status: 指向存储状态值的变量指针
 * @return mmc5983_status_t
 */
mmc5983_status_t mmc5983_read_status(uint8_t *status);

mmc5983_status_t mmc5983_readGauss(mmc5983_Gauss_t *dataGauss);
void mmc5983_waitMeasureDone(void);
mmc5983_status_t mmc5983_initConfig(void);
mmc5983_status_t mmc5983_measureGauss(mmc5983_Gauss_t *dataGauss);
#endif /* __MMC5983_H */