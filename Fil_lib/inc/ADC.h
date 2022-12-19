    /*!
    *   --------------------------------------------------------------------------
    *                       ///ADC initialization\\\
    *   --------------------------------------------------------------------------
    *   @author RCR group developers - Caska
    *   @date 18/07/2022 - last update version ADC
    *
    *       @note [FIL:ADC] Configuration file ADC
    */
#pragma once
#include "FilConfig.h"

#if(FIL_ADC == 1)
//----------------------------------------ADC Length-------------------------------------------------------------//
#define ADC_3_CYCLES    0
#define ADC_15_CYCLES   1
#define ADC_28_CYCLES   2
#define ADC_56_CYCLES   3
#define ADC_84_CYCLES   4
#define ADC_112_CYCLES  5
#define ADC_144_CYCLES  6
#define ADC_480_CYCLES  7

#if(__configADC_RESOLUTION == 10)
    #define K_RESOLUTION    1024.0
#elif(__configADC_RESOLUTION == 8)
    #define K_RESOLUTION    256.0
#elif(__configADC_RESOLUTION == 6)
    #define K_RESOLUTION    64.0
#else
    #define K_RESOLUTION    4096.0
#endif /*__configADC_RESOLUTION*/
//----------------------------------------ADC Functions----------------------------------------------------------//
#ifdef CortexM4
#ifdef CortexM4_High

    /*!
    *   @brief  ADCAddRegularChannel(ADCx,CHANNEL,CYCLES) - Adding new channel to conversions ADC
    *       @arg ADCx - Number of ADC
    *       @arg CHANNEL - Number of target channel
    *       @arg CYCLES - Sample time selection
    */
    __attribute__((unused)) static char RCH = 0;
    #define ADCAddRegularChannel(ADCx,CHANNEL,CYCLES)                                       {\
                        ADCx->SQR1 &= ~(0xF << 20);                                          \
                        ADCx->SQR1 |= RCH << 20;                                             \
                        *(&ADCx->SQR3 - (RCH / 6)) |= CHANNEL << ((RCH * 5) % 30);           \
                        *(&ADCx->SMPR2 - ((RCH / 10)*0x4)) |= CYCLES << ((RCH * 3) % 30);    \
                        RCH++;                                                               }

    /*!
    *   @brief  ADCAddInjectedChannel(ADC,CHANNEL,CYCLES, JCH) - Adding new injected channel to conversions ADC
    *       @arg ADC - Number of ADC
    *       @arg CHANNEL - Number of target injected channel
    *       @arg CYCLES - Sample time selection
    *       @arg JCH
    */
    __attribute__((unused)) static char JCH = 0;
    #define ADCAddInjectedChannel(ADCx,CHANNEL,CYCLES, JCH)                                        {\
                        ADCx->JSQR &= ~(0xF << 20);                                                 \
                        ADCx->JSQR |= (JCH << 20);                                                  \
                        ADCx->JSQR |= (CHANNEL << (((JCH + 3) * 5) % 30));                          \
                        *(&ADCx->SMPR2 - ((JCH / 10)*0x4)) |= (CYCLES << (JCH * 3) % 30);           \
                        if(JCH == 3) JCH = 0;                                                       \
                        JCH++;                                                                      }

#endif /*CortexM4_High*/

