//
// Created by xwj on 10/13/25.
//

/**
 * @file    motor_example.c
 * @brief   减速电机(减速比10:1)完整使用示例
 * @note    编码器MT6835安装在电机轴，通过减速器计算输出轴角度
 */

#include "main.h"
#include "mt6835.h"
#include "motor_angle.h"
#include <stdio.h>

/* 外部变量 */
extern SPI_HandleTypeDef hspi2;

/* 全局变量 */
MT6835_Handle encoder;              // 编码器句柄
Motor_AngleCalc_Handle motor;       // 电机角度计算句柄

/**
 * @brief  示例1: 基本使用 - 读取输出轴角度
 */
void Example1_BasicUsage(void)
{
    // 初始化编码器
    MT6835_Init(&encoder, &hspi2, GPIOB, GPIO_PIN_12);

    // 初始化角度计算器 (减速比10:1)
    Motor_AngleCalc_Init(&motor, 10.0f);

    printf("[ok] init\r\n");
    printf("ratio: %.1f:1\r\n\r\n", motor.gear_ratio);

    while(1)
    {
        // 1. 读取编码器角度
        MT6835_ReadAngle(&encoder);
        float encoder_angle = MT6835_GetAngleDegrees(&encoder);

        // 2. 更新角度计算
        Motor_AngleCalc_Update(&motor, encoder_angle);

        // 3. 获取输出轴角度
        float output_angle = Motor_GetOutputAngle(&motor);

        // 4. 显示结果
        printf("motor angle: %.2f | actual angle: %.2f\r\n",
               encoder_angle, output_angle);

        HAL_Delay(10);
    }
}

/**
 * @brief  示例2: 多圈计数 - 显示转过的圈数
 */
