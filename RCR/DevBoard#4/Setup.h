#pragma once

#define __configUSE_RCC                   1
#define __configUSE_GPIO                  1
#define __configUSE_TIM                   1
#define __configUSE_USART                 0
#define __configUSE_DMA                   1
#define __configUSE_I2C                   0
#define __configUSE_ADC                   1
#define __configUSE_EXTI                  0
#define __configUSE_RTC                   0
#define __configUSE_FREERTOS              0

#define __configCALC_RCC                  1
#define __configCALC_TIM                  1
#define __configCALC_USART                0
#define __configCALC_Regulators           0
#define __configCALC_Matrix               0

#define __configCONVERT_Volts               (0)
#define __configUSE_Battery_Charging        (0)
#define __configUSE_Temperature_Sensor      (0)

#define __configADC_InterruptRequest        (0)
#define __configADC_DMARequest              (1)
#define __configADC_Divider                 (3)
#define __configADC_RESOLUTION              (12)        // 12-bit resolution
#define __configADC_CYCLES                  (ADC_480_CYCLES)
#define __configADC_DIVIDER                 (3)

#define Board_Config                                                                   {\
                    SetGPIOA;                                                           \
                    SetTIM1;                                                            \
                    SetADC1;                                                            \
                    SetDMA2;                                                            \
                    GPIOConfPin(PWM1_PIN, ALTERNATE, PUSH_PULL, FAST_S, NO_PULL_UP);    \
                    GPIOConfPin(PWM2_PIN, ALTERNATE, PUSH_PULL, FAST_S, NO_PULL_UP);    \
                    GPIOConfAF(PWM1_PIN,AF1);                                           \
                    GPIOConfAF(PWM2_PIN,AF1);                                           \
                    GPIOConfPin(DIR1_PIN, GENERAL, PUSH_PULL, FAST_S, NO_PULL_UP);      \
                    GPIOConfPin(DIR2_PIN, GENERAL, PUSH_PULL, FAST_S, NO_PULL_UP);      \
                    GPIOConfPin(DIR3_PIN, GENERAL, PUSH_PULL, FAST_S, NO_PULL_UP);      \
                    GPIOConfPin(DIR4_PIN, GENERAL, PUSH_PULL, FAST_S, NO_PULL_UP);      \
                    GPIOConfPin(SENSOR1_PIN, ANALOG, PUSH_PULL, FAST_S, NO_PULL_UP);    \
                    GPIOConfPin(SENSOR2_PIN, ANALOG, PUSH_PULL, FAST_S, NO_PULL_UP);    \
                    TimPWMConfigureAutomatic(TIM1,50,1,1,0,0);                          \
                    SysTick_Config(84000);                                              }




