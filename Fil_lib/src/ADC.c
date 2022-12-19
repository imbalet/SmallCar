    /*!
    *   --------------------------------------------------------------------------
    *                       ///ADC Source file\\\
    *   --------------------------------------------------------------------------
    *   @author RCR group developers - Caska
    *   @date 13/10/2022 - last update version ADC
    *
    *       @note [FIL:ADC] ADC Source file.
    */
#include "ADC.h"
//--------------------------------------------------------------------------------//
//---------------------------ADC Interrupts---------------------------------------//
//--------------------------------------------------------------------------------//
/*!
*   @brief ADC_IRQHandler(void)
*/
void ADC_IRQHandler(void)
{

}
#if(FIL_ADC == 1)
//------------------------------------------------------------------------------------//
/*!
*   @info Main initializing function
*/
//------------------------------------------------------------------------------------//
#ifdef CortexM4_Low
__WEAK uint16_t ADC1_Data[ADC1_NUMB];
__WEAK void ADC_Init(void)
{
/* Confguration Divider */
#if(__configADC_Divider == 0)
    ConfADCCCR(0);
#elif(__configADC_Divider == 1)
    ConfADCCCR(1);
#elif(__configADC_Divider == 2)
    ConfADCCCR(2);
#elif(__configADC_Divider == 3)
    ConfADCCCR(3);
#else /*__configADC_Divider*/
    ConfADCCCR(3);
#endif /*__configADC_Divider*/
/* Configuration Resolution*/
#if(__configADC_RESOLUTION == 6)
    ConfADCResolution(ADC1,3);
#elif(__configADC_RESOLUTION == 8)
    ConfADCResolution(ADC1,2);
#elif(__configADC_RESOLUTION == 10)
    ConfADCResolution(ADC1,1);
#elif(__configADC_RESOLUTION == 12)
    ConfADCResolution(ADC1,0);
#else
    ConfADCResolution(ADC1,0);
#endif /*__configADC_RESOLUTION*/
#if(__configUSE_Temperature_Sensor == 1)
    ConfADCTSVREFE;
    ADCAddChannel(16,REGULAR,ADC_480_CYCLES);
    ADCAddChannel(17,REGULAR,ADC_480_CYCLES);
#elif(__configUSE_Battery_Charging == 1)
    ConfADCVBATE;
    ADCAddChannel(18,REGULAR,ADC_480_CYCLES);
#endif /*__configUSE_Battery_Charging*/
    unsigned char Buf[4] = {'A','D','C','1'};
    for(int i = 0; i <= 3; i++) { ADCStatus.ADCSource[i] = Buf[i]; }
    SetADCAdon(ADC1);
#if(FIL_DMA == 1 && __configADC_DMARequest == 1)
    SetADCDDS(ADC1);
    SetADCDMA(ADC1);
#endif /*__configADC_DMARequest*/
    SetADCCont(ADC1);
    SetADCScan(ADC1);
#if(__configADC_InterruptRequest == 1)
    SetADCRegularInterrupt(ADC);
#endif /*__configADC_InterruptRequest*/
        ADCStartRegular(ADC1);
        if(CheckADCJStart(ADC1) == 1) ADCStartInjected(ADC1);
}
#endif /*CortexM4_Low*/


#endif /*FIL_ADC*/