#ifdef CortexM4_Low

    #define ADCSimpleConfigure(ADC)                                            {\
        SetADCAdon(ADC);                                                        \
        SetADCDDS(ADC);                                                         \
        SetADCDMA(ADC);                                                         \
        SetADCCont(ADC);                                                        \
        SetADCScan(ADC);                                                        \
        (__configADC_InterruptRequest == 1) ? SetADCRegularInterrupt(ADC) :     \
                                              ResetADCRegularInterrupt(ADC);    \
        (__configADC_InterruptRequest == 1) ? SetADCInjectedInterrupt(ADC) :    \
                                              ResetADCInjectedInterrupt(ADC);   \
        ADCStartRegular(ADC);                                                   \
        while(!(ADC->SR & ADC_SR_EOC)) {}                                       \
        if(CheckADCJStart(ADC) == 1) ADCStartInjected(ADC);                     \
        while(!(ADC->SR & ADC_SR_EOC)) {}                                       }

    /*!
    *   @brief  ADCAddRegularChannel(CHANNEL,CYCLES) - Adding channel to conversions ADC
    *       @arg CHANNEL - Number of target channel
    *       @arg CYCLES - Sample time selection
    */
    __attribute__((unused)) char RCH;
    #define ADCAddRegularChannel(CHANNEL,CYCLES)                                           {\
                        ADC1->SQR1 &= ~(0xF << 20);                                         \
                        ADC1->SQR1 |= RCH << 20;                                            \
                        *(&ADC1->SQR3 - (RCH / 6)) |= CHANNEL << ((RCH * 5) % 30);          \
                        *(&ADC1->SMPR2 - ((RCH / 10)*0x4)) |= CYCLES << ((RCH * 3) % 30);   \
                        RCH++;                                                              }

    /*!
    *   @brief  ADCAddInjectedChannel(CHANNEL,CYCLES) - Adding injected channel to conversions ADC
    *       @arg CHANNEL - Number of target injected channel
    *       @arg CYCLES - Sample time selection
    */
    __attribute__((unused)) char JCH;
    #define ADCAddInjectedChannel(CHANNEL,CYCLES)                                           {\
                        ADC1->JSQR &= ~(0xF << 20);                                          \
                        ADC1->JSQR |= (JCH << 20);                                           \
                        ADC1->JSQR |= (CHANNEL << (((JCH + 3) * 5) % 30));                   \
                        *(&ADC1->SMPR2 - ((JCH / 10)*0x4)) |= (CYCLES << (JCH * 3) % 30);    \
                        if(JCH == 3) JCH = 0;                                                \
                        JCH++;                                                               }

    /*!
    *   @brief ADCAddChannel(CHANNEL,TYPE,CYCLES) - General adding channel to conversion ADC
    *       @arg CHANNEL - Number of target injected channel
    *       @arg TYPE - Type of necessary channel: REGULAR or INJECTED
    *       @arg CYCLES - Sample time selection
    */
    #define REGULAR         (0x2F)
    #define INJECTED        (0x3F)
    #define ADCAddChannel(CHANNEL,TYPE,CYCLES)                                     {\
                        if(TYPE == REGULAR) ADCAddRegularChannel(CHANNEL,CYCLES);   \
                        if(TYPE == INJECTED) ADCAddInjectedChannel(CHANNEL,CYCLES); }

#endif /*CortexM4_Low*/
#endif /*CortexM4*/

    /*!
    *   @brief  ADCAddInjectedGroups(ADC,NUMBER,J1,J2,J3,J4) -
    *       @arg ADC - Number of ADC
    *       @arg NUMBER - Number of necessary channels
    *       @arg Jx - number of ADC_IN channel
    */
    #define ADCAddInjectedGroup(ADC,NUMBER,J1,J2,J3,J4)                                        {\
                        ADC->JSQR &= ~(0x3FFFFF);                                               \
                        ADC->JSQR |= (NUMBER << 20);                                            \
                        ADC->JSQR |= ((J1) | (J2 << 5) | (J3 << 10) | (J4 << 15));              \
                        SetADCContInjected(ADC);                                                }

//----------------------------------------Set state----------------------------------------------------------------------------------------------------------------------------//
    #define SetADCSMP1(ADC,CYCLES)          ((ADC->SMPR1) |= ADCSmpr1(CYCLES))
    #define SetADCSMP2(ADC,CYCLES)          ((ADC->SMPR2) |= ADCSmpr2(CYCLES))
    #define SetADCLength(ADC,LENGTH)        ((ADC->SQR1) |= (LENGTH << 20))
    #define SetADCScan(ADC)                 ((ADC->CR1) |= (ADC_CR1_SCAN))
    #define SetADCDMA(ADC)                  ((ADC->CR2) |= (ADC_CR2_DMA))
    #define SetADCCont(ADC)                 ((ADC->CR2) |= (ADC_CR2_CONT))
    #define SetADCDDS(ADC)                  ((ADC->CR2) |= (ADC_CR2_DDS))
    #define SetADCAdon(ADC)                 ((ADC->CR2) |= (ADC_CR2_ADON))
    #define ADCStartRegular(ADC)            ((ADC->CR2) |= (ADC_CR2_SWSTART))
    #define ADCStartInjected(ADC)           ((ADC->CR2) |= (ADC_CR2_JSWSTART))
    #define SetADCInjectedInterrupt(ADC)    ((ADC->CR1) |= (ADC_CR1_JEOCIE))
    #define SetADCRegularInterrupt(ADC)     ((ADC->CR1) |= (ADC_CR1_EOCIE))
    #define SetADCContInjected(ADC)         ((ADC->CR1) |= (ADC_CR1_JAUTO))
