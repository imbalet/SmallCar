/*!
    *   --------------------------------------------------------------------------
    *                       ///RCR Maximum Configuration Kit\\
    *   --------------------------------------------------------------------------
    *   @file MaxKit.h
    *   @note [RCR] Setup pins, interfaces
    *   @author RCR group developers - Caska
    *   @date   16/08/2022 - last update
    *
*/
#pragma once

#include "FilConfig.h"

/*!
*   @note [RCR] This settings transport to FIL Driver
*/

#define __configUSE_RCC                 (1)
#define __configUSE_GPIO                (1)
#define __configUSE_TIM                 (0)
#define __configUSE_USART               (0)
#define __configUSE_DMA                 (0)
#define __configUSE_I2C                 (0)
#define __configUSE_ADC                 (0)
#define __configUSE_EXTI                (0)
#define __configUSE_RTC                 (0)
#define __configUSE_FREERTOS            (0)

#define __configCALC_RCC                (0)
#define __configCALC_TIM                (0)
#define __configCALC_USART              (0)
#define __configCALC_Regulators         (0)
#define __configCALC_Matrix             (0)
#define __config_SysTick_Counter        (0)

/*!
*   @list Timer 1 parameters
*/
#define __config_TIM1_PSC               (0)
#define __config_TIM1_ARR               (0)
#define __config_TIM1_CH1               (0)
#define __config_TIM1_CH2               (0)
#define __config_TIM1_CH3               (0)
#define __config_TIM1_CH4               (0)

/*!
*   @list Timer 2 parameters
*/
#define __config_TIM2_PSC               (0)
#define __config_TIM2_ARR               (0)
#define __config_TIM2_CH1               (0)
#define __config_TIM2_CH2               (0)
#define __config_TIM2_CH3               (0)
#define __config_TIM2_CH4               (0)

/*!
*   @list Timer 3 parameters
*/
#define __config_TIM3_PSC               (0)
#define __config_TIM3_ARR               (0)
#define __config_TIM3_CH1               (0)
#define __config_TIM3_CH2               (0)
#define __config_TIM3_CH3               (0)
#define __config_TIM3_CH4               (0)

/*!
*   @list Timer 4 parameters
*/
#define __config_TIM4_PSC               (0)
#define __config_TIM4_ARR               (0)
#define __config_TIM4_CH1               (0)
#define __config_TIM4_CH2               (0)
#define __config_TIM4_CH3               (0)
#define __config_TIM4_CH4               (0)

/*!
*   @list Timer 5 parameters
*/
#define __config_TIM5_PSC               (0)
#define __config_TIM5_ARR               (0)
#define __config_TIM5_CH1               (0)
#define __config_TIM5_CH2               (0)
#define __config_TIM5_CH3               (0)
#define __config_TIM5_CH4               (0)

/*!
*   @list Timer 6 parameters
*/
#define __config_TIM6_PSC               (0)
#define __config_TIM6_ARR               (0)

/*!
*   @list Timer 7 parameters
*/
#define __config_TIM7_PSC               (0)
#define __config_TIM7_ARR               (0)

/*!
*   @list Timer 8 parameters
*/
#define __config_TIM8_PSC               (0)
#define __config_TIM8_ARR               (0)
#define __config_TIM8_CH1               (0)
#define __config_TIM8_CH2               (0)
#define __config_TIM8_CH3               (0)
#define __config_TIM8_CH4               (0)

/*!
*   @list Timer 9 parameters
*/
#define __config_TIM9_PSC               (0)
#define __config_TIM9_ARR               (0)
#define __config_TIM9_CH1               (0)
#define __config_TIM9_CH2               (0)

/*!
*   @list Timer 10 parameters
*/
#define __config_TIM10_PSC               (0)
#define __config_TIM10_ARR               (0)
#define __config_TIM10_CH1               (0)

/*!
*   @list Timer 11 parameters
*/
#define __config_TIM11_PSC               (0)
#define __config_TIM11_ARR               (0)
#define __config_TIM11_CH1               (0)

#define __config_TIM12_PSC               (0)
#define __config_TIM12_ARR               (0)
#define __config_TIM12_CH1               (0)
#define __config_TIM12_CH2               (0)
#define __config_TIM12_CH3               (0)
#define __config_TIM12_CH4               (0)

#define __config_TIM13_PSC               (0)
#define __config_TIM13_ARR               (0)
#define __config_TIM13_CH1               (0)
#define __config_TIM13_CH2               (0)
#define __config_TIM13_CH3               (0)
#define __config_TIM13_CH4               (0)

#define __config_TIM14_PSC               (0)
#define __config_TIM14_ARR               (0)
#define __config_TIM14_CH1               (0)
#define __config_TIM14_CH2               (0)
#define __config_TIM14_CH3               (0)
#define __config_TIM14_CH4               (0)

#define MAX_PWM                         (0)
#define MAX_PWM_SERVO                   (0)

