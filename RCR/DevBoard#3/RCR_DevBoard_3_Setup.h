/*!
    *   --------------------------------------------------------------------------
    *                       ///RCR Main Board Configuration file #3\\
    *   --------------------------------------------------------------------------
    *   @file RCR_DevBoard_3_Setup.h
    *   @note [RCR] Setup pins, interfaces for Development Board #3
    *   @author RCR group developers - Caska, Evgeny Garanin
    *   @date   02/08/2022 - last update
    *
*/
#pragma once

#include "FilConfig.h"
#include "RCR_DevBoard_3.h"

#if defined(STM32F401xx)
/*!
*   @note [RCR] This settings transport to FIL Driver
*/
#define __configUSE_RCC                   1
#define __configUSE_GPIO                  1
#define __configUSE_TIM                   1
#define __configUSE_USART                 1
#define __configUSE_DMA                   1
#define __configUSE_I2C                   0
#define __configUSE_ADC                   1
#define __configUSE_EXTI                  1
#define __configUSE_RTC                   0

#define __configCALC_RCC                  1
#define __configCALC_TIM                  1
#define __configCALC_USART                1
//-----------------------------------------------------------------//
//-----------------------External includes-------------------------//
//-----------------------------------------------------------------//
#define __configEXT_FREERTOS              0
#define __configEXT_REGULATOR             0
#define __configEXT_MATRIX                0
#define __configEXT_KINEMATICS            0
#define __configEXT_SSD1306               0
#define __configEXT_MPU9250               0

/*!
*   @note [RCR] ModBus Slave Configuration
*/
#define __configEXT_ModBus                1
#define __configMODBUS_SlaveAddress       0x01
#define __configMODBUS_Source             USART1
#define __configMODBUS_InterruptSource    USART1_IRQn
#define __configMODBUS_Handler            USART1_IRQHandler
#define __configMODBUS_MINIMAL_OFFSET     7
#define __configMODBUS_MAXREGISTERS       5
//-----------------------------------------------------------------//
/*!
*   @note [RCR] Configuration Development Board #3
*/
//-----------------------------------------------------------------//
#define __config_SysTick_Counter        (84000)     // 1Hz

/*!
*   @note [RCR] Timers configuration
*/

#define __config_TIM1_PSC        (84 - 1)
#define __config_TIM1_ARR        (200)
#define __config_TIM1_CH1        1
#define __config_TIM1_CH2        1
#define __config_TIM1_CH3        0
#define __config_TIM1_CH4        0

#define __config_TIM5_PSC        (420 - 1)
#define __config_TIM5_ARR        (4000)
#define __config_TIM5_CH1        1
#define __config_TIM5_CH2        0
#define __config_TIM5_CH3        0
#define __config_TIM5_CH4        0

#define MAX_PWM         __config_TIM1_ARR
#define MAX_PWM_SERVO   __config_TIM5_ARR

/*!
*   @note [RCR] Regulator configuration { Car's engine }
*/

#define __config_RegulatorList          (1)
#define __config_RegulatorListP         (0)
#define __config_RegulatorListPI        (0)
#define __config_RegulatorListPID       (1)

/*
#define __config_Regulator_ON           (1)
#define __config_Regulator_Source       (TIM4)
#define __config_Regulator_FREQ         (100)
#define __config_Regulator_P_K          (5.0)
#define __config_Regulator_I_K          (1.5)
#define __config_Regulator_D_K          (0.5)
#define __config_MAX_SUM_ERROR          (6.0)
#define __config_OUTPUT_END             (50.0)
#define __config_Regulator_ERROR_END    (0.0)
#define __config_MAX_OUTPUT             (1.0)
#define __config_MIN_OUTPUT             (0.08)

#define PI2                             (6.28314)
#define REDUCTION_ENGINE                (150)
#define REDUCTION_DIFF                  (1.2)
#define REDUCTION_SUM                   (REDUCTION_ENGINE + REDUCTION_DIFF)
#define R_WHEEL                         (0.048)
#define WHEEL_LENGTH                    (PI2 * R_WHEEL)
#define DISKETS_ON_ROTATE               (41000.0)
#define COMPENSATE_VALUE                (0.9)
#define DISK_TO_REAL                    ((float)(WHEEL_LENGTH / DISKETS_ON_ROTATE * COMPENSATE_VALUE))
#define TIME                            ((float)(1.0 / __config_Regulator_FREQ))
*/

/*!
*   @note [RCR] UART/USART configuration
*/
#define __config_USART1_Baudrate    (9600)
#define __config_USART6_Baudrate    (115200)

