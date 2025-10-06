#include "ads1256.h"
#include <math.h>
#include <stdio.h>
// #include <string.h>

extern uint32_t tick;

void Delay_us(int time)
{
    int i;
    while (time--)
    {
        i = 10;
        while (i--)
            ;
    }
}
uint8_t SPI_SendByte(uint8_t data)
{
    uint8_t rd;
    HAL_SPI_TransmitReceive(&ads1256_spi, &data, &rd, 1, 1000);
    return rd;
}

void AD_WRITE(uint8_t addr, uint8_t data)
{
    uint8_t cmd = ADS1256_CMD_WREG | addr;
    uint8_t n = 0x00;

    SPI_CS_LOW;
    HAL_SPI_Transmit(&ads1256_spi, &cmd, 1, 1000);
    HAL_SPI_Transmit(&ads1256_spi, &n, 1, 1000);
    HAL_SPI_Transmit(&ads1256_spi, &data, 1, 1000);

    // SPI_SendByte(cmd);
    //	SPI_SendByte(n);
    //	SPI_SendByte(data);

    SPI_CS_HIGH;
}

uint8_t AD_READ(uint8_t addr)
{
    uint8_t data;
    uint8_t cmd = ADS1256_CMD_RREG | addr;
    uint8_t n = 0x00;
    SPI_CS_LOW;
    HAL_SPI_Transmit(&ads1256_spi, &cmd, 1, 1000);
    HAL_SPI_Transmit(&ads1256_spi, &n, 1, 1000);
    HAL_SPI_Receive(&ads1256_spi, &data, 1, 1000);
    SPI_CS_HIGH;

    return data;
}
// a=1 is reset pin high; a = else,reset pin low
void AD_RST(int a)
{
    if (a == 1)
    {
        HAL_GPIO_WritePin(AD_RST_GPIO_Port, AD_RST_Pin, GPIO_PIN_SET); // ads1256 rst低有效
        HAL_Delay(10);
    }
    else
    {
        HAL_GPIO_WritePin(AD_RST_GPIO_Port, AD_RST_Pin, GPIO_PIN_RESET); // ads1256 rst低有效
        HAL_Delay(10);
    }
}
void AD_SYSCAL(void)
{
    SPI_CS_LOW;
    // while(!DRDY);
    uint8_t cmd[] = {SYSOCAL};
    HAL_SPI_Transmit(&ads1256_spi, cmd, sizeof(cmd) / sizeof(cmd[0]), 1000);
    HAL_Delay(1000);
    uint8_t cmd1[] = {SYSGCAL};
    HAL_SPI_Transmit(&ads1256_spi, cmd1, sizeof(cmd1) / sizeof(cmd1[0]), 1000);

    SPI_CS_HIGH;
    HAL_Delay(1000);
}

void AD_SELFCAL(void)
{
    SPI_CS_LOW;

    // uint8_t cmd[] = {SELFOCAL};
    // HAL_SPI_Transmit(&ads1256_spi, cmd, sizeof(cmd)/sizeof(cmd[0]), 1000);
    // HAL_Delay(1000);
    // uint8_t cmd1[] = {SELFGCAL};
    // HAL_SPI_Transmit(&ads1256_spi, cmd1, sizeof(cmd1)/sizeof(cmd1[0]), 1000);
    uint8_t cmd2[] = {SELFCAL};
    HAL_SPI_Transmit(&ads1256_spi, cmd2, sizeof(cmd2) / sizeof(cmd2[0]), 1000);

    SPI_CS_HIGH;
    HAL_Delay(1000);
}

