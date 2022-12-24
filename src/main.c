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
typedef struct
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
    }Regulator;

extern Regulator PIDstruct[2];

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

struct {
    bool leftW;
    bool rightW;
    bool forwardW;
    bool backW;
} ways;


int main(void){
    uint32_t timer=0;
    config();

TCS3472_GetRGB();

//godistance(0.3);
//rotatePlatform(90.0);
//godistance(0.4);
//rotatePlatform(270.0);
//godistance(0.5);
    while(1){

        read(c);
        if(work)
            {
            ways.backW=false;
            ways.forwardW=false;
            ways.leftW=false;
            ways.rightW=false;

            if (sens.top[1]<2000){ways.leftW=true;}
            else if (sens.top[2]<2000){ways.rightW=true;}
            else if (a>=20){ways.forwardW=true;}

            if (ways.leftW) rotatePlatform(90);
            else if (ways.rightW) rotatePlatform(270);
            else if (!ways.leftW && !ways.rightW && !ways.forwardW) rotatePlatform(180);


            godistance(0.3);


//            ways.backW=false;
//            ways.forwardW=false;
//            ways.leftW=false;
//            ways.rightW=false;
//            if (sens.top[1]<2000){ways.leftW=true;}
//            else if (sens.top[2]<2000){ways.rightW=true;}
//            else if (a>=20){ways.forwardW=true;}



//            if (ways.leftW) rotatePlatform(90);
//            else if (ways.rightW) rotatePlatform(270);






//            if (sens.top[1]<2500 && a<=10.5){
//                rotatePlatform(90);
//            }
//            else if (sens.top[2]<2500 && a<=10.5){
//                rotatePlatform(270);
//            }
//            else {
//                PIDstruct[1].target=0.03;
//                PIDstruct[0].target=0.03;
//            }

            read(0);
            read(2);
            read(6);

            SetPin(LED_PIN);
            distance = sens.top[0] * sharp;
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


