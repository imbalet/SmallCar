#include "main.h"
#include "TCS3472.h"
#include "ssd1306.h"
#include "functions.h"
#include "OLED.h"
#include "fonts.c"
#include <math.h>




////////////////////////////////////////////////////////
extern uint8_t work;
//extern float rast[];
extern bool cubeflag, mazeflag;
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



float dist[2];



uint16_t b,g;
int h;

#define ADDRESS     0x29
#define RESULT_RANGE_STATUS     0x1E
uint8_t VL53L0_Connect(void);


static uint32_t timeout;


void writeReg(uint8_t reg, uint8_t value){
    I2C_MemoryWriteSingle(I2C1,ADDRESS, reg, value);
}



int main(void){
    float distance;
      uint32_t timer=0;
    config();


    while(1){

        checkWays();

        if(work)
            {
                read(8);
            checkWays();



            leftHand();



            //cubeREG();
            if (mazeflag){
                checkWays();
                //leftHand();
            }
            else{
                //preg();
            }




            SetPin(LED_PIN);




            if (globalTime-timer>=500){
                timer=globalTime;
                TCS3472_GetRGB();
                }





            if(cubeflag){
                cube();
                cubeflag=0;
                }
        }
}    }



