//
// Created by xwj on 10/13/25.
//

/**
 * @file    motor_angle.c
 * @brief   带减速器的电机角度计算模块
 * @note    编码器安装在电机轴(高速轴)，通过减速比计算输出轴角度
 */

#include "motor_angle.h"
#include <math.h>
