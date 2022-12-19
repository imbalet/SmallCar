/*!
*   --------------------------------------------------------------------------
*                       ///Developer workspace file\\\
*   --------------------------------------------------------------------------
*/
#include "dev.h"
#if (_configUSEBoards == 3)
    /*!
    *   @brief SetVoltage(Motor, Duty) - Установить напряжение на двигатель
    *       @arg Motor - number of Motor
    *       @arg Duty - duty value
    *       @note [FIL:TIM] Функция предназначена для управления двигателями постоянного тока.
    */


bool SetVoltage(float Duty)
{
    if(Duty >= 0.0)
    {
        ResetPin(BTN1_DIR_PIN);
//        SetPWM(BTN1_CCR,Duty);
        return true;
    }
    else
    {
        SetPin(BTN1_DIR_PIN);
//        SetPWM(BTN1_CCR,Duty);
        return true;
    }
return false;
}

void ServoInit(Servomotor* Servo, char servoType,TIM_TypeDef *TIMx, uint16_t ms)
{
    Servo->CCR = &TIMx->CCR1;
    Servo->ARR = TIMx->ARR;
    Servo->ms = ms;

    if(servoType == PDI6225MG_300)
    {
        Servo->maxAngle = 300;
        (*Servo).min_ms = 0.5;
        (*Servo).max_ms = 2.5;
    }
    else if(servoType == MG996R)
    {
        Servo->maxAngle = 180;
        (*Servo).min_ms = 1.0;
        (*Servo).max_ms = 2.0;
    }
}

void ServoSetRange(Servomotor* Servo, uint16_t min_angle, uint16_t max_angle)
{
    if(min_angle >= max_angle) return;
    Servo->Range_min = min_angle;
    Servo->Range_max = max_angle;
}

void ServoSetAngle(Servomotor* Servo, uint16_t angle)
{
    if(Servo->Range_min != 0 && angle < Servo->Range_min) angle = Servo->Range_min;
    if(Servo->Range_max != 0 && angle > Servo->Range_max) angle = Servo->Range_max;
    if(angle > (*Servo).maxAngle) angle = (*Servo).maxAngle;
    if(angle < 0)   angle = 0;

    float min_PWM = (float)(((Servo->ARR) * (*Servo).min_ms) / (*Servo).ms);
    float max_PWM = (float)(((Servo->ARR) * (*Servo).max_ms) / (*Servo).ms);

    *(*Servo).CCR = (uint32_t)(angle * ((max_PWM - min_PWM) / (*Servo).maxAngle) + min_PWM);
}

//static void PID_Parse_EncoderData(int32_t encoderdata)
//{
//    PID->current = ((((float)(encoderdata)) * DISK_TO_REAL) / TIME);
//    Motor_Coord += PID[0].current * TIME;
//}

//int16_t EncData;
//void RegulatorPIDLowLevel(void)
//{
//    EncData = ((int16_t)*ENCODER1_CNT);
//    if(EnginePWM > 1.0) EnginePWM = 1.0;
//    if(EnginePWM < -1.0) EnginePWM = -1.0;
//    PID->target = EnginePWM;
//    PID_Parse_EncoderData(EncData);
//    *ENCODER1_CNT = 0;
//    PID_Calc(&PID[0]);
//    SetVoltage(PID->output);
//}
#endif /*_configUSEBoards*/