//----------------------------------------Reset state----------------------------------------------------------------------------------------------------------------------------//
    #define ResetADCCont(ADC)               ((ADC->CR2) &= (~ADC_CR2_CONT))
    #define ADCStopRegular(ADC)             ((ADC->CR2) &= (~ADC_CR2_SWSTART))
    #define ResetADCEOCEvent(ADC)           ((ADC->SR) &= (~ADC_SR_EOC))
    #define ResetADCJEOCEvent(ADC)          ((ADC->SR) &= (~ADC_SR_JEOC))
    #define ResetADCOVREvent(ADC)           ((ADC->SR) &= (~ADC_SR_OVR))
    #define ResetADCInjectedInterrupt(ADC)  ((ADC->CR1) &= (~ADC_CR1_JEOCIE))
    #define ResetADCRegularInterrupt(ADC)   ((ADC->CR1) &= (~ADC_CR1_EOCIE))
//----------------------------------------Status monitoring--------------------------------------------------------------------------------------------------------------------//
    #define CheckADCAnalogWatchdogEvent(ADC)     (((ADC->SR) & (ADC_SR_AWD)))
    #define CheckADCRegularEndEvent(ADC)         (((ADC->SR) & (ADC_SR_EOC)) >> 1)
    #define CheckADCInjectedEndEvent(ADC)        (((ADC->SR) & (ADC_SR_JEOC)) >> 2)
    #define CheckADCInjectedStartEvent(ADC)      (((ADC->SR) & (ADC_SR_JSTRT)) >> 3)
    #define CheckADCRegularStartEvent(ADC)       (((ADC->SR) & (ADC_SR_STRT)) >> 4)
    #define CheckADCOverrunEvent(ADC)            (((ADC->SR) & (ADC_SR_OVR)) >> 5)
    #define CheckADCJStart(ADC)                  (((ADC->CR1) & (ADC_CR1_JAUTO)) >> 10)
//---------------------------Simple commands reset and set the state-------------------------------------------------------------------------------------------------------------//
    #define ConfADCResolution(ADC,RESOLUTION)               {ADC->CR1 = (((ADC->CR1)&(~(ADC_CR1_RES)))|((uint32_t)(RESOLUTION << 24)));}
    #define ConfADCVBATE                                    {ADC->CCR = (((ADC->CCR)&(~(ADC_CCR_VBATE | ADC_CCR_TSVREFE)))|(ADC_CCR_VBATE));}
    #define ConfADCTSVREFE                                  {ADC->CCR = (((ADC->CCR)&(~(ADC_CCR_TSVREFE | ADC_CCR_VBATE)))|(ADC_CCR_TSVREFE));}
    #define ConfADCCCR(CCRx)                                {ADC->CCR = (((ADC->CCR)&(~(ADC_CCR_ADCPRE)))|(CCRx << 16));}

#if(__configCONVERT_Volts == 1)
struct {
    unsigned char ADCSource[4];
    float Injeted[4];
    float Regular[14];
    float BATTERY;
    float TEMPERATURE;
}ADCStatus;
#elif (__configCONVERT_Volts == 0)
struct {
    unsigned char ADCSource[4];
    uint16_t Injected[4];
    uint16_t Regular[14];
    uint16_t BATTERY;
    uint16_t TEMPERATURE;
}ADCStatus;
#endif /*__configCONVERT_Volts*/

#ifdef CortexM4_Low

    /*!
    *   @brief ADC_Init(void) - General Initialize parameters of ADC (Low version)
    *       @return nothing
    */
    __WEAK void ADC_Init(void);

#endif /*CortexM4_High*/
#ifdef CortexM4_High

    /*!
    *   @brief ADC_Init(void) - General Initialize parameters of ADC (High version)
    *       @arg ADCx - number of necessary ADC
    *       @return nothing
    */
    __WEAK void ADC_Init(ADC_TypeDef *ADCx);

#endif /*CortexM4_High*/

#endif /*FIL_ADC*/