#define __config_Regulator_ON           (0)
#define __config_Regulator_Source       (0)
#define __config_Regulator_FREQ         (0)
#define __config_Regulator_P_K          (0.0)
#define __config_Regulator_I_K          (0.0)
#define __config_Regulator_D_K          (0.0)
#define __config_MAX_SUM_ERROR          (0.0)
#define __config_OUTPUT_END             (0.0)
#define __config_Regulator_ERROR_END    (0.0)
#define __config_MAX_OUTPUT             (0.0)
#define __config_MIN_OUTPUT             (0.0)


#define REDUCTION_ENGINE                (0)
#define REDUCTION_DIFF                  (0)
#define REDUCTION_SUM                   (REDUCTION_ENGINE + REDUCTION_DIFF)
#define R_WHEEL                         (0.0)
#define WHEEL_LENGTH                    (PI2 * R_WHEEL)
#define DISKETS_ON_ROTATE               (0.0)
#define COMPENSATE_VALUE                (1.0)
#define DISK_TO_REAL                    ((float)(WHEEL_LENGTH / DISKETS_ON_ROTATE * COMPENSATE_VALUE))
#define TIME                            ((float)(1.0 / __config_Regulator_FREQ))
#define PI2                             (6.28314)

#define __config_USART1_Baudrate        (0)
#define __config_USART6_Baudrate        (0)

#define __configUSE_ModBus              (0)
#define __configMODBUS_Type             (0)
#if(__configUSE_ModBus == 1)
    #include "ModBus_conf.h"
    #include "ModBus.h"
#endif /*__configUSE_ModBus*/

#define __configADC_Mode                (0)
#define __configCONVERT_Volts           (0)
#define __configUSE_Battery_Charging    (0)
#define __configUSE_Temperature_Sensor  (0)

#define __configUSE_SENSOR_1            (-1)
#define __configUSE_SENSOR_2            (-1)
#define __configUSE_SENSOR_3            (-1)
#define __configUSE_SENSOR_4            (-1)
#define __configUSE_SENSOR_5            (-1)
#define __configUSE_SENSOR_6            (-1)
#define __configUSE_SENSOR_7            (-1)
#define __configUSE_SENSOR_8            (-1)
#define __configUSE_SENSOR_9            (-1)
#define __configUSE_SENSOR_10           (-1)

#define __configADC_InterruptRequest    (0)
/*!
*   @info Supported divider ADC frequency
*       @note [RCR] ADC Freq = APB2 Clock (exmp. 84 MHz) / divider
*       @arg 0 - divided by 2
*       @arg 1 - divided by 4
*       @arg 2 - divided by 6
*       @arg 3 - divided by 8
*/
#define __configADC_Divider              (0)
/*!
*   @info Supported resolution ADC data
*       @arg 12[bit]
*       @arg 10[bit]
*       @arg 8[bit]
*       @arg 6[bit]
*/
#define __configADC_RESOLUTION          (0)
/*!
*   @info Supported cycles mode ADC
*       @arg 480[cycles]
*       @arg 144[cycles]
*       @arg 112[cycles]
*       @arg 84[cycles]
*       @arg 56[cycles]
*       @arg 28[cycles]
*       @arg 15[cycles]
*       @arg 3[cycles]
*/
#define __configADC_CYCLES              (0)

#define __configCALC_I2C_SCANNING       (0)
#define __configI2C_FindListSize        (0)
#define __configI2C_TIMEOUT             (0)

#define __configI2C_LCD_SOURCE          (0)
#define __configUSE_LVGL                (0)
#define SSD1306_ADDR                    (0x78)

#define __configI2C_MPU_SOURCE          (0)
#define __configMPU_USE_Calibration     (0)
#define __configMPU_Scale               (0)
#define __configIS_AD0                  (0)
#define MPU9250_ADDR                    (__configIS_AD0 == 1) ? (0x69)  : (0x68)

/*!
*   @note [RCR] RTC configuration
*/
#define __configRTC_YEAR             (22)
#define __configRTC_MONTHS           (8)
#define __configRTC_DATE             (30)

#define __configRTC_HOURS            (9)
#define __configRTC_MINUTES          (30)
#define __configRTC_SECONDS          (0)
/*!
*   RTC Alarm A
*/
#define __configUSE_ALARM_A          (0)
#define __configRTC_ALARM_A_DATE     (0)
#define __configRTC_ALARM_A_HOURS    (0)
#define __configRTC_ALARM_A_MINUTES  (0)
#define __configRTC_ALARM_A_SECONDS  (0)
/*!
*   RTC Alarm B
*/
#define __configUSE_ALARM_B          (0)
#define __configRTC_ALARM_B_DATE     (0)
#define __configRTC_ALARM_B_HOURS    (0)
#define __configRTC_ALARM_B_MINUTES  (0)
#define __configRTC_ALARM_B_SECONDS  (0)
