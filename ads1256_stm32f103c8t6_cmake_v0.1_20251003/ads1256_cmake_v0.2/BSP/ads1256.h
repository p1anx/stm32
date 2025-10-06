#ifndef __ADS1256_H
#define __ADS1256_H

#include "stm32f1xx.h"
#include "gpio.h"
#include "spi.h"
#include "usart.h"

#define HUART huart1

#define ads1256_spi hspi1

#define AD_CS_GPIO_Port GPIOA
#define AD_CS_Pin GPIO_PIN_4
#define AD_DRDY_GPIO_Port GPIOB
#define AD_DRDY_Pin GPIO_PIN_0
#define AD_RST_GPIO_Port GPIOB
#define AD_RST_Pin GPIO_PIN_1

#define SPI_CS_LOW HAL_GPIO_WritePin(AD_CS_GPIO_Port, AD_CS_Pin, GPIO_PIN_RESET)
#define SPI_CS_HIGH HAL_GPIO_WritePin(AD_CS_GPIO_Port, AD_CS_Pin, GPIO_PIN_SET)

#define DRDY HAL_GPIO_ReadPin(AD_DRDY_GPIO_Port, AD_DRDY_Pin)

#define SELFCAL 0xF0
#define SELFOCAL 0xF1
#define SELFGCAL 0xF2
#define SYSOCAL 0xF3
#define SYSGCAL 0xF4

#define ADS1256_CMD_WAKEUP 0x00
#define ADS1256_CMD_RDATA 0x01
#define ADS1256_CMD_RDATAC 0x03
#define ADS1256_CMD_SDATAC 0x0f
#define ADS1256_CMD_RREG 0x10
#define ADS1256_CMD_WREG 0x50
#define ADS1256_CMD_SELFCAL 0xf0
#define ADS1256_CMD_SELFOCAL 0xf1
#define ADS1256_CMD_SELFGCAL 0xf2
#define ADS1256_CMD_SYSOCAL 0xf3
#define ADS1256_CMD_SYSGCAL 0xf4
#define ADS1256_CMD_SYNC 0xfc
#define ADS1256_CMD_STANDBY 0xfd
#define ADS1256_CMD_REST 0xfe

// define the ADS1256 register values
#define ADS1256_STATUS 0x00
#define ADS1256_MUX 0x01
#define ADS1256_ADCON 0x02
#define ADS1256_DRATE 0x03
#define ADS1256_IO 0x04
#define ADS1256_OFC0 0x05
#define ADS1256_OFC1 0x06
#define ADS1256_OFC2 0x07
#define ADS1256_FSC0 0x08
#define ADS1256_FSC1 0x09
#define ADS1256_FSC2 0x0A

#define CLKOUT_OFF (0x00 << 5)
#define CLKOUT_CLKIN (0x01 << 5)
#define DETECT_OFF (0x00 << 3)
#define DETECT_ON_2UA (0x02 << 3)

// define multiplexer codes
#define ADS1256_MUXP_AIN0 0x00
#define ADS1256_MUXP_AIN1 0x10
#define ADS1256_MUXP_AIN2 0x20
#define ADS1256_MUXP_AIN3 0x30
#define ADS1256_MUXP_AIN4 0x40
#define ADS1256_MUXP_AIN5 0x50
#define ADS1256_MUXP_AIN6 0x60
#define ADS1256_MUXP_AIN7 0x70
#define ADS1256_MUXP_AINCOM 0x80

#define ADS1256_MUXN_AIN0 0x00
#define ADS1256_MUXN_AIN1 0x01
#define ADS1256_MUXN_AIN2 0x02
#define ADS1256_MUXN_AIN3 0x03
#define ADS1256_MUXN_AIN4 0x04
#define ADS1256_MUXN_AIN5 0x05
#define ADS1256_MUXN_AIN6 0x06
#define ADS1256_MUXN_AIN7 0x07
#define ADS1256_MUXN_AINCOM 0x08

// define gain codes
#define ADS1256_GAIN_1 0x00
#define ADS1256_GAIN_2 0x01
#define ADS1256_GAIN_4 0x02
#define ADS1256_GAIN_8 0x03
#define ADS1256_GAIN_16 0x04
#define ADS1256_GAIN_32 0x05
#define ADS1256_GAIN_64 0x06
// #define ADS1256_GAIN_64     0x07

// define drate codes
#define ADS1256_DRATE_30000SPS 0xF0
#define ADS1256_DRATE_15000SPS 0xE0
#define ADS1256_DRATE_7500SPS 0xD0
#define ADS1256_DRATE_3750SPS 0xC0
#define ADS1256_DRATE_2000SPS 0xB0
#define ADS1256_DRATE_1000SPS 0xA1
#define ADS1256_DRATE_500SPS 0x92
#define ADS1256_DRATE_100SPS 0x82
#define ADS1256_DRATE_60SPS 0x72
#define ADS1256_DRATE_50SPS 0x63
#define ADS1256_DRATE_30SPS 0x53
#define ADS1256_DRATE_25SPS 0x43
#define ADS1256_DRATE_15SPS 0x33
#define ADS1256_DRATE_10SPS 0x23
#define ADS1256_DRATE_5SPS 0x13
#define ADS1256_DRATE_2_5SPS 0x03

#define BufferON 0x02
#define BufferOFF 0x00

#define ACALON 0x04
#define ACALOFF 0x00

void AD_WRITE(uint8_t addr, uint8_t data);
void ADS1256_Init(uint8_t gain, uint8_t drate, uint8_t c);
void AD_RST(int a);
uint32_t AD_ReadData(void);

void SelectChannel(uint8_t c);
void Data_Print(void);
void Matlab_Print(void);
void Transmit_To_Python(void);

void AD_SYSCAL(void);
void AD_SELFCAL(void);
void AD_CAL_RegRead(void);
uint8_t AD_READ(uint8_t addr);

#endif /* _ADS1256_H_ */