/*!
*   @note [RCR] ADC configuration
*/
#define __configADCCONVERT_Volts        (0)
#define __configUSE_Battery_Charging    (1)
#define __configUSE_Temperature_Sensor  (1)
#define __configADC_InterruptRequest    (0)
#define __configADC_DMARequest          (1)
/*!
*   @info Supported divider ADC frequency
*       @note [RCR] ADC Freq = APB2 Clock (exmp. 84 MHz) / divider
*       @arg 0 - divided by 2
*       @arg 1 - divided by 4
*       @arg 2 - divided by 6
*       @arg 3 - divided by 8
*/
#define __configADC_Divider              (3)
/*!
*   @info Supported resolution ADC data
*       @arg 12[bit]
*       @arg 10[bit]
*       @arg 8[bit]
*       @arg 6[bit]
*/
#define __configADC_RESOLUTION          (12)        // 12-bit resolution
/*!
*   @info Supported cycles mode ADC
*       @arg ADC_480_CYCLES - 480[cycles]
*       @arg ADC_144_CYCLES - 144[cycles]
*       @arg ADC_112_CYCLES - 112[cycles]
*       @arg ADC_84_CYCLES  -  84[cycles]
*       @arg ADC_56_CYCLES  -  56[cycles]
*       @arg ADC_28_CYCLES  -  28[cycles]
*       @arg ADC_15_CYCLES  -  15[cycles]
*       @arg ADC_3_CYCLES   -   3[cycles]
*/
#define __configADC_CYCLES              (ADC_480_CYCLES)

/*!
*   @info Supported divider for ADC bus
*   @note [RCR] ADC Freq = APB2(example 84 MHz) / __configADC_DIVIDER
*       @arg 0 - divided by 2
*       @arg 1 - divided by 4
*       @arg 2 - divided by 6
*       @arg 3 - divided by 8
*/
#define __configADC_DIVIDER             (3)
/*!
*   @note [RCR] IIC(I2C) configuration
*/
// General IIC Configuration
#define __configCALC_I2C_SCANNING       (1)

#define __configI2C_FindListSize        (3)

#define __configI2C_TIMEOUT             (5000)

// configuration LCD
#define __configI2C_LCD_SOURCE          (I2C1)
#define __configUSE_LVGL                (0)

// configuration Gyro
#define __configEXTMPU_SOURCE           (I2C1)
#define __configEXTMPU_Calibration      (1)
#define __configEXTMPU_aScale           AFSR_4G
#define __configEXTMPU_gScale           GFSR_500DPS
#define __configEXTMPU_mScale           MRES_16BIT
#define __configEXTMPU_mResolution

//-----------------------------------------------------------------//
/*!
*   @brief General Initialization. This sector is custom adding by author.
*          You can modify and use some new functions that you need.
*/
#define Board_Config                           {\
    SetPWR;                                     \
    SetGPIOA;                                   \
    SetGPIOB;                                   \
    SetGPIOC;                                   \
    SetTIM1;                                    \
    SetTIM3;                                    \
    SetTIM4;                                    \
    SetTIM5;                                    \
    SetDMA2;                                    \
    SetADC1;                                    \
    SetUSART1;                                  \
    SetUSART6;                                  \
    SetSYSCFG;                                  \
    InitPeriph;                                 \
    InitTimers;                                 \
    InitInterrupts;                             \
    USARTBothConfigure(USART1,115200,1,0);      \
    SetI2C1;                                    }

