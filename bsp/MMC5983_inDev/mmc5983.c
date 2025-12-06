//
// Created by xwj on 12/6/25.
//

#include "mmc5983.h"
#include <stdbool.h>
#include <stdio.h>

// --- SPI 片选控制 ---
static inline void mmc5983_cs_low(void) {
    HAL_GPIO_WritePin(MMC5983_CS_GPIO_Port, MMC5983_CS_Pin, GPIO_PIN_RESET);
}

static inline void mmc5983_cs_high(void) {
    HAL_GPIO_WritePin(MMC5983_CS_GPIO_Port, MMC5983_CS_Pin, GPIO_PIN_SET);
}

// --- 内部辅助函数 ---
/**
 * @brief  内部写寄存器函数
 * @param  reg: 寄存器地址
 * @param  data: 要写入的数据
 * @return mmc5983_status_t
 */
static mmc5983_status_t _mmc5983_write_reg(uint8_t reg, uint8_t data) {
    uint8_t tx_data[2];
    // SPI 写命令格式: bit0=0(WRITE), bit1=don't care, bit2-7=address
    // tx_data[0] = (reg << 2) & 0xFC; // 将地址左移2位，低位补0
    tx_data[0] = (reg & 0x3F); // bit8 = 0
    tx_data[1] = data;

    mmc5983_cs_low();
    // 使用 HAL 库发送数据
    if (HAL_SPI_Transmit(&MMC5983_SPI_HANDLE, tx_data, 2, HAL_MAX_DELAY) != HAL_OK) {
        mmc5983_cs_high();
        return MMC5983_ERROR;
    }
    mmc5983_cs_high();

    return MMC5983_OK;
}

/**
 * @brief  内部读寄存器函数
 * @param  reg: 寄存器地址
 * @param  data: 指向存储读取数据的变量指针
 * @return mmc5983_status_t
 */
static mmc5983_status_t _mmc5983_read_reg(uint8_t reg, uint8_t *data) {
    uint8_t tx_data, rx_data[2];

    // SPI 读命令格式: bit0=1(READ), bit1=don't care, bit2-7=address
    // tx_data = ((reg << 2) & 0xFC) | 0x01; // 将地址左移2位，bit0置1
    tx_data = (reg & 0x3f) | 0x80; // 将地址左移2位，bit0置1

    mmc5983_cs_low();
    // 发送地址命令
    if (HAL_SPI_Transmit(&MMC5983_SPI_HANDLE, &tx_data, 1, HAL_MAX_DELAY) != HAL_OK) {
        mmc5983_cs_high();
        return MMC5983_ERROR;
    }
    // 接收数据
    if (HAL_SPI_Receive(&MMC5983_SPI_HANDLE, rx_data, 1, HAL_MAX_DELAY) != HAL_OK) {
        mmc5983_cs_high();
        return MMC5983_ERROR;
    }
    mmc5983_cs_high();

    *data = rx_data[0];
    return MMC5983_OK;
}

/**
 * @brief  内部读多个连续寄存器函数
 * @param  start_reg: 起始寄存器地址
 * @param  data: 指向存储读取数据的数组指针
 * @param  len: 要读取的字节数
 * @return mmc5983_status_t
 */
static mmc5983_status_t _mmc5983_read_regs(uint8_t start_reg, uint8_t *data, uint8_t len) {
    uint8_t tx_data;

    // SPI 读命令格式: bit0=1(READ), bit1=don't care, bit2-7=address
    // tx_data = ((start_reg << 2) & 0xFC) | 0x01; // 将地址左移2位，bit0置1
    tx_data = (start_reg & 0x3f) | 0x80; // 将地址左移2位，bit0置1

    mmc5983_cs_low();
    // 发送起始地址命令
    if (HAL_SPI_Transmit(&MMC5983_SPI_HANDLE, &tx_data, 1, HAL_MAX_DELAY) != HAL_OK) {
        mmc5983_cs_high();
        return MMC5983_ERROR;
    }
    // 接收多个数据
    if (HAL_SPI_Receive(&MMC5983_SPI_HANDLE, data, len, HAL_MAX_DELAY) != HAL_OK) {
        mmc5983_cs_high();
        return MMC5983_ERROR;
    }
    mmc5983_cs_high();

    return MMC5983_OK;
}


