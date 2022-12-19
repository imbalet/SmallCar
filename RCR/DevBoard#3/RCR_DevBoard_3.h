#pragma once

/////////////////////////////////////////////////////////////////////////////
//________________________________BTN PWM__________________________________//
/////////////////////////////////////////////////////////////////////////////
#define BTN1_PWM_PIN            GPIOPinID(PORTA,9)         // Wheels
#define BTN2_PWM_PIN            GPIOPinID(PORTA,8)         // Servo rotate

#define BTN1_CCR                ((uint32_t *)&(TIM1->CCR1))
#define BTN2_CCR                ((uint32_t *)&(TIM1->CCR2))
/////////////////////////////////////////////////////////////////////////////
//_____________________________BTN directions______________________________//
/////////////////////////////////////////////////////////////////////////////
#define BTN1_DIR_PIN            GPIOPinID(PORTB,14)        // Wheels direction
#define BTN2_DIR_PIN            GPIOPinID(PORTB,15)        // NONE
/////////////////////////////////////////////////////////////////////////////
//________________________________Encoders_________________________________//
/////////////////////////////////////////////////////////////////////////////
#define ENCODER1A_PIN           GPIOPinID(PORTA,0)
#define ENCODER1B_PIN           GPIOPinID(PORTA,1)
#define ENCODER2A_PIN           GPIOPinID(PORTA,6)
#define ENCODER2B_PIN           GPIOPinID(PORTA,7)

#define ENCODER1_CNT           ((uint32_t *)&(TIM3->CNT))
#define ENCODER2_CNT           ((uint32_t *)&(TIM4->CNT))
/////////////////////////////////////////////////////////////////////////////
//_____________________________ADC_PIN_____________________________________//
/////////////////////////////////////////////////////////////////////////////
#define MULPLXA_PIN             GPIOPinID(PORTB,10)                //A channel
#define MULPLXB_PIN             GPIOPinID(PORTB,12)                //B channel
#define MULPLXC_PIN             GPIOPinID(PORTB,13)                //C channel
#define ADC_TOP                 GPIOPinID(PORTB,0)                 //ADC_TOP
#define ADC_BOTTOM              GPIOPinID(PORTB,1)                 //ADC_BOTTOM
#define POT_PIN                 GPIOPinID(PORTA,4)                 //POT
/////////////////////////////////////////////////////////////////////////////
//__________________________________USART__________________________________//
/////////////////////////////////////////////////////////////////////////////
//USART3 in stm32, USART1 as PCB header. AF7
#define TX1_PIN                  GPIOPinID(PORTA,9)
#define RX1_PIN                  GPIOPinID(PORTA,10)
//USART1 in stm32, USART2 as PCB header. AF7
#define TX3_PIN                  GPIOPinID(PORTA,2)
#define RX3_PIN                  GPIOPinID(PORTA,3)
/////////////////////////////////////////////////////////////////////////////
//____________________________External interrupts__________________________//
/////////////////////////////////////////////////////////////////////////////
#define EXTI1_PIN               GPIOPinID(PORTB,2)
#define EXTI2_PIN               GPIOPinID(PORTB,3)
#define EXTI3_PIN               GPIOPinID(PORTB,4)
#define EXTI4_PIN               GPIOPinID(PORTB,5)
#define EXTI5_PIN               GPIOPinID(PORTA,15)
/////////////////////////////////////////////////////////////////////////////
//________________________________I2C pins_________________________________//
/////////////////////////////////////////////////////////////////////////////
#define I2C_SDA_PIN             GPIOPinID(PORTB,9)                   //I2C_SDA//
#define I2C_SCL_PIN             GPIOPinID(PORTB,8)                   //I2C_SCL//
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
//________________________________USB/CAN pins_____________________________//
/////////////////////////////////////////////////////////////////////////////
#define USBP_PIN                GPIOPinID(PORTA,12)
#define USBN_PIN                GPIOPinID(PORTA,11)
/////////////////////////////////////////////////////////////////////////////
//_________________________________Other Pins______________________________//
/////////////////////////////////////////////////////////////////////////////
#define INT_PIN	                GPIOPinID(PORTA,5)
#define LED2_PIN                GPIOPinID(PORTA,10)
#define LED1_PIN                GPIOPinID(PORTC,13)
/////////////////////////////////////////////////////////////////////////////
