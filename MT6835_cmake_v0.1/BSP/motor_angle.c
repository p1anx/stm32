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

#define ANGLE_THRESHOLD  270.0f  // 角度跳变检测阈值

/**
 * @brief  初始化电机角度计算器
 * @param  motor: 电机句柄
 * @param  gear_ratio: 减速比 (例如: 10表示10:1减速)
 */
void Motor_AngleCalc_Init(Motor_AngleCalc_Handle *motor, float gear_ratio)
{
    motor->gear_ratio = gear_ratio;
    motor->motor_angle_deg = 0.0f;
    motor->motor_angle_raw = 0;
    motor->motor_turns = 0;
    motor->motor_total_angle = 0.0f;
    motor->output_angle_deg = 0.0f;
    motor->output_turns = 0;
    motor->output_total_angle = 0.0f;
    motor->prev_motor_angle = 0.0f;
    motor->is_first_read = true;
}

/**
 * @brief  更新电机角度 (每次读取编码器后调用)
 * @param  motor: 电机句柄
 * @param  encoder_angle: 编码器读取的角度 (0-360度)
 */
void Motor_AngleCalc_Update(Motor_AngleCalc_Handle *motor, float encoder_angle)
{
    motor->motor_angle_deg = encoder_angle;

    // 第一次读取，初始化
    if (motor->is_first_read)
    {
        motor->prev_motor_angle = encoder_angle;
        motor->is_first_read = false;
        return;
    }

    // 计算角度变化
    float delta_angle = encoder_angle - motor->prev_motor_angle;

    // 检测角度跳变 (跨越0度/360度边界)
    if (delta_angle > ANGLE_THRESHOLD)
    {
        // 从359°跳到1° (逆时针跨越边界)
        delta_angle -= 360.0f;
        motor->motor_turns--;  // 反转时圈数减少
    }
    else if (delta_angle < -ANGLE_THRESHOLD)
    {
        // 从1°跳到359° (顺时针跨越边界)
        delta_angle += 360.0f;
        motor->motor_turns++;  // 正转时圈数增加
    }

    // 累积电机轴总角度
    motor->motor_total_angle += delta_angle;

    // 计算输出轴角度
    float output_total = motor->motor_total_angle / motor->gear_ratio;

    // 计算输出轴圈数和当前角度
    motor->output_turns = (int32_t)(output_total / 360.0f);
    motor->output_total_angle = output_total;
    motor->output_angle_deg = fmodf(output_total, 360.0f);

    // 处理负角度
    if (motor->output_angle_deg < 0)
    {
        motor->output_angle_deg += 360.0f;
    }

    // 保存当前角度用于下次计算
    motor->prev_motor_angle = encoder_angle;
}

/**
 * @brief  获取电机轴当前角度 (单圈,0-360度)
 * @param  motor: 电机句柄
 * @return 电机轴角度
 */
float Motor_GetMotorAngle(Motor_AngleCalc_Handle *motor)
{
    return motor->motor_angle_deg;
}

/**
 * @brief  获取电机轴总角度 (多圈累积)
 * @param  motor: 电机句柄
 * @return 电机轴累积角度
 */
float Motor_GetMotorTotalAngle(Motor_AngleCalc_Handle *motor)
{
    return motor->motor_total_angle;
}

/**
 * @brief  获取电机轴转过的圈数
 * @param  motor: 电机句柄
 * @return 圈数 (正数为顺时针,负数为逆时针)
 */
int32_t Motor_GetMotorTurns(Motor_AngleCalc_Handle *motor)
{
    return motor->motor_turns;
}

/**
 * @brief  获取输出轴当前角度 (单圈,0-360度)
 * @param  motor: 电机句柄
 * @return 输出轴角度
 */
float Motor_GetOutputAngle(Motor_AngleCalc_Handle *motor)
{
    return motor->output_angle_deg;
}

/**
 * @brief  获取输出轴总角度 (多圈累积)
 * @param  motor: 电机句柄
 * @return 输出轴累积角度
 */
float Motor_GetOutputTotalAngle(Motor_AngleCalc_Handle *motor)
{
    return motor->output_total_angle;
}

/**
 * @brief  获取输出轴转过的圈数
 * @param  motor: 电机句柄
 * @return 圈数 (正数为顺时针,负数为逆时针)
 */
int32_t Motor_GetOutputTurns(Motor_AngleCalc_Handle *motor)
{
    return motor->output_turns;
}

/**
 * @brief  获取输出轴角度(弧度)
 * @param  motor: 电机句柄
 * @return 输出轴角度(弧度,0-2π)
 */
float Motor_GetOutputAngleRad(Motor_AngleCalc_Handle *motor)
{
    return motor->output_angle_deg * M_PI / 180.0f;
}

/**
 * @brief  重置角度计数器
 * @param  motor: 电机句柄
 */
void Motor_AngleCalc_Reset(Motor_AngleCalc_Handle *motor)
{
    motor->motor_turns = 0;
    motor->motor_total_angle = 0.0f;
    motor->output_turns = 0;
    motor->output_total_angle = 0.0f;
    motor->is_first_read = true;
}

/**
 * @brief  设置当前位置为零点
 * @param  motor: 电机句柄
 * @note   保留已转过的圈数,只重置单圈角度偏移
 */
void Motor_SetZeroPosition(Motor_AngleCalc_Handle *motor)
{
    // 计算当前总角度
    float current_total = motor->motor_total_angle;

    // 减去当前单圈角度,保留整圈部分
    float full_rotations = (float)motor->motor_turns * 360.0f;
    motor->motor_total_angle = full_rotations;

    // 重新计算输出轴
    motor->output_total_angle = motor->motor_total_angle / motor->gear_ratio;
    motor->output_turns = (int32_t)(motor->output_total_angle / 360.0f);
    motor->output_angle_deg = fmodf(motor->output_total_angle, 360.0f);

    if (motor->output_angle_deg < 0)
    {
        motor->output_angle_deg += 360.0f;
    }
}

/**
 * @brief  完全重置到零点 (包括圈数)
 * @param  motor: 电机句柄
 */
void Motor_ResetToZero(Motor_AngleCalc_Handle *motor)
{
    Motor_AngleCalc_Reset(motor);
}