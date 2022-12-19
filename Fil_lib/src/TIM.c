    /*!
    *   --------------------------------------------------------------------------
    *                       ///TIM Source file\\\
    *   --------------------------------------------------------------------------
    *   @author RCR group developers
    *   @date 13/07/2022 - last update version TIM
    *
    *       @note [FIL:TIM] TIM Source file.
    */
#include "TIM.h"
uint32_t globalTime = 0;
/*!
*    @brief void SysTick_Handler(void) - System 24-bit timer, increment the time value in 1Hz to 1000
*       @note [FIL:TIM] ����� ������������ ��� ������ �������, 1000 ������ ������������� 1 �������
*/

void SysTick_Handler(void)
{

    globalTime++;
}
#if (FIL_CALC_TIM == 1)
//---------------------------------------------------------//
//----------------------Timer Interrupts-------------------//
//---------------------------------------------------------//
void TIM1_IRQHandler(void)
{

ResetTimSR(TIM1);
}
//uint16_t Enc[2];
//void TIM2_IRQHandler(void)
//{
//
//Enc[0] = TIM3 -> CNT;
//Enc[1] = TIM5 -> CNT;
//
//ResetTimSR(TIM2);
//}

void TIM3_IRQHandler(void)
{

ResetTimSR(TIM3);
}
//
//void TIM4_IRQHandler(void)
//{
//
//ResetTimSR(TIM4);
//}

void TIM5_IRQHandler(void)
{

ResetTimSR(TIM5);
}

#if defined(STM32F40_41xxx) /*--------------STM32F407------------------*/
void TIM6_DAC_IRQHandler(void)
{

ResetTimSR(TIM6);
}

void TIM7_IRQHandler(void)
{

ResetTimSR(TIM7);
}

void TIM8_UP_TIM13_IRQHandler(void)
{

ResetTimSR(TIM13);
}
#endif /*STM32F40_41xxx*/
static uint32_t startTick;
void delay_ms(uint32_t ticks)
{
    if(ticks == 0) return;
    startTick = globalTime;
    while((globalTime - startTick) < ticks);
}

void delay_sec(uint32_t ticks)
{
    if(ticks == 0) return;
    startTick = globalTime / 1000;
    while(((globalTime / 1000) - startTick) < ticks);
}
    /*!
    *   @brief CalcTimStatus(TIM_TypeDef *TIMx) - Calculating Timer Status
    *       @arg TIMx - number of timer
    *           @note [FIL:TIM] ������� ��������� �������� ������� ������ �������, ���������� ��� � ������� ������
    */
void CalcTimStatus(TIM_TypeDef *TIMx)
{
    TIMStatus.Timer[0] = 'T';
    TIMStatus.Timer[1] = 'I';
    TIMStatus.Timer[2] = 'M';
    TIMStatus.Timer[3] = (TIMx == TIM1) ? 0x31 :
                         (TIMx == TIM2) ? 0x32 :
                         (TIMx == TIM3) ? 0x33 :
                         (TIMx == TIM4) ? 0x34 :
                         (TIMx == TIM5) ? 0x35 :
                         (TIMx == TIM6) ? 0x36 :
                         (TIMx == TIM7) ? 0x37 :
                         (TIMx == TIM8) ? 0x38 :
                         (TIMx == TIM9) ? 0x39 : 0x31 ;
    TIMStatus.Timer[4] = (TIMx == TIM10) ? 0x30 :
                         (TIMx == TIM11) ? 0x31 :
                         (TIMx == TIM12) ? 0x32 :
                         (TIMx == TIM13) ? 0x33 :
                         (TIMx == TIM14) ? 0x34 : ' ';
    CalcTimClockSourse(TIMx);

    TIMStatus.DutyCH1 = ((uint32_t)(((float)TIMx->CCR1) / TIMx->ARR * 100));
    TIMStatus.DutyCH2 = ((uint32_t)(((float)TIMx->CCR2) / TIMx->ARR * 100));
    TIMStatus.DutyCH3 = ((uint32_t)(((float)TIMx->CCR3) / TIMx->ARR * 100));
    TIMStatus.DutyCH4 = ((uint32_t)(((float)TIMx->CCR4) / TIMx->ARR * 100));
    TIMStatus.Frequency = (TIMStatus.SourseClock / ((TIMx->PSC + 1) * TIMx->ARR));
}
    /*!
    *   @brief CalcTimFrequency(TIM_TypeDef *TIMx, uint16_t freq) - Calculating Timer frequency
    *       @arg TIMx - number of timer
    *       @arg freq - necessary frequency
    *           @note [FIL:TIM] ������� ��� ������� ������� ������ ��������
    */
