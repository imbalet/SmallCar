    /*!
    *   --------------------------------------------------------------------------
    *                       ///MPU9250 Source file\\\
    *   --------------------------------------------------------------------------
    *   @author RCR group developers
    *   @date 07/09/2022 - last update version MPU
    *
    *       @note [MPU] MPU Source file.
    */
#include "mpu9250.h"

#if(EXTERNAL_MPU9250 == 1)

#define MPU_Reconnect_it    (100)
static uint32_t MPU_Timeout;

static const uint8_t BYPASS_EN = 0x2;
static const uint8_t CLOCK_SEL_PLL = 0x1;
static const uint8_t I2C_MASTER_DS = 0x00;

static const uint8_t AK8963_PWR_DOWN = 0x00;
static const uint8_t AK8963_RESET = 0x01;
static const uint8_t AK8963_FUSE_ROM = 0x0F;
static const uint8_t AK8963_HOFL_MASK = 0x8;
/*!
*   @brief Initialization MPU9250
*       @arg status - errors with connection to device
*       @value 1 - AK8963 init end
*       @value 2 - Calibration (if enable setting)
*       @value 3 - Verification complete
*       @value 4 - MPU_Connect done
*       @value 5 - begin connection
*/
uint8_t MPU_Init(void)
{
    // restore bad connection
    if(I2CBusBusyEvent(__configEXTMPU_SOURCE))
    {
        I2C_RestoreConnection(__configEXTMPU_SOURCE);
        I2CSimpleConfigure(__configEXTMPU_SOURCE,I2C_Fast);
    }
    bool connect = false;

    connect = MPU_Connect(__configEXTMPU_SOURCE,true);
    if(!connect) return 1;

    uint8_t Data;
    // MPU9250 check WHO_AM_I register
    Data = I2C_MemoryReadSingle(__configEXTMPU_SOURCE,MPU9250_ADDR,MPUWHO_AM_I);
    delay_ms(5);
    if(Data != MPUWHO_AM_I_9250) return 1;

    // Set clock source PLL 0x1
    Data = I2C_MemoryWriteSingle(__configEXTMPU_SOURCE,MPU9250_ADDR,MPUPWR_MGMT_1,CLOCK_SEL_PLL);
    delay_ms(5);
    if(Data != CLOCK_SEL_PLL) return 1;

    Data = I2C_MemoryWriteSingle(__configEXTMPU_SOURCE,MPU9250_ADDR,MPUUSER_CTRL,I2C_MASTER_DS);
    delay_ms(5);
    if(Data != I2C_MASTER_DS) return 1;

    // Enable bypass for AK8963
    Data = I2C_MemoryWriteSingle(__configEXTMPU_SOURCE,MPU9250_ADDR,MPUINT_PIN_CFG,BYPASS_EN);
    delay_ms(5);

    // AK8963 check WHO_AM_I register
    Data = I2C_MemoryReadSingle(__configEXTMPU_SOURCE,AK8963_ADDR,AK8963_WHO_AM_I);
    if(Data != AK8963_ID) return 1;
    delay_ms(5);
#if(CALC_I2C_SCANNING == 1)
    MPU9250.MPUstatus = 3;
#endif/*CALC_I2C_SCANNING*/
#if(__configEXTMPU_Calibration == 1)
    uint8_t accelerometerFullScaleRange = AFSR_4G;
    uint8_t gyroscopeFullScaleRange  = GFSR_500DPS;

    // calibration parameters for gyro and accel
    MPU_ScaleCalibration(__configEXTMPU_SOURCE,accelerometerFullScaleRange,gyroscopeFullScaleRange);
    delay_ms(5);

#if(CALC_I2C_SCANNING == 1)
    MPU9250.MPUstatus = 2;
#endif/*CALC_I2C_SCANNING*/

    AK8963_Init();
#endif /*__configEXTMPU_Calibration*/
#if(CALC_I2C_SCANNING == 1)
    MPU9250.MPUstatus = 1;
#endif/*CALC_I2C_SCANNING*/

return 0;
}

