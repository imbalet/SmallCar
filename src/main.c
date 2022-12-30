#include "main.h"
#include "TCS3472.h"
#include "ssd1306.h"
#include "functions.h"
#include "OLED.h"
#include "fonts.c"
#include <math.h>
////////////////////////////////////////////////////////////
extern uint8_t work;
extern float rast[];
extern bool cubeflag;
extern float linS;

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

extern struct {
    bool leftW;
    bool rightW;
    bool forwardW;
    bool backW;
} ways;



float a;




int main(void){
    float distance;
    uint32_t timer=0;
    config();

    while(1){

        read(8);
        if(work)
            {
            checkWays();


            SetPin(LED_PIN);


            distance = (float)sens.top[0] * 0.0008058608;
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