// --- API 函数实现 ---

mmc5983_status_t mmc5983_init(void) {
    // 1. 确保 SPI 已经初始化 (在 main.c 中通过 MX_SPI1_Init() 完成)
    // 2. 确保 CS 引脚已初始化为输出高电平
    mmc5983_cs_high();

    // 3. 等待上电稳定 (数据手册建议 10ms)
    HAL_Delay(10);

    // 4. 软件复位
    if (mmc5983_software_reset() != MMC5983_OK) {
        return MMC5983_ERROR;
    }
    HAL_Delay(10); // 等待复位完成

    // 5. 验证产品 ID
    uint8_t id = 0;
    if (mmc5983_read_product_id(&id) != MMC5983_OK) {
        return MMC5983_ERROR;
    }
    if (id != 0x30) { // 预期 ID 为 0x30
        return MMC5983_ERROR;
    }

    // 6. (可选) 配置其他寄存器，例如设置带宽、使能连续模式等
    // 例如，设置 18 位分辨率 (BW=00, 100Hz ODR)
    if (_mmc5983_write_reg(MMC5983_CONTROL_1_ADDR, 0x00) != MMC5983_OK) {
        return MMC5983_ERROR;
    }

    return MMC5983_OK;
}
mmc5983_status_t mmc5983_initConfig(void) {
    // 1. 确保 SPI 已经初始化 (在 main.c 中通过 MX_SPI1_Init() 完成)
    // 2. 确保 CS 引脚已初始化为输出高电平
    mmc5983_cs_high();

    // 3. 等待上电稳定 (数据手册建议 10ms)
    HAL_Delay(10);

    // 4. 软件复位
    if (mmc5983_software_reset() != MMC5983_OK) {
        return MMC5983_ERROR;
    }
    HAL_Delay(10); // 等待复位完成

    // 5. 验证产品 ID
    uint8_t id = 0;
    if (mmc5983_read_product_id(&id) != MMC5983_OK) {
        return MMC5983_ERROR;
    }
    if (id != 0x30) { // 预期 ID 为 0x30
        return MMC5983_ERROR;
    }

    // 6. (可选) 配置其他寄存器，例如设置带宽、使能连续模式等
    // 例如，设置 18 位分辨率 (BW=00, 100Hz ODR)
    if (_mmc5983_write_reg(MMC5983_CONTROL_1_ADDR, MMC5983_CONFIG_BW_800HZ) != MMC5983_OK) {
        return MMC5983_ERROR;
    }

    return MMC5983_OK;
}

void mmc5983_waitMeasureDone(void) {
    uint8_t status = 0;
    uint32_t timeout = HAL_GetTick() + 100; // 100ms 超时
    while (HAL_GetTick() < timeout) {
        if (mmc5983_read_status(&status) == MMC5983_OK) {
            if (status & MMC5983_STATUS_MEAS_M_DONE) {
                break; // 测量完成
            }
        }
    }
}
mmc5983_status_t mmc5983_software_reset(void) {
    return _mmc5983_write_reg(MMC5983_CONTROL_0_ADDR, MMC5983_CONTROL_0_OTP_READ); // 写 SW_RST 位 (在 Control 1)
    // 注意：手册中 SW_RST 在 Control Register 1 (0x0A) 的 Bit 7
    // uint8_t current_val;
    // if (_mmc5983_read_reg(MMC5983_CONTROL_1_ADDR, &current_val) != MMC5983_OK) {
    //     return MMC5983_ERROR;
    // }
    // current_val |= (1 << 7); // Set SW_RST bit
    // return _mmc5983_write_reg(MMC5983_CONTROL_1_ADDR, current_val);
    // 正确的 SW_RST 位在 Control Register 1 (0x0A)
    return _mmc5983_write_reg(MMC5983_CONTROL_1_ADDR, 0x80);
}


