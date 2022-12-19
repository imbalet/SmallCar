#pragma once
#include <stdbool.h>
#include "FilConfig.h"

#if (_configUSEBoards == 3)
#define PDI6225MG_300   0
#define MG996R          1

#define Button1_Click       (PinVal(EXTI1_PIN))
#define Button2_Click       (PinVal(EXTI2_PIN))
#define Button3_Click       (PinVal(EXTI3_PIN))
#define Button4_Click       (PinVal(EXTI4_PIN))
#define Button5_Click       (PinVal(EXTI5_PIN))


//---------------------------------------------//
//---------------Servo struct------------------//
//---------------------------------------------//
typedef struct
{
    volatile uint32_t *CCR,
                       ARR;
    uint16_t  ms;
    float     min_ms,
              max_ms;
    uint16_t maxAngle;
    uint16_t Range_min, Range_max;
} Servomotor;

//-------------------------------------------------------------------------------------//
void ServoInit(Servomotor* Servo, char servoType, TIM_TypeDef *TIMx, uint16_t ms);

void ServoSetRange(Servomotor* Servo, uint16_t min_angle, uint16_t max_angle);

void ServoSetAngle(Servomotor* Servo, uint16_t angle);
//-------------------------------------------------------------------------------------//

bool SetVoltage(float Duty);

float EnginePWM;
float Motor_Coord;
void RegulatorPIDLowLevel(void);
#endif /*#if (_configUSEBoards == 3)*/
