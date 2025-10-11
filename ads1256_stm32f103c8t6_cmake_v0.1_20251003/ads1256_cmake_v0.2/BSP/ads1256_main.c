#include "ads1256_main.h"

void ads1256_main(void)
{
    ADS1256_t ads1256;

    // config for ads1256
    ads1256.configChannel = 1;
    ads1256.configGain = ADS1256_GAIN_1;
    ads1256.configDrate = ADS1256_DRATE_2_5SPS;

    // 1.
    //  ADS1256_Init(ADS1256_GAIN_1, ADS1256_DRATE_1000SPS, 1);
    // 2.
    ADS1256_ConfigInit(&ads1256);
    HAL_Delay(1000);
    ADS1256_getInfo();
    while (1)
    {
        // ADS1256_getVoltage(&ads1256);
        ADS1256_printVoltage(&ads1256);
        // printf("v = %f\n", ads1256.)
    }
}