void CalcTimFrequency(TIM_TypeDef *TIMx, uint32_t freq)
{
    CalcTimClockSourse(TIMx);

    TIMx->PSC = (freq <= 100) ? ((uint32_t)(TIMStatus.SourseClock / 10000)) :
                                ((uint32_t)(TIMStatus.SourseClock / 1000000));
    TIMx->ARR = ((uint32_t)(TIMStatus.SourseClock / ((TIMx->PSC)* freq)));
    TIMx->PSC -= 1;
}

void CalcTimPulseLength(TIM_TypeDef* TIMx, uint8_t channel, uint8_t Degree, uint16_t Length)
{
    uint32_t divider = 0;
    if(Degree >= 3 && Degree < 6) { CalcTimFrequency(TIMx, 1); divider = 1000; }
    if(Degree >= 6 && Degree < 9) { CalcTimFrequency(TIMx, 1000); divider = 1000000; }
    if(Degree >= 9 && Degree < 12) { CalcTimFrequency(TIMx, 1000000); divider = 1000000000; }

    if(channel == 1) TIMx->CCR1 = (((float)(TIMx->ARR)) * (((float)(Length)) / divider));
    if(channel == 2) TIMx->CCR2 = (((float)(TIMx->ARR)) * (((float)(Length)) / divider));
    if(channel == 3) TIMx->CCR3 = (((float)(TIMx->ARR)) * (((float)(Length)) / divider));
    if(channel == 4) TIMx->CCR4 = (((float)(TIMx->ARR)) * (((float)(Length)) / divider));
}

    /*!
    *   @brief CalcTimClockSourse(TIM_TypeDef *TIMx) - Calculating Timer Clock Sourse
    *       @arg TIMx - number of timer
    *       @note [FIL:TIM] ������� ��������� ������, ������������ ��������, ������� ������.
    */
void CalcTimClockSourse(TIM_TypeDef *TIMx)
{
    CalcRCCClocks();
    #if defined(STM32F401xx)
    if(TIMx == TIM1 || TIMx == TIM9 || TIMx == TIM10 || TIMx == TIM11)
    {
        TIMStatus.SourseClock = Clocks.CurrentAPB2;
    }
    else if(TIMx == TIM2 || TIMx == TIM3 || TIMx == TIM4 || TIMx == TIM5)
    {
        TIMStatus.SourseClock = Clocks.CurrentAPB1;
    }
#elif defined(STM32F40_41xxx)
    if(TIMx == TIM1 || TIMx == TIM8 || TIMx == TIM9 || TIMx == TIM10 || TIMx == TIM11)
    {
        TIMStatus.SourseClock = Clocks.CurrentAPB2;
    }
    else if(TIMx == TIM2 || TIMx == TIM3 || TIMx == TIM4 || TIMx == TIM5 || TIMx == TIM6 || TIMx == TIM7 || TIMx == TIM12 || TIMx == TIM13 || TIMx == TIM14)
    {
        TIMStatus.SourseClock = Clocks.CurrentAPB1;
    }
#endif
}

    /*!
    *   @brief SetPWM(TIM_TypeDef *TIMx, uint8_t Channel, float Duty) - Set impulse duration on channel timer
    *       @arg TIMx - Necessary timer
    *       @arg Channel - Channel of timer
    *       @arg Duty - duty value
    *       @note [FIL:TIM] Function for setting PWM of timer
    */
    __WEAK bool SetPWM(TIM_TypeDef *TIMx, uint8_t Channel, float Duty)
    {
        if(Channel > 4) return false;
        __attribute__((unused)) uint32_t *address = ((uint32_t *)TIMx);
        address += ((uint32_t)(((uint32_t)(Channel - 1) * 0x4) + 0x34) >> 2);
        if(Duty > 1.0) Duty = 1.0;
        if(Duty < -1.0) Duty = -1.0;
        if(Duty >= 0)
        {
            *address = ((int32_t) (Duty * TIMx->ARR));
            return true;
        }
        else
        {
            *address = ((int32_t)(TIMx->ARR +  (Duty * TIMx->ARR)));
            return true;
        }
        return false;
    }

    /*!
    *   @brief float CalcTimDuration(void(*Handle)(void)) - Measure function time
    *       @arg Handle - Function
    *       @attention Function must do not return anything and have anything type other than void
    */
    __WEAK float CalcTimDuration(void(*Handle)(void))
    {
        uint32_t startInterval = globalTime;
        (*Handle)();
        return ((float)(globalTime - startInterval) / 1000);
    }


#endif /*FIL_CALC_TIM*/
