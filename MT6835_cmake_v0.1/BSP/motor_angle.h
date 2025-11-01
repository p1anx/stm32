//
// Created by xwj on 10/13/25.
//

/**
 * @file    motor_angle.h
 * @brief   带减速器的电机角度计算模块头文件
 */

#ifndef __MOTOR_ANGLE_H
#define __MOTOR_ANGLE_H

#include <stdint.h>
#include <stdbool.h>

// /**
//  * @brief  电机角度计算句柄
//  */
// typedef struct {
//     // 配置参数
//     float gear_ratio;              // 减速比 (例如: 10表示10:1)
//
//     // 电机轴(编码器)数据
//     float motor_angle_deg;         // 电机轴当前角度 (0-360°)
//     uint32_t motor_angle_raw;      // 电机轴原始编码器值
//     int32_t motor_turns;           // 电机轴转过的圈数
//     float motor_total_angle;       // 电机轴累积总角度
//
//     // 输出轴数据 (经过减速器)
//     float output_angle_deg;        // 输出轴当前角度 (0-360°)
//     int32_t output_turns;          // 输出轴转过的圈数
//     float output_total_angle;      // 输出轴累积总角度
//
//     // 内部变量
//     float prev_motor_angle;        // 上次电机轴角度
//     bool is_first_read;            // 是否首次读取
// } Motor_AngleCalc_Handle;
#endif