// ADS1256——STATUS must be set afer ACON and DRATE
void ADS1256_Init(uint8_t gain, uint8_t drate, uint8_t c)
{
    uint8_t status;
    AD_RST(1);
    uint8_t reset_cmd = ADS1256_CMD_REST;
    HAL_SPI_Transmit(&ads1256_spi, &reset_cmd, 1, 1000);
    HAL_Delay(10);

    AD_WRITE(ADS1256_ADCON, CLKOUT_OFF | DETECT_OFF | gain);
    AD_WRITE(ADS1256_DRATE, drate);
    AD_WRITE(ADS1256_STATUS, ACALON | BufferOFF);

    AD_WRITE(ADS1256_IO, 0x00);
    // AD_WRITE(ADS1256_MUX, 0x01);
    SelectChannel(1);

    SPI_CS_LOW;
    uint8_t sync_cmd = ADS1256_CMD_SYNC;
    HAL_SPI_Transmit(&ads1256_spi, &sync_cmd, 1, 1000);
    Delay_us(50); // SYNC命令后需要延时

    uint8_t wakeup_cmd = ADS1256_CMD_WAKEUP;
    HAL_SPI_Transmit(&ads1256_spi, &wakeup_cmd, 1, 1000);
    SPI_CS_HIGH;

    // AD_SYSCAL();
    // AD_SELFCAL();
    HAL_Delay(10); // 等待第一次转换完成
}
void ads1256_getInfo(void)
{
    uint8_t status = AD_READ(ADS1256_STATUS);
    uint8_t mux = AD_READ(ADS1256_MUX);
    uint8_t ad = AD_READ(ADS1256_ADCON);
    uint8_t drate = AD_READ(ADS1256_DRATE);
    printf("status = 0x%xh\n", status);
    printf("mux = 0x%xh\n", mux);
    printf("ad = 0x%xh\n", ad);
    printf("drate = 0x%xh\n", drate);
}
uint32_t ads1256_readData(void)
{
    uint8_t data[3];
    uint32_t value;

    SPI_CS_LOW;
    // uint8_t wakeup_cmd = ADS1256_CMD_WAKEUP;
    // HAL_SPI_Transmit(&ads1256_spi, &wakeup_cmd, 1, 1000);
    while (DRDY)
    {
        // printf("waiting data\n");
    }
    uint8_t rdata_cmd = ADS1256_CMD_RDATA;
    HAL_SPI_Transmit(&ads1256_spi, &rdata_cmd, 1, 1000);
    HAL_Delay(2);

    // if (HAL_SPI_TransmitReceive(&ads1256_spi, dummy, data, 3, 1000) != HAL_OK)
    if (HAL_SPI_Receive(&ads1256_spi, data, 3, 1000) != HAL_OK)
    {
        printf("[error] spi failed to recieve\n");
        return -10;
    }

    printf("data is ok\n");

    SPI_CS_HIGH;
    value = data[0] << 16 | data[1] << 8 | data[0];
    return value;
}
float ads1256_getVoltage(void)
{
    uint32_t result = ads1256_readData();
    float voltage;
    printf("raw value = %d\n", result);

    if (result > 0x7FFFFF)
    {
        result = 0xFFFFFF - (unsigned int)result + 1; //
        result &= 0xFFFFFF;
        result = -result;
    }
    voltage = result * 5 / (pow(2, 23) - 1);
    printf("voltage = %f\n", voltage);
    return voltage;
}

void ADS1256_Init_test(uint8_t gain, uint8_t drate, uint8_t c)
{
    // AD_RST(1);
    ads1256_getInfo();
    uint8_t reset_cmd = ADS1256_CMD_REST;
    uint8_t drdy = 0;
    HAL_SPI_Transmit(&ads1256_spi, &reset_cmd, 1, 1000);
    HAL_Delay(10);

    AD_WRITE(ADS1256_ADCON, CLKOUT_OFF | DETECT_OFF | gain);
    AD_WRITE(ADS1256_DRATE, drate);
    AD_WRITE(ADS1256_STATUS, ACALON | BufferON);

    AD_WRITE(ADS1256_IO, 0x00);
    // AD_WRITE(ADS1256_MUX, 0x01);
    SelectChannel(1);

    SPI_CS_LOW;
    uint8_t sync_cmd = ADS1256_CMD_SYNC;
    HAL_SPI_Transmit(&ads1256_spi, &sync_cmd, 1, 1000);
    Delay_us(50); // SYNC命令后需要延时
    drdy = ads1256_getDRDY_N();
    printf("after sync drdy = %d\n", drdy);

    // uint8_t wakeup_cmd = ADS1256_CMD_WAKEUP;
    // HAL_SPI_Transmit(&ads1256_spi, &wakeup_cmd, 1, 1000);
    SPI_CS_HIGH;

    printf("===================\n");
    printf("[ok] ads1256 init\n");
    printf("===================\n");
    ads1256_getInfo();
    HAL_Delay(10); // 等待第一次转换完成
    drdy = ads1256_getDRDY_N();
    printf("after sync drdy = %d\n", drdy);
    ads1256_getVoltage();
}
void AD_CAL_RegRead(void)
{
    uint8_t ofc[3];
    uint8_t fsc[3];

    uint32_t fscc, ofcc;
    double voltage_fscc, voltage_ofcc;
    uint32_t alph = 0x3c0000;
    float beta = 1.74;
    ofc[0] = AD_READ(0X05);
    ofc[1] = AD_READ(0X06);
    ofc[2] = AD_READ(0X07);
    //  printf("ofc0:%x\n", ofc[0]);
    //  printf("ofc1:%x\n", ofc[1]);
    //  printf("ofc2:%x\n", ofc[2]);
    ofcc = ofc[0] | ofc[1] << 8 | ofc[2] << 16;
    voltage_ofcc = ofcc * 5 / (pow(2, 23) - 1);
    printf("ofc:%x\n", ofcc);
    printf("ofc_v:%lf V\n", voltage_ofcc);

    fsc[0] = AD_READ(0X08);
    fsc[1] = AD_READ(0X09);
    fsc[2] = AD_READ(0X0a);
    //  printf("fsc0:%x\n", fsc[0]);
    //  printf("fsc1:%x\n", fsc[1]);
    //  printf("fsc2:%x\n", fsc[2]);
    fscc = fsc[0] | fsc[1] << 8 | fsc[2] << 16;
    voltage_fscc = fscc * 5 / (pow(2, 23) - 1);
    printf("fsc:%x\n", fscc);
    printf("fsc_v:%lf V\n", voltage_fscc);
}