// void Example2_MultiTurnCounting(void)
// {
//     MT6835_Init(&encoder, &hspi1, GPIOA, GPIO_PIN_4);
//     Motor_AngleCalc_Init(&motor, 10.0f);
//
//     printf("多圈计数示例 - 旋转电机观察圈数变化\r\n\r\n");
//
//     while(1)
//     {
//         // 读取并更新
//         MT6835_ReadAngle(&encoder);
//         Motor_AngleCalc_Update(&motor, MT6835_GetAngleDegrees(&encoder));
//
//         // 获取各项数据
//         int32_t motor_turns = Motor_GetMotorTurns(&motor);
//         float motor_total = Motor_GetMotorTotalAngle(&motor);
//         int32_t output_turns = Motor_GetOutputTurns(&motor);
//         float output_total = Motor_GetOutputTotalAngle(&motor);
//         float output_angle = Motor_GetOutputAngle(&motor);
//
//         // 显示
//         printf("电机轴: %ld圈 (%.1f°) | 输出轴: %ld圈 + %.2f° (总计%.1f°)\r\n",
//                motor_turns, motor_total,
//                output_turns, output_angle, output_total);
//
//         HAL_Delay(100);
//     }
// }
//
// /**
//  * @brief  示例3: 位置控制 - 控制输出轴到指定角度
//  */
// void Example3_PositionControl(void)
// {
//     MT6835_Init(&encoder, &hspi1, GPIOA, GPIO_PIN_4);
//     Motor_AngleCalc_Init(&motor, 10.0f);
//
//     float target_angle = 90.0f;  // 目标角度: 90度
//     float tolerance = 1.0f;      // 容差: ±1度
//
//     printf("位置控制示例\r\n");
//     printf("目标角度: %.2f°\r\n\r\n", target_angle);
//
//     while(1)
//     {
//         // 读取当前角度
//         MT6835_ReadAngle(&encoder);
//         Motor_AngleCalc_Update(&motor, MT6835_GetAngleDegrees(&encoder));
//
//         float current_angle = Motor_GetOutputAngle(&motor);
//         float error = target_angle - current_angle;
//
//         // 处理跨越0度的情况
//         if (error > 180.0f) error -= 360.0f;
//         if (error < -180.0f) error += 360.0f;
//
//         // 判断是否到位
//         if (fabsf(error) < tolerance)
//         {
//             printf("✓ 到达目标位置! 当前: %.2f°, 误差: %.2f°\r\n",
//                    current_angle, error);
//             // 这里可以停止电机
//         }
//         else
//         {
//             printf("→ 移动中... 当前: %.2f°, 误差: %.2f°\r\n",
//                    current_angle, error);
//             // 这里可以根据误差控制电机速度和方向
//             // 例如: PWM = Kp * error
//         }
//
//         HAL_Delay(50);
//     }
// }
//
// /**
//  * @brief  示例4: 速度测量 - 测量输出轴转速
//  */
// void Example4_VelocityMeasurement(void)
// {
//     MT6835_Init(&encoder, &hspi1, GPIOA, GPIO_PIN_4);
//     Motor_AngleCalc_Init(&motor, 10.0f);
//
//     float prev_total_angle = 0.0f;
//     uint32_t prev_time = 0;
//
//     printf("速度测量示例\r\n\r\n");
//
//     // 首次读取初始化
//     MT6835_ReadAngle(&encoder);
//     Motor_AngleCalc_Update(&motor, MT6835_GetAngleDegrees(&encoder));
//     prev_total_angle = Motor_GetOutputTotalAngle(&motor);
//     prev_time = HAL_GetTick();
//
//     HAL_Delay(100);
//
//     while(1)
//     {
//         // 读取当前角度
//         MT6835_ReadAngle(&encoder);
//         Motor_AngleCalc_Update(&motor, MT6835_GetAngleDegrees(&encoder));
//
//         float current_total = Motor_GetOutputTotalAngle(&motor);
//         uint32_t current_time = HAL_GetTick();
//
//         // 计算速度
//         float delta_angle = current_total - prev_total_angle;
//         float delta_time = (current_time - prev_time) / 1000.0f;  // 转为秒
//
//         float angular_velocity = delta_angle / delta_time;  // 度/秒
//         float rpm_output = angular_velocity / 6.0f;         // 输出轴转速(RPM)
//         float rpm_motor = rpm_output * motor.gear_ratio;    // 电机轴转速(RPM)
//
//         // 显示结果
//         printf("输出轴: %.2f RPM | 电机轴: %.2f RPM | 角速度: %.2f °/s\r\n",
//                rpm_output, rpm_motor, angular_velocity);
//
//         // 更新上次数据
//         prev_total_angle = current_total;
//         prev_time = current_time;
//
//         HAL_Delay(100);
//     }
// }
//
// /**
//  * @brief  示例5: 零点设置
//  */
// void Example5_ZeroCalibration(void)
// {
//     MT6835_Init(&encoder, &hspi1, GPIOA, GPIO_PIN_4);
//     Motor_AngleCalc_Init(&motor, 10.0f);
//
//     printf("零点校准示例\r\n");
//     printf("1. 旋转电机到期望的零点位置\r\n");
//     printf("2. 按下按钮设置零点\r\n\r\n");
//
//     bool zero_set = false;
//
//     while(1)
//     {
//         // 读取角度
//         MT6835_ReadAngle(&encoder);
//         Motor_AngleCalc_Update(&motor, MT6835_GetAngleDegrees(&encoder));
//
//         float output_angle = Motor_GetOutputAngle(&motor);
//         float output_total = Motor_GetOutputTotalAngle(&motor);
//
//         // 检测按钮按下 (假设使用PA0作为按钮)
//         if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) == GPIO_PIN_RESET && !zero_set)
//         {
//             // 设置当前位置为零点
//             Motor_SetZeroPosition(&motor);
//
//             printf("\r\n✓ 零点已设置!\r\n\r\n");
//             zero_set = true;
//         }
//
//         if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) == GPIO_PIN_SET)
//         {
//             zero_set = false;
//         }
//
//         // 显示当前角度
//         printf("当前角度: %.2f° (总计: %.2f°)\r\n",
//                output_angle, output_total);
//
//         HAL_Delay(100);
//     }
// }
//
// /**
//  * @brief  示例6: 综合显示 - 显示所有信息
//  */
// void Example6_ComprehensiveDisplay(void)
// {
//     MT6835_Init(&encoder, &hspi1, GPIOA, GPIO_PIN_4);
//     Motor_AngleCalc_Init(&motor, 10.0f);
//
//     uint32_t loop_count = 0;
//
//     printf("======================================\r\n");
//     printf("  减速电机监控系统 (减速比 10:1)    \r\n");
//     printf("======================================\r\n\r\n");
//
//     while(1)
//     {
//         // 读取编码器
//         MT6835_ReadAngle(&encoder);
//         uint32_t raw_value = MT6835_GetAngleRaw(&encoder);
//         float encoder_angle = MT6835_GetAngleDegrees(&encoder);
//
//         // 更新角度计算
//         Motor_AngleCalc_Update(&motor, encoder_angle);
//
//         // 每10次循环显示一次完整信息
//         if (loop_count % 10 == 0)
//         {
//             printf("\r\n========== 当前状态 ==========\r\n");
//
//             // 编码器原始数据
//             printf("编码器原始值: %lu / 2097151\r\n", raw_value);
//
//             // 电机轴信息
//             printf("\n【电机轴】\r\n");
//             printf("  单圈角度: %.2f°\r\n", Motor_GetMotorAngle(&motor));
//             printf("  转过圈数: %ld 圈\r\n", Motor_GetMotorTurns(&motor));
//             printf("  累积角度: %.2f°\r\n", Motor_GetMotorTotalAngle(&motor));
//
//             // 输出轴信息
//             printf("\n【输出轴】\r\n");
//             printf("  单圈角度: %.2f° (%.4f rad)\r\n",
//                    Motor_GetOutputAngle(&motor),
//                    Motor_GetOutputAngleRad(&motor));
//             printf("  转过圈数: %ld 圈\r\n", Motor_GetOutputTurns(&motor));
//             printf("  累积角度: %.2f°\r\n", Motor_GetOutputTotalAngle(&motor));
//
//             printf("=============================\r\n");
//         }
//         else
//         {
//             // 简化显示
//             printf("输出轴: %.2f°  ", Motor_GetOutputAngle(&motor));
//         }
//
//         loop_count++;
//         HAL_Delay(100);
//     }
// }
//
// /**
//  * @brief  主函数
//  */
// // int main(void)
// // {
// //     HAL_Init();
// //     SystemClock_Config();
// //     MX_GPIO_Init();
// //     MX_SPI1_Init();
// //     MX_USART1_UART_Init();
// //
// //     // 选择要运行的示例
// //     // Example1_BasicUsage();              // 基本使用
// //     // Example2_MultiTurnCounting();       // 多圈计数
// //     // Example3_PositionControl();         // 位置控制
// //     // Example4_VelocityMeasurement();     // 速度测量
// //     // Example5_ZeroCalibration();         // 零点校准
// //     Example6_ComprehensiveDisplay();    // 综合显示
// //
// //     while(1);
// // }