mmc5983_status_t mmc5983_read_product_id(uint8_t *id) {
    if (id == NULL) {
        return MMC5983_ERROR;
    }
    return _mmc5983_read_reg(MMC5983_PRODUCT_ID1_ADDR, id);
}

mmc5983_status_t mmc5983_set(void) {
    return _mmc5983_write_reg(MMC5983_CONTROL_0_ADDR, MMC5983_CONTROL_0_SET);
}

mmc5983_status_t mmc5983_reset(void) {
    return _mmc5983_write_reg(MMC5983_CONTROL_0_ADDR, MMC5983_CONTROL_0_RESET);
}

mmc5983_status_t mmc5983_start_measurement(void) {
    return _mmc5983_write_reg(MMC5983_CONTROL_0_ADDR, MMC5983_CONTROL_0_TM_M);
}

mmc5983_status_t mmc5983_read_raw_data_v0(mmc5983_raw_data_t *data) {
    if (data == NULL) {
        return MMC5983_ERROR;
    }

    uint8_t raw_data[7]; // X(2) + Y(2) + Z(2) + XYZout2(1) = 7 bytes
    if (_mmc5983_read_regs(MMC5983_XOUT0_ADDR, raw_data, 2) != MMC5983_OK) {
        return MMC5983_ERROR;
    }

    // 组合 18 位数据
    // X: XOUT0[7:0], XOUT1[7:0], XYZOUT2[7:6]
    data->x = ((int32_t)(raw_data[0]) << 10) | ((int32_t)(raw_data[1]) << 2) | ((raw_data[6] & 0xC0) >> 6);
    // Y: YOUT0[7:0], YOUT1[7:0], XYZOUT2[5:4]
    data->y = ((int32_t)(raw_data[2]) << 10) | ((int32_t)(raw_data[3]) << 2) | ((raw_data[6] & 0x30) >> 4);
    // Z: ZOUT0[7:0], ZOUT1[7:0], XYZOUT2[3:2]
    data->z = ((int32_t)(raw_data[4]) << 10) | ((int32_t)(raw_data[5]) << 2) | ((raw_data[6] & 0x0C) >> 2);

    // 转换为有符号整数 (18位补码)
    // if (data->x & 0x00020000) data->x |= 0xFFFC0000; // 检查第17位，如果为1，则符号扩展
    // if (data->y & 0x00020000) data->y |= 0xFFFC0000;
    // if (data->z & 0x00020000) data->z |= 0xFFFC0000;

    return MMC5983_OK;
}