void SelectChannel(uint8_t c)
{
    switch (c)
    {
    case 1:
        AD_WRITE(ADS1256_MUX, ADS1256_MUXP_AIN0 | ADS1256_MUXN_AINCOM);
        break;
    case 2:
        AD_WRITE(ADS1256_MUX, ADS1256_MUXP_AIN1 | ADS1256_MUXN_AINCOM);
        break;
    case 3:
        AD_WRITE(ADS1256_MUX, ADS1256_MUXP_AIN2 | ADS1256_MUXN_AINCOM);
        break;
    case 4:
        AD_WRITE(ADS1256_MUX, ADS1256_MUXP_AIN3 | ADS1256_MUXN_AINCOM);
        break;
    case 5:
        AD_WRITE(ADS1256_MUX, ADS1256_MUXP_AIN4 | ADS1256_MUXN_AINCOM);
        break;
    case 6:
        AD_WRITE(ADS1256_MUX, ADS1256_MUXP_AIN5 | ADS1256_MUXN_AINCOM);
        break;
    case 7:
        AD_WRITE(ADS1256_MUX, ADS1256_MUXP_AIN6 | ADS1256_MUXN_AINCOM);
        break;
    case 8:
        AD_WRITE(ADS1256_MUX, ADS1256_MUXP_AIN7 | ADS1256_MUXN_AINCOM);
        break;
    case 12:
        AD_WRITE(ADS1256_MUX, ADS1256_MUXP_AIN0 | ADS1256_MUXN_AIN1);
        break;
    case 13:
        AD_WRITE(ADS1256_MUX, ADS1256_MUXP_AIN0 | ADS1256_MUXN_AIN2);
        break;
    default:
        AD_WRITE(ADS1256_MUX, ADS1256_MUXP_AIN0 | ADS1256_MUXN_AINCOM);
        break;
    }
}
int ads1256_getDRDY_N(void)
{
    uint8_t status_reg = AD_READ(ADS1256_STATUS);
    uint8_t drdy_n = status_reg & 0x1;
    return drdy_n;
}

uint32_t AD_ReadData(void)
{
    uint8_t cmd[3] = {ADS1256_CMD_SYNC, ADS1256_CMD_WAKEUP, ADS1256_CMD_RDATA};
    uint8_t data[3];
    uint8_t dummy[3];
    uint32_t rd;
    // SelectChannel(1); // 不影响采集
    SPI_CS_LOW;

    // uint8_t drdy = ads1256_getDRDY_N();
    while (ads1256_getDRDY_N())
    {
        printf("DRDY is waiting data\n");
    }

    // AD_RST(0);
    uint8_t sync_cmd = ADS1256_CMD_SYNC;
    HAL_SPI_Transmit(&ads1256_spi, &sync_cmd, 1, 1000);

    uint8_t wakeup_cmd = ADS1256_CMD_WAKEUP;
    HAL_SPI_Transmit(&ads1256_spi, &wakeup_cmd, 1, 1000);
    uint8_t rdata_cmd = ADS1256_CMD_RDATA;
    HAL_SPI_Transmit(&ads1256_spi, &rdata_cmd, 1, 1000);
    // if (HAL_SPI_Transmit(&ads1256_spi, cmd, sizeof(cmd) / sizeof(cmd[0]), 1000) != HAL_OK)
    // if (HAL_SPI_Transmit(&ads1256_spi, cmd, 1, 1000) != HAL_OK)
    // {
    //     printf("[error] spi failed to send");
    //     return -1;
    // }
    HAL_Delay(2);

    // if (HAL_SPI_TransmitReceive(&ads1256_spi, dummy, data, 3, 1000) != HAL_OK)
    if (HAL_SPI_Receive(&ads1256_spi, data, 3, 1000) != HAL_OK)
    {
        printf("[error] spi failed to recieve\n");
        return -10;
    }

    SPI_CS_HIGH;

    rd = data[0] << 16 | data[1] << 8 | data[2];
    printf("rd = %d\n", rd);
    for (int i = 0; i < 3; i++)
    {
        printf("data %d = %d \n", i, data[i]);
    }
    return rd;
}

