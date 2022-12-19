#include "main.h"
#include "TCS3472.h"
#include "ssd1306.h"
#include "functions.h"
#include "OLED.h"
#include "fonts.c"
#include <math.h>


float sharp = 0.0008058608;
extern time;
extern work;
extern rast[];
extern goal;
extern cubeflag;
extern struct{
uint16_t top[3];

uint16_t bottom[8];
}sens;
extern struct
{
float Pk;
float Ik;
float Dk;
float Max_output;
float Min_output;
float Max_sum_error;
float output;
float current;
float target;
float error;
float prev_error;
float sum_error;
}PIDstruct;//left
extern linS;

///////////////////////////////////////////////////////

    //SSD1306_Fill(SSD1306_COLOR_BLACK);
//    ssd1306_image(logo_RCR_20x20, 64,128,0, 0);
//    SSD1306_GotoXY(0,44);
//    SSD1306_Puts("ggggg", &Font_11x18 , SSD1306_COLOR_WHITE);
//    SSD1306_DrawCircle(10,33,7,SSD1306_COLOR_WHITE);
 //   SSD1306_UpdateScreen();
//    draw();
//        TCS3472_GetRGB();
//        read(1,0);
//        read(1,1);

//        ADC1_Data[0]=ADC1->DR;
//        ADC1_Data[1]=ADC1->JDR1;


//        SetSpeed(0.3,1);
//        SetSpeed(0.3,0);
//        read(2,1);
//        read(2,0);
/////////////////////////////////////////////////////

uint8_t data = 0;
int c=8;
float distance;
float a;
int main(void){
    uint32_t timer=0;
    config();

TCS3472_GetRGB();
    while(1){
        read(c);
        if(work)
            {
            SetPin(LED_PIN);
            distance = sens.top[1] * sharp;
            a = 29.988*powf(distance, -1.173);
            if (globalTime-timer>=500){
                timer=globalTime;
                TCS3472_GetRGB();

            }
            if(cubeflag){
                cube();
                cubeflag=0;
                }
        }
    }
}


