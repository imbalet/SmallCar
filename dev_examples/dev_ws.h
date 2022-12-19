#pragma once

/*!
*   @brief LESSON_1
*       @note [RCR:LESSON1] LED Operations
*/

// ��������� � ���������� �� ������� ����� ������
// ��-�� �������� ������ �������� �������� ����������. ����� ���������, ������� �������� delay_ms(10).
/*
    int main(void)
    {
        Board_Config;
        bool flag = false;
        bool IsPress = false;
        while(1)
        {
        if(!Button1_Click) IsPress = false;
            // ������ ������, �������� �������
            if(Button1_Click && !flag && !IsPress)
            {
                SetPin(LED2_PIN);
                flag = true;
                IsPress = true;
            }
            // ������ ������, ������ �������
            if(Button1_Click && flag && !IsPress)
            {
                ResetPin(LED2_PIN);
                flag = false;
                IsPress = true;
            }
        }
    }
*/

// ��������� ����������� �� ������� ������
/*
    int main(void)
    {
        // ���� �� ����������� � ��������������� ������� (PC13)
        Board_Config;
        while(1)
        {
            // ���� ������ ������ ������ - ���� ������ ���������
            if(Button1_Click)
            {
                ResetPin(LED1_PIN);
                ResetPin(LED2_PIN);
            }
            // ���� ������ ������ ������ - ���� ������ ���������
            if(Button2_Click)
            {
                SetPin(LED1_PIN);
                SetPin(LED2_PIN);
            }
            else
            {
                SetPin(LED1_PIN);
                ResetPin(LED2_PIN);
            }
        }
    }
*/

// ���������\���������� ���������� ����� 2 ������
/*
int main(void)
{
    Board_Config;
    while(1)
    {
        // ���� ������1 ������ �� ��������
        if(Button1_Click)
        {
            SetPin(LED2_PIN);
        }
        // ���� ������2 ������ �� ���������
        if(Button2_Click)
        {
            ResetPin(LED2_PIN);
        }
    }
}
*/


/*!
*   @brief LESSON_2
*       @note [RCR:LESSON2] PWM Operations
*/

// ������� ���������� �������� ���������
/*
int main(void)
{
    Board_Config;
    float PWM = 0.0;
    while(1)
    {
        while(PWM <= 1.0)
        {
            SetVoltage(PWM);
            delay_sec(1);
            PWM += 0.1;
        }
    }
}
*/

/*!
*   @brief LESSON_3
*       @note [RCR:LESSON3] Move Robot on range
*/

// �������� ������� ������������� ����������
/*

static void PID_Parse_EncoderData(int32_t encoderdata)
{
    PID->current = ((((float)(encoderdata)) * DISK_TO_REAL) / TIME);
    Motor_Coord += PID[0].current * TIME;
}

float EnginePWM;
int16_t EncData;
void RegulatorPIDLowLevel(void)
{
    EncData = ((int16_t)*ENCODER1_CNT);
    if(EnginePWM > 1.0) EnginePWM = 1.0;
    if(EnginePWM < -1.0) EnginePWM = -1.0;
    PID->target = EnginePWM;
    PID_Parse_EncoderData(EncData);
    *ENCODER1_CNT = 0;
    PID_Calc(&PID[0]);
    SetVoltage(PID->output);
}

float distanse = 0.0;
void TIM4_IRQHandler(void)
{
    if(Motor_Coord <= distanse) RegulatorPIDLowLevel();
    else
    {
        PID_Stop(&PID[0]);
        SetVoltage(0.0);
    }
ResetTimSR(TIM4);
}
*/

/*!
*   @brief LESSON_4
*       @note [RCR:LESSON4] Servo management
*/

/*
Servomotor Servo1;
int main(void)
{
    Board_Config;
    ServoInit(&Servo1,PDI6225MG_300,TIM5,20);
    ServoSetRange(&Servo1,5,60);
    ServoSetAngle(&Servo1,10);
    uint8_t angle = 0.0;
    while(1)
    {
        while(angle <= 60)
        {
            ServoSetAngle(&Servo1,angle);
            angle = angle + 5;
            delay_ms(500);
        }
        while(angle >= 5)
        {
            ServoSetAngle(&Servo1,angle);
            angle = angle - 5;
            delay_ms(500);
        }
    }
}
*/

/*
Servomotor Servo1;
int main(void)
{
    Board_Config;
    ServoInit(&Servo1,PDI6225MG_300,TIM5,20);
    ServoSetRange(&Servo1,5,60);
    ServoSetAngle(&Servo1,10);
    uint8_t angle = 5;
    while(1)
    {
        while(angle <= 60)
        {
            ServoSetAngle(&Servo1,angle);
            angle = angle*2;
            delay_ms(500);
        }
        while(angle >= 5)
        {
            ServoSetAngle(&Servo1,angle);
            angle = angle/2;
            delay_ms(500);
        }
    }
}
*/

/*!
*   @brief LESSON_5
*       @note [RCR:LESSON5] Robot racing
*/

/*
Servomotor Servo1;

void MoveRectangle(float dist)
{
    Motor_Coord = 0.0;
    EnginePWM = 0.1;

    // ������ �����
    while(Motor_Coord <= dist) {}
    Motor_Coord = 0.0;

    // �������
    ServoSetAngle(&Servo1, 60);
    while(Motor_Coord <= dist/2) {}
    Motor_Coord = 0.0;
    ServoSetAngle(&Servo1,30);

    // ������ �����
    while(Motor_Coord <= dist) {}
    Motor_Coord = 0.0;

    // �������
    ServoSetAngle(&Servo1, 60);
    while(Motor_Coord <= dist/2) {}
    Motor_Coord = 0.0;
    ServoSetAngle(&Servo1,30);

    // ������ �����
    while(Motor_Coord <= dist) {}
    Motor_Coord = 0.0;

    // �������
    ServoSetAngle(&Servo1, 60);
    while(Motor_Coord <= dist/2) {}
    Motor_Coord = 0.0;
    ServoSetAngle(&Servo1,30);

    // ��������� �����
    while(Motor_Coord <= dist) {}
    Motor_Coord = 0.0;

PID_Stop(&PID[0]);
SetVoltage(0.0);
}

int main(void)
{
    Board_Config;
    ServoInit(&Servo1,PDI6225MG_300,TIM5,20);
    ServoSetRange(&Servo1,5,60);
    ServoSetAngle(&Servo1,30);
    while(1)
    {
        MoveRectangle(1.0);
    }
}
*/

/*!
*   @brief LESSON_6
*       @note [RCR:LESSONS6] parsing data from sensors
*/

/*
int main(void)
{
    Board_Config;
    ADC_Init(ADC1);
    while(1)
    {
        AnalogReadInjected(ADC1);
    }
}
*/