/*!
*   @brief Initialization Magnetometer AK8963
*       @arg status - errors with connection to device
*       @value 1 - Start success, no errors
*       @value 2 - power resetting done
*       @value 3 - Begin initialization
*/
void AK8963_Init(void)
{
#if(CALC_I2C_SCANNING == 1)
    MPU9250.AK8963status = 2;
#endif/*CALC_I2C_SCANNING*/
    __attribute__((unused)) uint8_t Data;

    // Power mode OFF
    Data = I2C_MemoryWriteSingle(__configEXTMPU_SOURCE,AK8963_ADDR,AK8963_CNTL1,AK8963_PWR_DOWN);
    delay_ms(100);
    if(Data != AK8963_PWR_DOWN) return;

    // Power mode FUSE ROM
    Data = I2C_MemoryWriteSingle(__configEXTMPU_SOURCE,AK8963_ADDR,AK8963_CNTL1,AK8963_FUSE_ROM);
    delay_ms(100);
    if(Data != AK8963_FUSE_ROM) return;

    uint8_t Buf[3];
    (void)I2C_MemoryReadMultiple(__configEXTMPU_SOURCE,AK8963_ADDR,AK8963_ASAX, Buf, 3);
    MPU9250.MagnetometerScaleFactor[0] = (float)((Buf[0] - 128) /  256.0) + 1.0;
    MPU9250.MagnetometerScaleFactor[1] = (float)((Buf[1] - 128) /  256.0) + 1.0;
    MPU9250.MagnetometerScaleFactor[2] = (float)((Buf[2] - 128) /  256.0) + 1.0;
    delay_ms(100);

#if(CALC_I2C_SCANNING == 1)
    MPU9250.AK8963status = 1;
#endif/*CALC_I2C_SCANNING*/

    // Power mode OFF
    Data = I2C_MemoryWriteSingle(__configEXTMPU_SOURCE,AK8963_ADDR,AK8963_CNTL2,AK8963_RESET);
    delay_ms(100);
    if(Data != AK8963_RESET);

    uint8_t magnetometerResolutionRange = __configEXTMPU_mScale;
    uint8_t AK8963_Mode = magnetometerResolutionRange << 4 | 0x6;

    // set Continuous measurement mode 1
    Data = I2C_MemoryWriteSingle(__configEXTMPU_SOURCE,AK8963_ADDR,AK8963_CNTL1,AK8963_Mode);
    delay_ms(100);
    if(Data != AK8963_Mode) return;

#if(CALC_I2C_SCANNING == 1)
    MPU9250.AK8963status = 0;
#endif/*CALC_I2C_SCANNING*/
}