/*!
*   @brief Initialization pins
*/
#define InitPeriph {\
    GPIOConfPin(BTN1_DIR_PIN, GENERAL, PUSH_PULL, FAST_S, NO_PULL_UP);\
    GPIOConfPin(MULPLXA_PIN,  GENERAL, PUSH_PULL, FAST_S, PULL_DOWN);\
    GPIOConfPin(MULPLXB_PIN,  GENERAL, PUSH_PULL, FAST_S, PULL_DOWN);\
    GPIOConfPin(MULPLXC_PIN,  GENERAL, PUSH_PULL, FAST_S, PULL_DOWN);\
    GPIOConfPin(INT_PIN,  GENERAL, PUSH_PULL, FAST_S, PULL_DOWN);\
    GPIOConfPin(LED1_PIN,  GENERAL, PUSH_PULL, FAST_S, NO_PULL_UP);\
    GPIOConfPin(LED2_PIN,  GENERAL, PUSH_PULL, FAST_S, NO_PULL_UP);\
    GPIOConfPin(ADC_TOP, ANALOG, PUSH_PULL, FAST_S, NO_PULL_UP);\
    GPIOConfPin(POT_PIN, ANALOG, PUSH_PULL, FAST_S, PULL_DOWN);\
    GPIOConfPin(EXTI1_PIN, INPUT, PUSH_PULL, FAST_S, PULL_DOWN);\
    GPIOConfPin(EXTI2_PIN, INPUT, PUSH_PULL, FAST_S, PULL_DOWN);\
    GPIOConfPin(EXTI3_PIN, INPUT, PUSH_PULL, FAST_S, PULL_DOWN);\
    GPIOConfPin(EXTI4_PIN, INPUT, PUSH_PULL, FAST_S, PULL_DOWN);\
    GPIOConfPin(EXTI5_PIN, INPUT, PUSH_PULL, FAST_S, PULL_DOWN);\
    GPIOConfPin(TX1_PIN, ALTERNATE, PUSH_PULL, FAST_S, PULL_UP);\
    GPIOConfPin(RX1_PIN, ALTERNATE, PUSH_PULL, FAST_S, PULL_UP);\
    GPIOConfAF(TX1_PIN,AF7);\
    GPIOConfAF(RX1_PIN,AF7);\
    GPIOConfPin(BTN1_PWM_PIN, ALTERNATE, PUSH_PULL, FAST_S, NO_PULL_UP);\
    GPIOConfAF(BTN1_PWM_PIN, AF1);\
    GPIOConfPin(BTN2_PWM_PIN, ALTERNATE, PUSH_PULL, FAST_S, NO_PULL_UP);\
    GPIOConfAF(BTN2_PWM_PIN, AF1);\
    GPIOConfPin(ENCODER1A_PIN, ALTERNATE, PUSH_PULL, LOW_S, PULL_UP);\
    GPIOConfAF(ENCODER1A_PIN, AF2);\
    GPIOConfPin(ENCODER1B_PIN, ALTERNATE, PUSH_PULL, LOW_S, PULL_UP);\
    GPIOConfAF(ENCODER1B_PIN, AF2);\
    GPIOConfPin(ENCODER2A_PIN, ALTERNATE, PUSH_PULL, LOW_S, PULL_UP);\
    GPIOConfAF(ENCODER2A_PIN, AF2);\
    GPIOConfPin(ENCODER2B_PIN, ALTERNATE, PUSH_PULL, LOW_S, PULL_UP);\
    GPIOConfAF(ENCODER2B_PIN, AF2);\
    GPIOConfPin(I2C_SDA_PIN, ALTERNATE, OPEN_DRAIN, FAST_S, NO_PULL_UP);\
    GPIOConfAF(I2C_SDA_PIN, AF4);\
    GPIOConfPin(I2C_SCL_PIN, ALTERNATE, OPEN_DRAIN, FAST_S, NO_PULL_UP);\
    GPIOConfAF(I2C_SCL_PIN, AF4);}

/*!
*   @brief Initialization timers
*       @arg TIM1 - Wheels engine
*       @arg TIM5 - Servo management
*       @arg TIM4 - PID Calculating (Interrupt)
*           @attention check interrupts file for TIM
*               @file TIM.c
*       @arg TIM3 - Encoder monitoring
*/
#define InitTimers                                                                                                                      {\
    TimPWMConfigure(TIM1,__config_TIM1_PSC,__config_TIM1_ARR,__config_TIM1_CH1,__config_TIM1_CH2,__config_TIM1_CH3,__config_TIM1_CH4);   \
    TimPWMConfigure(TIM5,__config_TIM5_PSC,__config_TIM5_ARR,__config_TIM5_CH1,__config_TIM5_CH2,__config_TIM5_CH3,__config_TIM5_CH4);   \
    TimEncoderConfigure(TIM3);                                                                                                           \
    TimPIDConfigureAutomatic(TIM4,100);                                                                                                  }
/*!
*   @brief Initialization interrupts
*/
#define InitInterrupts {\
    NVIC_EnableIRQ(TIM4_IRQn);}

/*!
*   @brief Initialization uart/usart
*/
/*
#define InitUSART {\
    USARTBothConfigure(USART1,__config_USART1_Baudrate, 0, 0); \
    USARTTransmitterConfigure(USART6, __config_USART6_Baudrate, 0);} */

/*!
*   @brief Initialization Regulators
*/
/*
#define InitRegulators                                         {\
    Settings[0].reg_on = __config_Regulator_ON;                 \
    Settings[0].p_k = __config_Regulator_P_K;                   \
    Settings[0].i_k = __config_Regulator_I_K;                   \
    Settings[0].d_k = __config_Regulator_D_K;                   \
    Settings[0].max_sum_error = __config_MAX_SUM_ERROR;         \
    Settings[0].reg_output_end = __config_OUTPUT_END;           \
    Settings[0].reg_error_end = __config_Regulator_ERROR_END;   \
    Settings[0].min_output = __config_MIN_OUTPUT;               \
    Settings[0].max_output = __config_MAX_OUTPUT;               } */

#endif /*STM32F401xx*/