// uint32_t AD_ReadData(void)
// {
//     uint8_t data[3];
//     uint32_t rd;
//
//     SPI_CS_LOW;
//
//     // 1. 等待DRDY为低电平（数据准备好）
//     while (DRDY)
//         ;
//
//     // 2. 发送RDATA命令
//     uint8_t cmd = ADS1256_CMD_RDATA;
//     HAL_SPI_Transmit(&ads1256_spi, &cmd, 1, 1000);
//
//     // 3. 添加短暂延时（根据时钟频率，通常需要24个CLKIN周期）
//     Delay_us(10); // 或者使用HAL_Delay(1);
//
//     // 4. 读取3字节数据
//     HAL_SPI_Receive(&ads1256_spi, data, 3, 1000);
//
//     SPI_CS_HIGH;
//
//     // 5. 组合24位数据
//     rd = ((uint32_t)data[0] << 16) | ((uint32_t)data[1] << 8) | data[2];
//
//     return rd;
// }
uint32_t AD_ReadData_v0(void)
{
    SelectChannel(1); // 不影响采集
    uint8_t cmd[3] = {ADS1256_CMD_SYNC, ADS1256_CMD_WAKEUP, ADS1256_CMD_RDATA};
    uint8_t data[3];
    uint8_t dummy[3];
    uint32_t rd;
    SPI_CS_LOW;
    while (DRDY)
        ;

    if (HAL_SPI_Transmit(&ads1256_spi, cmd, sizeof(cmd) / sizeof(cmd[0]), 1000) != HAL_OK)
    {
        printf("[error] spi failed to send");
        return -1;
    }
    // HAL_Delay(1);

    if (HAL_SPI_TransmitReceive(&ads1256_spi, dummy, data, 3, 1000) != HAL_OK)
    {
        printf("[error] spi failed to recieve\n");
        return -1;
    }

    SPI_CS_HIGH;

    rd = data[0] << 16 | data[1] << 8 | data[2];
    return rd;
}
// int

void Data_Print(void)
{

    int result;
    double voltage;
    // if(tick == 1){
    // 	result = AD_ReadData();
    // 	tick = 0;
    // }
    result = AD_ReadData();

    if (result > 0x7FFFFF)
    {
        result = 0xFFFFFF - (unsigned int)result + 1; //
        result &= 0xFFFFFF;
        result = -result;
    }
    voltage = result * 5 / (pow(2, 23) - 1);
    printf("raw_value = %d\n", result);
    printf("voltage2 = %lf v\n", voltage);
    // printf("voltage2 = %lf v", voltage);
    // fflush(stdout);
    // printf("\n\r");
}

void Matlab_Print(void)
{
    int result;
    uint8_t flag = '*';
    uint8_t rdata[3];
    result = AD_ReadData();
    //	if(result > 0x7FFFFF){
    //		result = 0xFFFFFF - (unsigned int)result + 1; //����ȡֵ
    //		result &= 0xFFFFFF;
    ////		result = -result;
    //	}

    rdata[0] = (result & 0xff0000) >> 16;
    rdata[1] = (result & 0xff00) >> 8;
    rdata[2] = (result & 0xff);
    HAL_UART_Transmit(&HUART, &flag, 1, 1000);
    HAL_UART_Transmit(&HUART, rdata, 3, 1000);
    HAL_Delay(5);
    //	HAL_UART_Transmit(&huart1, &result, 3, 1000);
}

void Transmit_To_Python(void)
{
    int result;
    uint8_t flag = 0x19;
    uint8_t rdata[3];
    result = AD_ReadData();

    rdata[0] = (result & 0xff0000) >> 16;
    rdata[1] = (result & 0xff00) >> 8;
    rdata[2] = (result & 0xff);
    printf("read data = %d\n", result);
    HAL_UART_Transmit(&HUART, &flag, 1, 1000);
    HAL_UART_Transmit(&HUART, rdata, 3, 1000);
    HAL_Delay(5);
}