void MPU_ScaleCalibration(I2C_TypeDef* I2Cx, uint8_t aScale, uint8_t gScale)
{
//--------------------Accelerometer Scale Configuration--------------------------//
    switch(aScale)
    {
        case AFSR_2G:
        MPU9250.aScaleFactor = 16384.0;
        (void)I2C_MemoryWriteSingle(I2Cx,MPU9250_ADDR,MPUACCEL_CONFIG,0x00);
        break;

        case AFSR_4G:
        MPU9250.aScaleFactor = 8192.0;
        (void)I2C_MemoryWriteSingle(I2Cx,MPU9250_ADDR,MPUACCEL_CONFIG,0x08);
        break;

        case AFSR_8G:
        MPU9250.aScaleFactor = 4096.0;
        (void)I2C_MemoryWriteSingle(I2Cx,MPU9250_ADDR,MPUACCEL_CONFIG,0x10);
        break;

        case AFSR_16G:
        MPU9250.aScaleFactor = 2048.0;
        (void)I2C_MemoryWriteSingle(I2Cx,MPU9250_ADDR,MPUACCEL_CONFIG,0x18);
        break;

        default:
        MPU9250.aScaleFactor = 8192.0;
        (void)I2C_MemoryWriteSingle(I2Cx,MPU9250_ADDR,MPUACCEL_CONFIG,0x08);
        break;
    }
//-------------------------------------------------------------------------------//
//--------------------Gyroscope Scale Configuration------------------------------//
    switch(gScale)
    {
        case GFSR_250DPS:
        MPU9250.gScaleFactor = 131.0;
        (void)I2C_MemoryWriteSingle(I2Cx,MPU9250_ADDR,MPUGYRO_CONFIG,0x00);
        break;

        case GFSR_500DPS:
        MPU9250.gScaleFactor = 65.5;
        (void)I2C_MemoryWriteSingle(I2Cx,MPU9250_ADDR,MPUGYRO_CONFIG,0x08);
        break;

        case GFSR_1000DPS:
        MPU9250.gScaleFactor = 32.8;
        (void)I2C_MemoryWriteSingle(I2Cx,MPU9250_ADDR,MPUGYRO_CONFIG,0x10);
        break;

        case GFSR_2000DPS:
        MPU9250.gScaleFactor = 16.4;
        (void)I2C_MemoryWriteSingle(I2Cx,MPU9250_ADDR,MPUGYRO_CONFIG,0x18);
        break;

        default:
        MPU9250.gScaleFactor = 65.5;
        (void)I2C_MemoryWriteSingle(I2Cx,MPU9250_ADDR,MPUGYRO_CONFIG,0x08);
        break;
    }
//-------------------------------------------------------------------------------//
}

void MPU_GyroscopeCalibration(uint16_t CalPoints)
{
    int32_t x = 0;
    int32_t y = 0;
    int32_t z = 0;

    if(CalPoints == 0) CalPoints = 1;

    for(int i = 0; i < CalPoints; i++)
    {
        MPU_ReadRawData();
        x += MPU9250.Raw_Data[4];
        y += MPU9250.Raw_Data[5];
        z += MPU9250.Raw_Data[6];
        delay_ms(12);
    }

    MPU9250.GyroCal[0] = ((float)x) / (float)CalPoints;
    MPU9250.GyroCal[1] = ((float)y) / (float)CalPoints;
    MPU9250.GyroCal[2] = ((float)z) / (float)CalPoints;
}

/*!
*   @brief Connect to MPU9250
*/
bool MPU_Connect(I2C_TypeDef* I2Cx, bool IsWrite)
{

    for(int i = 0; i < MPU_Reconnect_it; i++)
    {
        SetI2CPeriphDisable(I2Cx);
#if(CALC_I2C_SCANNING == 1)
        MPU9250.MPUstatus = 5;
#endif/*CALC_I2C_SCANNING*/

        I2C_ClearAllStats(I2Cx);

        SetI2CPeriphEnable(I2Cx);
        I2CStart(I2Cx);

        MPU_Timeout = __configI2C_TIMEOUT;
        while (!I2CStartBitEvent(I2Cx)) {
            if (--MPU_Timeout == 0x00)
            {
                break;
            }
        }
        if(!I2CStartBitEvent(I2Cx)) continue;


        if ((I2Cx->CR1 & I2C_CR1_ACK) == 0) SetI2CAsk(I2Cx);

        if(IsWrite) I2Cx->DR = (MPU9250_ADDR << 1) & ~I2C_OAR1_ADD0;
        else I2Cx->DR = (MPU9250_ADDR << 1) | I2C_OAR1_ADD0;

        MPU_Timeout = __configI2C_TIMEOUT;
        while(!I2CAddressSentEvent(I2Cx))
        {
            if(--MPU_Timeout == 0x00) {
                break;
            }
        }
        if(!(I2Cx->SR1 & I2C_SR1_ADDR)) continue;
#if(CALC_I2C_SCANNING == 1)
        MPU9250.MPUstatus = 4;
#endif/*CALC_I2C_SCANNING*/

        I2CStop(I2Cx);

        return true;
    }

return false;
}

