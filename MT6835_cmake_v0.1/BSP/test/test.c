#include "test.h"
#include <stdint.h>
#include <stdio.h>
#include "ads1256.h"
#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_spi.h"

ADS1256_t ads1256;

void test_main(void)
{
    printf("testing...\n");
    // test_led();
    test_init();
}
void test_led(void)
{
    printf("[OK] start ads1256\n");
    ADS1256_Init(ADS1256_GAIN_1, ADS1256_DRATE_100SPS, 3);
    HAL_Delay(1000);
    while (1)
    {
        Data_Print();
        HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
        HAL_Delay(500);
    }
}
void test_init(void)
{
    // ads1256.drate = ADS1256_DRATE_1000SPS;
    // ads1256.gain = ADS1256_GAIN_2;
    // ads1256.channel = 1;
    ads1256.configChannel = 1;
    ads1256.configGain = ADS1256_GAIN_1;
    ads1256.configDrate = ADS1256_DRATE_2_5SPS;

    // ADS1256_Init(ADS1256_GAIN_1, ADS1256_DRATE_1000SPS, 1);
    ADS1256_ConfigInit(&ads1256);
    // ADS1256_SYSGCAL();
    // ADS1256_SELFCAL();

    // ADS1256_RST_LOW();
    // AD_RST(1);
    // HAL_Delay(10);
    // AD_RST(1);
    // ADS1256_RST_HIGH();
    // uint8_t cmd = ADS1256_CMD_REST;
    // HAL_SPI_Transmit(&ads1256_spi, &cmd, 1, 1000);
    HAL_Delay(1000);
    while (1)
    {
        // SelectChannel(1);

        // 1.
        // Data_Print();
        // HAL_Delay(1000);
        // 2.
        //  ADS1256_getInfo();
        //  uint8_t addr = ADS1256_STATUS;
        //  uint8_t data;
        //  ADS1256_read(addr, &data);
        //  printf("data = %x\n", data);
        //  HAL_Delay(1000);
        // 3.
        // ADS1256_getVoltage(&ads1256);
        // printf("v = %f\n", ads1256.voltage);
        // 4.
        // ADS1256_getOFC();
        // HAL_Delay(1000);
        // 5.
        // ADS1256_OFC(&ads1256);
        // HAL_Delay(1000);
        // 6.
        // printf("before\n");
        // ADS1256_getFSC(&ads1256);
        // ADS1256_SYSGCAL();

        printf("after\n");
        // ADS1256_getFSC(&ads1256);
        // ADS1256_OFC(&ads1256);
        ADS1256_printVoltage(&ads1256);
        HAL_Delay(1000);
        // 7.
        // ADS1256_getVoltage_with_cal(&ads1256);
        // HAL_Delay(1000);
    }
}