    /*!
    *   --------------------------------------------------------------------------
    *                       ///MPU9250 Header file\\\
    *   --------------------------------------------------------------------------
    *   @author RCR group developers
    *   @date 07/09/2022 - last update version MPU
    *
    *       @note [MPU] MPU Header file.
    */
#pragma once
#include "FilConfig.h"

#if(EXTERNAL_MPU9250 == 1)
#include <math.h>
#include "stdbool.h"

/*!
*   @note [MPU] MPU9250 Registry
*/
#define MPU9250_ADDR        (0x68)   // Gyro Accelerometer
#define MPU9250_ADDR_AD0    (0x69)

#define MPUSELF_TEST_X_GYRO    0x00
#define MPUSELF_TEST_Y_GYRO    0x01
#define MPUSELF_TEST_Z_GYRO    0x02
#define MPUSELF_TEST_X_ACCEL   0x0D
#define MPUSELF_TEST_Y_ACCEL   0x0E
#define MPUSELF_TEST_Z_ACCEL   0x0F
#define XG_OFFSET_H            0x13
#define XG_OFFSET_L            0x14
#define YG_OFFSET_H            0x15
#define YG_OFFSET_L            0x16
#define ZG_OFFSET_H            0x17
#define ZG_OFFSET_L            0x18
#define MPUCONFIG              0x1A
#define MPUGYRO_CONFIG         0x1B
#define MPUACCEL_CONFIG        0x1C
#define MPUI2C_MST_CTRL        0x24
#define MPUI2C_SLV0_ADDR       0x25
#define MPUI2C_SLV0_REG        0x26
#define MPUI2C_SLV0_CTRL       0x27
#define MPUINT_PIN_CFG         0x37
#define MPUINT_ENABLE          0x38
#define MPUINT_STATUS          0x3A
#define MPUACCEL_XOUT_H        0x3B
#define MPUEXT_SENS_DATA_00    0x49
#define MPUI2C_SLV0_DO         0x63
#define MPUWHO_AM_I_6050       0x68
#define MPUUSER_CTRL           0x6A
#define MPUPWR_MGMT_1          0x6B
#define MPUPWR_MGMT_2          0x6C
#define MPUWHO_AM_I_9250       0x71
#define MPUWHO_AM_I            0x75

/*!
*   @note [MPU] AK8963 Registry
*/
#define AK8963_ADDR            0x0C    //Slave address of magnetometer

#define AK8963_ST1             0x02
#define AK8963_HXL             0x03
#define AK8963_ST2             0x09
#define AK8963_CNTL1           0x0A
#define AK8963_CNTL2           0x0B
#define AK8963_ASAX            0x10
#define AK8963_WHO_AM_I        0x00
#define AK8963_ID              0x48

struct {
    char MPUstatus;
    char AK8963status;
    float Altitude[3];
    float Compass[3];
    float AnglePosition[3];
    float Accelerometer[3];
    float Gyroscope[3];
    float Magnetometer[3];
    float GyroCal[3];
    float aScaleFactor;
    float gScaleFactor;
    float MagnetometerScaleFactor[3];
    int16_t Raw_Data[10];
    uint8_t Bus[21];
}MPU9250;

/*!
*   @list Parameters for configuration range and resolution
*/
enum accelerometerFullScaleRange
{
    AFSR_2G,
    AFSR_4G,
    AFSR_8G,
    AFSR_16G
};

enum gyroscopeFullScaleRange
{
    GFSR_250DPS,
    GFSR_500DPS,
    GFSR_1000DPS,
    GFSR_2000DPS
};

enum magnetometerResolutionRange
{
    MRES_14BIT = 0,
    MRES_16BIT = 1
};

/*!
*   @brief This function is reconnect to device MPUXX50
*       @note [MPU] if this function on too long then have problem on bus I2C and reconnect_it is much
*/
bool MPU_Connect(I2C_TypeDef* I2Cx, bool IsWrite);

void MPU_ScaleCalibration(I2C_TypeDef* I2Cx, uint8_t aScale, uint8_t gScale);
void MPU_GyroscopeCalibration(uint16_t CalPoints);
/*!
*   @brief This function is writing new value to device MPUXX50
*       @note [MPU] if end value if false then have problem with bus or device
*/
uint8_t MPU_WriteRegistry(I2C_TypeDef* I2Cx, uint8_t Register, uint8_t Value);

uint8_t MPU_ReadRegistry(I2C_TypeDef* I2Cx, uint8_t Register);

void MPU_ReadRawData(void);
void AK8963_ReadRawData(void);
void MPU_parseData(void);
/*!
*   @brief Main Init Function for MPUxx50
*       @note [RCR] MPU9250 currently used
*/
#define RAD2DEG     57.2957795131
void AK8963_Init(void);
uint8_t MPU_Init(void);

#endif/*EXTERNAL_MPU9250*/