mmc5983_status_t mmc5983_read_raw_data(mmc5983_raw_data_t *data) {
    if (data == NULL) {
        return MMC5983_ERROR;
    }

    uint8_t raw_data[7]; // X(2) + Y(2) + Z(2) + XYZout2(1) = 7 bytes
    uint8_t raw_xout[2];
    uint8_t raw_xyzout;
    // if (_mmc5983_read_regs(MMC5983_XYZOUT2_ADDR, &raw_xyzout, 1) != MMC5983_OK) {
    //     return MMC5983_ERROR;
    // }
    // if (_mmc5983_read_regs(MMC5983_XOUT0_ADDR, raw_xout, 2) != MMC5983_OK) {
    //     return MMC5983_ERROR;
    // }
    if (_mmc5983_read_regs(MMC5983_XOUT0_ADDR, raw_data, 7) != MMC5983_OK) {
        return MMC5983_ERROR;
    }

    // 组合 18 位数据
    // X: XOUT0[7:0], XOUT1[7:0], XYZOUT2[7:6]
    // data->x = ((int32_t)(raw_xout[0]) << 10) | ((int32_t)(raw_xout[1]) << 2) | ((raw_xyzout & 0xC0) >> 6);
    data->x = ((int32_t)(raw_data[0]) << 10) | ((int32_t)(raw_data[1]) << 2) | ((raw_data[6] & 0xC0) >> 6);
    // Y: YOUT0[7:0], YOUT1[7:0], XYZOUT2[5:4]
    data->y = ((int32_t)(raw_data[2]) << 10) | ((int32_t)(raw_data[3]) << 2) | ((raw_data[6] & 0x30) >> 4);
    // Z: ZOUT0[7:0], ZOUT1[7:0], XYZOUT2[3:2]
    data->z = ((int32_t)(raw_data[4]) << 10) | ((int32_t)(raw_data[5]) << 2) | ((raw_data[6] & 0x0C) >> 2);

    // 转换为有符号整数 (18位补码)
    // if (data->x & 0x00020000) data->x |= 0xFFFC0000; // 检查第17位，如果为1，则符号扩展
    // if (data->y & 0x00020000) data->y |= 0xFFFC0000;
    // if (data->z & 0x00020000) data->z |= 0xFFFC0000;

    return MMC5983_OK;
}
mmc5983_status_t mmc5983_readGauss(mmc5983_Gauss_t *dataGauss) {
    mmc5983_raw_data_t *raw_data;
    raw_data = &dataGauss->raw_data;
   if (mmc5983_read_raw_data(raw_data) != MMC5983_OK) {
       return MMC5983_ERROR;
   }
    // float sign_x = 1, sign_y = 1, sign_z = 1;
    // if (raw_data->x > 131072 - 1) {
    //     raw_data->x = 262144 - raw_data->x;
    //     sign_x = -1;
    //
    // }
    // if (raw_data->y > 131072 - 1) {
    //     raw_data->y = 262144 - raw_data->y;
    //     sign_y = -1;
    // }
    // if (raw_data->z > 131072 - 1) {
    //     raw_data->z = 262144 - raw_data->z;
    //     sign_z = -1;
    // }
    dataGauss->x = (float)raw_data->x / MMC5983_18BITS_RESOLUTION;
    dataGauss->y = (float)raw_data->y / MMC5983_18BITS_RESOLUTION;
    dataGauss->z = (float)raw_data->z / MMC5983_18BITS_RESOLUTION;
    // dataGauss->x = sign_x*(float)raw_data->x / MMC5983_18BITS_RESOLUTION;
    // dataGauss->y = sign_y*(float)raw_data->y / MMC5983_18BITS_RESOLUTION;
    // dataGauss->z = sign_z*(float)raw_data->z / MMC5983_18BITS_RESOLUTION;
    return  MMC5983_OK;
}

mmc5983_status_t mmc5983_measureGauss(mmc5983_Gauss_t *dataGauss) {

    if (mmc5983_start_measurement() == MMC5983_OK) {
        // 等待测量完成 (轮询方式)
        mmc5983_waitMeasureDone();
        if (mmc5983_readGauss(dataGauss) == MMC5983_OK) {
          printf("%f, %f, %f, %d, %d, %d\n", dataGauss->x, dataGauss->y, dataGauss->z, dataGauss->raw_data.x, dataGauss->raw_data.y, dataGauss->raw_data.z);
          // printf("%f, %f, %f\n", dataGauss->x, dataGauss->y, dataGauss->z);
        }
    }
    HAL_Delay(1); // 每次循环间隔 100ms

}
mmc5983_status_t mmc5983_start_temperature_measurement(void) {
    return _mmc5983_write_reg(MMC5983_CONTROL_0_ADDR, MMC5983_CONTROL_0_TM_T);
}

mmc5983_status_t mmc5983_read_raw_temperature(uint8_t *temp_raw) {
    if (temp_raw == NULL) {
        return MMC5983_ERROR;
    }
    return _mmc5983_read_reg(MMC5983_TOUT_ADDR, temp_raw);
}

mmc5983_status_t mmc5983_read_status(uint8_t *status) {
    if (status == NULL) {
        return MMC5983_ERROR;
    }
    return _mmc5983_read_reg(MMC5983_STATUS_ADDR, status);
}
