//
// Created by xwj on 10/12/25.
//

#include "driver_encoder.h"
// #include "../mt6835.bak.h"
#include "mt6835.h"
/**
 * @file bsp_encoder.c
 * @version 0.1.0
 * @date August 2022
 * @author yongweixia
 *
 * @brief
 *   编码器角度寄存器读写接口
 *
 * @copyright (c) 2022 HYZY
 */
#include "driver_encoder.h"
//#include "bsp_spi.h"
//#include "bsp_gpio.h"
#include "stdio.h"
#include "stdlib.h"
#include "main.h"
#include "spi.h"
#include "usart.h"
#include "gpio.h"
#include  "math.h"
//#include "schedul_task.h"

#ifdef __cplusplus
extern "C" {
#endif

#define READCOMMAND 0x3000

/* CRC校验查表，公式：X8+X2+X+1 */
static uint8_t Crc8Table[256]=
{
    0x00,0x07,0x0e,0x09,0x1c,0x1b,0x12,0x15,0x38,0x3f,0x36,0x31,0x24,0x23,0x2a,0x2d,
    0x70,0x77,0x7e,0x79,0x6c,0x6b,0x62,0x65,0x48,0x4f,0x46,0x41,0x54,0x53,0x5a,0x5d,
    0xe0,0xe7,0xee,0xe9,0xfc,0xfb,0xf2,0xf5,0xd8,0xdf,0xd6,0xd1,0xc4,0xc3,0xca,0xcd,
    0x90,0x97,0x9e,0x99,0x8c,0x8b,0x82,0x85,0xa8,0xaf,0xa6,0xa1,0xb4,0xb3,0xba,0xbd,
    0xc7,0xc0,0xc9,0xce,0xdb,0xdc,0xd5,0xd2,0xff,0xf8,0xf1,0xf6,0xe3,0xe4,0xed,0xea,
    0xb7,0xb0,0xb9,0xbe,0xab,0xac,0xa5,0xa2,0x8f,0x88,0x81,0x86,0x93,0x94,0x9d,0x9a,
    0x27,0x20,0x29,0x2e,0x3b,0x3c,0x35,0x32,0x1f,0x18,0x11,0x16,0x03,0x04,0x0d,0x0a,
    0x57,0x50,0x59,0x5e,0x4b,0x4c,0x45,0x42,0x6f,0x68,0x61,0x66,0x73,0x74,0x7d,0x7a,
    0x89,0x8e,0x87,0x80,0x95,0x92,0x9b,0x9c,0xb1,0xb6,0xbf,0xb8,0xad,0xaa,0xa3,0xa4,
    0xf9,0xfe,0xf7,0xf0,0xe5,0xe2,0xeb,0xec,0xc1,0xc6,0xcf,0xc8,0xdd,0xda,0xd3,0xd4,
    0x69,0x6e,0x67,0x60,0x75,0x72,0x7b,0x7c,0x51,0x56,0x5f,0x58,0x4d,0x4a,0x43,0x44,
    0x19,0x1e,0x17,0x10,0x05,0x02,0x0b,0x0c,0x21,0x26,0x2f,0x28,0x3d,0x3a,0x33,0x34,
    0x4e,0x49,0x40,0x47,0x52,0x55,0x5c,0x5b,0x76,0x71,0x78,0x7f,0x6a,0x6d,0x64,0x63,
    0x3e,0x39,0x30,0x37,0x22,0x25,0x2c,0x2b,0x06,0x01,0x08,0x0f,0x1a,0x1d,0x14,0x13,
    0xae,0xa9,0xa0,0xa7,0xb2,0xb5,0xbc,0xbb,0x96,0x91,0x98,0x9f,0x8a,0x8d,0x84,0x83,
    0xde,0xd9,0xd0,0xd7,0xc2,0xc5,0xcc,0xcb,0xe6,0xe1,0xe8,0xef,0xfa,0xfd,0xf4,0xf3,
};

/*!
 * @brief  CRC校验：X8+X2+X+1
 * @return CRC校验值
 */
static uint8_t Crc_Table(uint8_t *ptr, uint8_t len)
{
    uint8_t crc=0x00;  //计算的初始crc值，也存放结果
    while(len--)
    {
        crc ^= *ptr++; //每次先与需要计算的数据异或,计算完指向下一数据
        crc = Crc8Table[crc];
    }
    return (crc);
}


/*!
 * @brief  单字节读取编码器寄存器
 * @param  add：寄存器地址
 * @return 相应寄存器值
 */
uint8_t ReadMT6835(uint16_t add)
{
    uint8_t pTxData[3]={0,0,0},pRxData[3]={0,0,0};

    HAL_GPIO_WritePin(MT6835_SPI_CS_PORT, MT6835_SPI_CS_PIN, GPIO_PIN_SET);//0011 0000 0000 0011
    add=((add&0x0FFF)|READCOMMAND);
    pTxData[0]=(uint8_t)(add>>8);
    pTxData[1]=(uint8_t)(add>>0);
    pTxData[2]=(uint8_t)(add>>0);

    HAL_GPIO_WritePin(MT6835_SPI_CS_PORT,MT6835_SPI_CS_PIN, GPIO_PIN_RESET);
		HAL_SPI_TransmitReceive(&hspi2,(unsigned char *)pTxData,(unsigned char *)pRxData,3, 100);
//    spi1_transmit_receive(pTxData, pRxData, 3, 0xffff);
    HAL_GPIO_WritePin(MT6835_SPI_CS_PORT,MT6835_SPI_CS_PIN, GPIO_PIN_SET);

    return(pRxData[2]);
}

/*!
 * @brief  读取编码器角度
 * @return 角度值
 */
//int8_t  Zero_Cross_Valid      = 0;
//int8_t  Direction_Of_Rotation = 0;
//int8_t  Large_Or_Small        = 0;
//int8_t  Counter1              = 0;
//int8_t  Counter2              = 0;
//int8_t  Counter3              = 0;
int32_t MT6835_Angle          = 0;
uint32_t ReadMT6835_Angle(void)
{
    uint8_t MT6835Register[4]      = {0,0,0,0};
    //int32_t Temp_MT6835_Angle_New  =  0;
    //int32_t Temp_MT6835_Angle_Last =  0;

    //Counter2++;

    MT6835Register[0] = ReadMT6835(0x03);
    MT6835Register[1] = ReadMT6835(0x04);
    MT6835Register[2] = ReadMT6835(0x05);
    MT6835Register[3] = ReadMT6835(0x06);

    /* 举例：以总结规律(以计算5个角度值的平均数为例)
     *  15 +  10 +   5 +   0 + 355 =  385 - 1 * 360 =  25 / 5 =  5
     *  10 +   5 +   0 + 355 + 350 =  720 - 2 * 360 =   0 / 5 =  0
     *   5 +   0 + 355 + 350 + 345 = 1055 - 3 * 360 = -25 / 5 = -5 + 360 = 355
     * 340 + 355 +  10 +  25 +  40 =  770 - 2 * 360 =  50 / 5 = 10
     * 355 +  10 +  25 +  40 +  55 =  485 - 1 * 360 = 125 / 5 = 25
     * 345 + 350 + 355 + 360 +   5 = 1415 - 4 * 360 = -25 / 5 = -5 + 360 = 355 */
    if(Crc_Table(&MT6835Register[0],3) == MT6835Register[3])
    {
        //Counter1++;
        //if(Counter1 <= 16)
        //{
            MT6835_Angle = ((MT6835Register[0]<<13)|(MT6835Register[1]<<5)|(MT6835Register[2]>>3));
        //    Temp_MT6835_Angle_New = ((MT6835Register[0]<<13)|(MT6835Register[1]<<5)|(MT6835Register[2]>>3));
        //    if(Counter1 == 1)
        //    {
        //        MT6835_Angle = MT6835_Angle + Temp_MT6835_Angle_New;
        //    }
        //    else
        //    {
        //        if(((abs(Temp_MT6835_Angle_New - Temp_MT6835_Angle_Last)) > 1048576))
        //        {
        //            if(Temp_MT6835_Angle_New < Temp_MT6835_Angle_Last)
        //            {   //逆时针旋转
        //                Counter3 = Counter1 - 1;
        //            }
        //            else
        //            {   //顺时针旋转
        //                Counter3 = 16 - (Counter1 - 1);
        //            }
        //            MT6835_Angle = MT6835_Angle + Temp_MT6835_Angle_New;
        //        }
        //        else
        //        {
        //            MT6835_Angle = MT6835_Angle + Temp_MT6835_Angle_New;
        //        }
        //    }

        //    if(Counter1 == 16)
        //    {
        //        MT6835_Angle = (MT6835_Angle - Counter3 * 360) >> 4; //右移4位相当于除以16求平均数
        //        if(MT6835_Angle < 0)
        //        {
        //            MT6835_Angle = MT6835_Angle + 360;
        //        }
        //        else
        //        {
        //            ;
        //        }
        //        Control.MT6835_Angle_q31t = MT6835_Angle;
        //    }
        //    else
        //    {
        //        ;
        //    }
        //}
        //else
        //{
        //    ;
        //}
    }
    //else
    //{
    //    ;
    //}

    //if(Counter2 == 20)
    //{
    //    Zero_Cross_Valid      = 0;
    //    Direction_Of_Rotation = 0;
    //    Large_Or_Small        = 0;
    //    Counter1              = 0;
    //    Counter2              = 0;
    //    Counter3              = 0;
    //    MT6835_Angle          = 0;
    //}
    //else
    //{
    //    ;
    //}

    //Temp_MT6835_Angle_Last = Temp_MT6835_Angle_New;

    return(MT6835_Angle);
}

#ifdef __cplusplus
}
#endif