void MPU_ReadRawData(void)
{
    uint8_t* MPU_data = MPU9250.Bus;

    uint16_t DataItems = I2C_MemoryReadMultiple(__configEXTMPU_SOURCE,MPU9250_ADDR,MPUACCEL_XOUT_H, (uint8_t *)MPU_data, 14);
    if(DataItems != 14) return;
    MPU9250.MPUstatus = 0;

    MPU9250.Raw_Data[0] = MPU9250.Bus[0] << 8 | MPU9250.Bus[1];     //ax
    MPU9250.Raw_Data[1] = MPU9250.Bus[2] << 8 | MPU9250.Bus[3];     //ay
    MPU9250.Raw_Data[2] = MPU9250.Bus[4] << 8 | MPU9250.Bus[5];     //az
    MPU9250.Raw_Data[3] = MPU9250.Bus[6] << 8 | MPU9250.Bus[7];     //temperature
    MPU9250.Raw_Data[4] = MPU9250.Bus[8] << 8 | MPU9250.Bus[9];     //gx
    MPU9250.Raw_Data[5] = MPU9250.Bus[10] << 8 | MPU9250.Bus[11];   //gy
    MPU9250.Raw_Data[6] = MPU9250.Bus[12] << 8 | MPU9250.Bus[13];   //gz


    MPU9250.Accelerometer[0] = MPU9250.Raw_Data[0] / MPU9250.aScaleFactor;
    MPU9250.Accelerometer[1] = MPU9250.Raw_Data[1] / MPU9250.aScaleFactor;
    MPU9250.Accelerometer[2] = MPU9250.Raw_Data[2] / MPU9250.aScaleFactor;

    MPU9250.Gyroscope[0] = (MPU9250.Raw_Data[4] - MPU9250.GyroCal[0]) / MPU9250.gScaleFactor;
    MPU9250.Gyroscope[1] = (MPU9250.Raw_Data[5] - MPU9250.GyroCal[1]) / MPU9250.gScaleFactor;
    MPU9250.Gyroscope[2] = (MPU9250.Raw_Data[6] - MPU9250.GyroCal[2]) / MPU9250.gScaleFactor;
}

void AK8963_ReadRawData(void)
{
    uint8_t DataItems = I2C_MemoryReadSingle(__configEXTMPU_SOURCE,AK8963_ADDR,AK8963_ST1);
    delay_ms(2);
    DataItems &= 0x1;
    if(DataItems == 0x00) return;

    uint8_t* Data = MPU9250.Bus + 14;
    DataItems = I2C_MemoryReadMultiple(__configEXTMPU_SOURCE,AK8963_ADDR,AK8963_HXL,Data,7);
    if(DataItems != 7) return;
    if((MPU9250.Bus[20] & AK8963_HOFL_MASK)) return;

    MPU9250.Raw_Data[7] = (((int16_t)MPU9250.Bus[15] << 8) | MPU9250.Bus[14]);
    MPU9250.Raw_Data[8] = (((int16_t)MPU9250.Bus[17] << 8) | MPU9250.Bus[16]);
    MPU9250.Raw_Data[9] = (((int16_t)MPU9250.Bus[19] << 8) | MPU9250.Bus[18]);

    MPU9250.Compass[0] = ((float)(MPU9250.Raw_Data[7])) * MPU9250.MagnetometerScaleFactor[0] * 0.1499;
    MPU9250.Compass[1] = ((float)(MPU9250.Raw_Data[8])) * MPU9250.MagnetometerScaleFactor[1] * 0.1499;
    MPU9250.Compass[2] = ((float)(MPU9250.Raw_Data[9])) * MPU9250.MagnetometerScaleFactor[2] * 0.1499;

    delay_ms(10);
}
#endif /*EXTERNAL_MPU9250*/
