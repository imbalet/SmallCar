#pragma once

#include "FilConfig.h"

/*!
*   @note [RCR] This settings transport to FIL Driver
*/
#define __configUSE_RCC                   1
#define __configUSE_GPIO                  1
#define __configUSE_TIM                   1
#define __configUSE_USART                 0
#define __configUSE_DMA                   0
#define __configUSE_I2C                   0
#define __configUSE_ADC                   0
#define __configUSE_EXTI                  0
#define __configUSE_RTC                   0
#define __configUSE_FREERTOS              0
#define __configUSE_DeprecatedFunctions   0   // !Deprecated

#define __configCALC_RCC                  0
#define __configCALC_TIM                  0
#define __configCALC_USART                0
#define __configCALC_Regulators           0
#define __configCALC_Matrix               0
#define __configCALC_Kinematics           0

#if defined(STM32F401xx)
#define __config_TIM1_PSC        (84 - 1)
#define __config_TIM1_ARR        (200)
#define __config_TIM1_CH1        1
#define __config_TIM1_CH2        1

#define __config_TIM3_PSC        (420 - 1)
#define __config_TIM3_ARR        (1000)

#define MAX_PWM         __config_TIM1_ARR

#define PA8             pin_id(PORTA,8)
#define PA9             pin_id(PORTA,9)
#define PC13            pin_id(PORTC,13)

#define Board_Config {\
    SetPWR;           \
    SetSYSCFG;        \
    SetGPIOA;         \
    SetGPIOC;         \
    InitPeriph;       \
    InitTimers;       \
    InitInterrupts;   }

#define InitPeriph                                         {\
    conf_pin(PA8,ALTERNATE,PUSH_PULL,HIGH_S,NO_PULL_UP);    \
    conf_pin(PA9,ALTERNATE,PUSH_PULL,HIGH_S,NO_PULL_UP);    \
    conf_pin(PC13,GENERAL,PUSH_PULL,LOW_S,NO_PULL_UP);      }

#define InitTimers                                             {\
    TimPWMConfigure(TIM1,__config_TIM1_PSC,__config_TIM1_ARR,   \
                    __config_TIM1_CH1,__config_TIM1_CH2,0,0);   \
    TimPIDConfigure(TIM3,__config_TIM3_PSC, __config_TIM3_ARR); }

#define InitInterrupts  {\
    NVIC_EnableIRQ(TIM3_IRQn);  }

#endif /*STM32F401xx*/
#if defined(STM32F40_41xxx) || defined(STM32F411xE)
#define __config_TIM4_PSC        (4200 - 1)
#define __config_TIM4_ARR        (10000)
#define __config_TIM4_CH1        1
#define __config_TIM4_CH2        1
#define __config_TIM4_CH3        1
#define __config_TIM4_CH4        1

#define __config_TIM1_PSC        (840 - 1)
#define __config_TIM1_ARR        (1000)

#define MAX_PWM         __config_TIM4_ARR

#define PD12            pin_id(PORTD,12)
#define PD13            pin_id(PORTD,13)
#define PD14            pin_id(PORTD,14)
#define PD15            pin_id(PORTD,15)

#define Board_Config   {\
    SetPWR;             \
    SetSYSCFG;          \
    SetGPIOD;           \
    InitPeriph;         \
    SetTIM4;            \
    InitTimers;         \
    InitInterrupts;     \
    TIM4->CCR1 = 0x5DC; \
    TIM4->CCR2 = 0xBB8; \
    TIM4->CCR3 = 0x1770;\
    TIM4->CCR4 = 0x1F40;}

#define InitPeriph                                          {\
    conf_pin(PD12,ALTERNATE,PUSH_PULL,LOW_S,NO_PULL_UP);     \
    conf_pin(PD13,ALTERNATE,PUSH_PULL,LOW_S,NO_PULL_UP);     \
    conf_pin(PD14,ALTERNATE,PUSH_PULL,LOW_S,NO_PULL_UP);     \
    conf_pin(PD15,ALTERNATE,PUSH_PULL,LOW_S,NO_PULL_UP);     \
    conf_af(PD12,AF2);                                       \
    conf_af(PD13,AF2);                                       \
    conf_af(PD14,AF2);                                       \
    conf_af(PD15,AF2);                                       }

#define InitTimers                                             {\
    TimPWMConfigure(TIM4,__config_TIM4_PSC,__config_TIM4_ARR,   \
                    __config_TIM4_CH1,__config_TIM4_CH2,        \
                    __config_TIM4_CH3,__config_TIM4_CH4);       \
    TimPIDConfigure(TIM1,__config_TIM1_PSC, __config_TIM1_ARR); }

#ifdef STM32F411xE
#define InitInterrupts         {\
    NVIC_EnableIRQ(TIM1_UP_TIM10_IRQn);  }
#endif/*STM32F411xE*/
#ifdef STM32F40_41xxx
#define InitInterrupts         {\
    NVIC_EnableIRQ(TIM1_IRQn);  }
#endif/*STM32F40_41xxx*/

#endif /*STM32F40_41xxx*/
