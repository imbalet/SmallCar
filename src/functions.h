#include "main.h"
#include "ssd1306.h"

void read(int num);
void TIM2_IRQHandler(void);
void config(void);
void SetSpeed(float Dutyr, bool motor);
void EXTI2_IRQHandler(void);
void PID(void);
void PID_Calc(int number);
void TIM4_IRQHandler(void);
void godistance(float dist);
void cube(void);
void rotatePlatform(float dec);
void checkWays(void);
void leftHand(void);
