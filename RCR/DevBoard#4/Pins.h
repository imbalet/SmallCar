#pragma once

#define LED_PIN          GPIOPinID(PORTC,13)

#define PWM1_PIN         GPIOPinID(PORTA,8)
#define PWM2_PIN         GPIOPinID(PORTA,9)

#define PWM1_CCR        ((uint32_t *)&(TIM1->CCR1))
#define PWM2_CCR        ((uint32_t *)&(TIM1->CCR2))

#define DIR1_PIN         GPIOPinID(PORTA,10)
#define DIR2_PIN         GPIOPinID(PORTA,11)
#define DIR3_PIN         GPIOPinID(PORTA,7)
#define DIR4_PIN         GPIOPinID(PORTA,6)


#define SENSOR1_PIN     GPIOPinID(PORTA,0)
#define SENSOR2_PIN     GPIOPinID(PORTA,1)

