#include "main.h"
#ifdef __configTCS3472_SOURCE
#define TCS3472_I2C     __configTCS3472_ADDR
#else
#define TCS3472_I2C     (0x29)
#endif /*__configTCS3472_SOURCE*/

#define TCS34723_ID       0x4D
#define TCS34727_ID       0x4D
#define TCS34721_ID       0x44
#define TCS34725_ID       0x44

#define TCS3472_ENABLE     0x80
#define TCS3472_ATIME      0x81
#define TCS3472_WTIME      0x83
#define TCS3472_CONFIG     0x8D
#define TCS3472_CONTROL    0x8F
#define TCS3472_ID         0x92
#define TCS3472_STATUS     0x93
#define TCS3472_CLEAR      0x94
#define TCS3472_RED        0x96
#define TCS3472_GREEN      0x98
#define TCS3472_BLUE       0x9A

struct
{
    I2C_TypeDef* Source;
    uint8_t status;
    uint8_t IntegrationTime;
    uint8_t Gain;
    uint8_t WaitTime;
    uint8_t RawData[8];
    float RGB[4];
    uint16_t ColorTemperature;
    uint16_t Illuminance;
    bool IsInterrupt;
    uint8_t color;
}TCS3472;

bool TCS3472_Init(void);

bool TCS3472_SetProperties(uint8_t Gain, uint8_t IntegrationTime, uint8_t WaitTime);

bool TCS3472_SetGain(uint8_t Gain);

bool TCS3472_SetIntegrationTime(uint8_t IntegrationTime);

bool TCS3472_SetWaitTime(uint8_t WaitTime);

bool TCS3472_Connect(void);

bool TCS3472_CalculateLux(void);

bool TCS3472_CalculateColorTemperatureKelvin(void);

bool TCS3472_GetRGB(void);

bool TCS3472_GetRawData(void);
