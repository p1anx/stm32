//
// Created by xwj on 10/12/25.
//

#ifndef MT6835_CMAKE_DRIVER_ENCODER_H
#define MT6835_CMAKE_DRIVER_ENCODER_H

/**
 * @file bsp_encoder.h
 * @version 0.1.0
 * @date August 2022
 * @author yongweixia
 *
 * @brief
 *   编码器角度寄存器读写接口
 *
 * @copyright (c) 2022 HYZY
 */
#ifndef __DRIVER_ENCODER_H__
#define __DRIVER_ENCODER_H__

#include "stdint.h"

#ifdef __cplusplus
extern "C" {
#endif

    /*!
     * @brief  单字节读取编码器寄存器
     * @param  add：寄存器地址
     * @return 相应寄存器值
     */
    uint8_t ReadMT6835(uint16_t add);

    /*!
     * @brief  读取编码器角度
     * @return 角度值
     */
    uint32_t ReadMT6835_Angle(void);

#ifdef __cplusplus
}
#endif

#endif //__DRIVER_ENCODER_H__


#endif // MT6835_CMAKE_DRIVER_ENCODER_H

