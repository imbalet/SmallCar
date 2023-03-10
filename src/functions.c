#define R                  0.02//?????? ??????

#define length             0.1256628
#define baseDiscrets       4100.0//??????? ???????? ?? 360*
#define LenCircle           0.34


#include "TCS3472.h"
#include "functions.h"
#include "OLED.h"
extern float dist[2];

uint8_t work=0;

struct{
uint16_t top[4];
uint16_t bottom[8];
}sens;
float distance;
void read(int num){//0-7 sensors, 8-all
        if(num<=7){
            ResetPin(MULPLXA_PIN);
            ResetPin(MULPLXB_PIN);
            ResetPin(MULPLXC_PIN);
            if(((num >> 2)&(0x1)) == 1) SetPin(MULPLXC_PIN);
            if(((num >> 1)&(0x1)) == 1) SetPin(MULPLXB_PIN);
            if(num&0x1) SetPin(MULPLXA_PIN);
            delay_ms(2);
            sens.bottom[num]=ADC1_Data[1];

            switch(num){
                case(0):
                    sens.top[0]=ADC1_Data[0];
                    break;
                case(5):
                    sens.top[1]=(ADC1_Data[0]);
                    break;
                case(6):
                    sens.top[2]=(ADC1_Data[0]);
                    break;
                case(4):
                    sens.top[3]=(ADC1_Data[0]);
                    break;
                }
        }
        else{
            for (int i=0;i<=7;i++){
                read(i);
                delay_ms(2);
                }
        }
            distance = (float)sens.top[1] * 0.0008058608;
            dist[0] = 29.988*powf(distance, -1.173);


            distance = (float)sens.top[0] * 0.0008058608;
            dist[1]= 29.988*powf(distance, -1.173);
}

int16_t EncoderData[2];
float uglS[2], linS[2], speed[2];

void config() {
    Board_Config;

    TIM3->CNT = 0;
    TIM5->CNT = 0;

    ADCAddChannel(8,REGULAR,ADC_480_CYCLES);
    ADCAddChannel(9,REGULAR,ADC_480_CYCLES);
    ConnectADCTODMA(HIGH_P, ADC1_Data, 0);
    ADC_Init();

    I2CSimpleConfigure(I2C1, I2C_Fast);
    TCS3472_Init();
    SSD1306_Init();

    PID();

    NVIC_EnableIRQ(TIM2_IRQn);
    NVIC_EnableIRQ(TIM4_IRQn);

    AddEXTIInterrupt(EXTI1_PIN,EXTI_RISING_EDGE);
    NVIC_EnableIRQ(EXTI2_IRQn);
    AddEXTIInterrupt(EXTI2_PIN,EXTI_RISING_EDGE);
    NVIC_EnableIRQ(EXTI3_IRQn);
    AddEXTIInterrupt(EXTI3_PIN,EXTI_RISING_EDGE);
    NVIC_EnableIRQ(EXTI4_IRQn);

    SSD1306_GotoXY(0,44);
    SSD1306_Puts("Kiborg ubiyca", &Font_7x10, SSD1306_COLOR_WHITE);
    SSD1306_UpdateScreen();

    TCS3472_GetRGB();
}

void SetSpeed(float Dutyr, bool motor){
    if (motor){
        if (Dutyr>=0){
            ResetPin(BTN2_DIR_PIN);
            SetPWM(TIM1,2,Dutyr);
        }
        else{
            SetPin(BTN2_DIR_PIN);
            SetPWM(TIM1,2,Dutyr);
        }
    }
    else{
        if (Dutyr>=0){
            ResetPin(BTN1_DIR_PIN);
            SetPWM(TIM1,1,Dutyr);
        }
        else{
            SetPin(BTN1_DIR_PIN);
            SetPWM(TIM1,1,Dutyr);
        }
    }
}

/////////////////////////////////////////////
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

Regulator PIDstruct[2];

void PID(void)
{
PIDstruct[0].Pk = 6;
PIDstruct[0].Ik = 0.15;
PIDstruct[0].Dk = 0.2;
PIDstruct[0].current = 0.0;
PIDstruct[0].target = 0.0;
PIDstruct[0].error = 0.0;
PIDstruct[0].Max_output = 1.0;
PIDstruct[0].Min_output = 0.18;
PIDstruct[0].Max_sum_error = 5.0;
PIDstruct[0].prev_error = 0.0;
PIDstruct[0].sum_error = 0.0;

PIDstruct[1].Pk = 6;
PIDstruct[1].Ik = 0.15;
PIDstruct[1].Dk = 0.2;
PIDstruct[1].current = 0.0;
PIDstruct[1].target = 0.0;
PIDstruct[1].error = 0.0;
PIDstruct[1].Max_output = 1.0;
PIDstruct[1].Min_output = 0.18;
PIDstruct[1].Max_sum_error = 5.0;
PIDstruct[1].prev_error = 0.0;
PIDstruct[1].sum_error = 0.0;
}


void PID_Calc(int number)
{
    float p=0.0,i=0.0,dp = 0.0;
    PIDstruct[number].error = PIDstruct[number].target - PIDstruct[number].current;
    PIDstruct[number].sum_error += PIDstruct[number].error;
    if(PIDstruct[number].sum_error > PIDstruct[number].Max_sum_error) PIDstruct[number].sum_error = PIDstruct[number].Max_sum_error;
    if(PIDstruct[number].sum_error < -PIDstruct[number].Max_sum_error) PIDstruct[number].sum_error = -PIDstruct[number].Max_sum_error;
    p=PIDstruct[number].Pk * PIDstruct[number].error;
    i=PIDstruct[number].Ik * PIDstruct[number].sum_error;
    dp=PIDstruct[number].Dk * PIDstruct[number].prev_error;
    PIDstruct[number].output = (p) + (i) + (dp);
    if(PIDstruct[number].output < PIDstruct[number].Min_output &&
       PIDstruct[number].output > -PIDstruct[number].Min_output) PIDstruct[number].output = 0.0000;

    if(PIDstruct[number].output < -PIDstruct[number].Max_output) PIDstruct[number].output = -1.0;
    if(PIDstruct[number].output > PIDstruct[number].Max_output) PIDstruct[number].output = 1.0;
    PIDstruct[number].prev_error = PIDstruct[number].error;
}


void checkcolor(){
    if ((TCS3472.RGB[2])>100){
        SSD1306_Fill(SSD1306_COLOR_BLACK);
        SSD1306_GotoXY(0,22);
        SSD1306_Puts("blue", &Font_11x18, SSD1306_COLOR_WHITE);
        SSD1306_UpdateScreen();
        TCS3472.color=1;
    }
    else if ((TCS3472.RGB[1])>88){
        if ((TCS3472.RGB[0])>90){
            SSD1306_Fill(SSD1306_COLOR_BLACK);
            SSD1306_GotoXY(0,22);
            SSD1306_Puts("yellow", &Font_11x18, SSD1306_COLOR_WHITE);
            SSD1306_UpdateScreen();
            TCS3472.color=2;
        }
        else{
            SSD1306_Fill(SSD1306_COLOR_BLACK);
            SSD1306_GotoXY(0,22);
            SSD1306_Puts("green", &Font_11x18, SSD1306_COLOR_WHITE);
            SSD1306_UpdateScreen();
            TCS3472.color=2;
        }

    }
    else if ((TCS3472.RGB[0])>100){
            SSD1306_Fill(SSD1306_COLOR_BLACK);
            SSD1306_GotoXY(0,22);
            SSD1306_Puts("red", &Font_11x18, SSD1306_COLOR_WHITE);
            SSD1306_UpdateScreen();
            TCS3472.color=4;
    }
     else if (((TCS3472.RGB[0])>100) || ((TCS3472.RGB[1])>100) || ((TCS3472.RGB[2])>100) ){
            SSD1306_Fill(SSD1306_COLOR_BLACK);
            SSD1306_GotoXY(0,22);
            SSD1306_Puts("white", &Font_11x18, SSD1306_COLOR_WHITE);
            SSD1306_UpdateScreen();
     }


}




void cube(){
    checkcolor();
    switch(TCS3472.color){
        case(1):
            godistance(0.25);
            break;
        case(2):
            godistance(0.15);
            break;
        case(3):
            godistance(0);
            break;
        case(4):
            godistance(0.4);
            break;
    }
    rotatePlatform(180);
}





////////////////////////////////////////////////////

void TIM4_IRQHandler(void)
{
PIDstruct[0].current= -speed[0];
PIDstruct[1].current= speed[1];
PID_Calc(0);
PID_Calc(1);
SetSpeed((PIDstruct[0].output),0);
SetSpeed((PIDstruct[1].output),1);


ResetTimSR(TIM4);
}
int lens;

int myint;
int baseint=0;
uint8_t confirmK;
void EXTI2_IRQHandler(void)
{
    confirmK=0;
    myint++;
    baseint=0;
    switch(myint){
        case(1):
            baseint=123;
            break;
        case(2):
            baseint=213;
            break;
        case(3):
            baseint=214;
            break;
        case(4):
            baseint=234;
            break;
        case(5):
            baseint=341;
            break;
        case(6):
            baseint=342;
            break;
        case(7):
            baseint=412;
            break;
        case(8):
            baseint=413;
            myint=0;
            break;

    }
    writeint(0, baseint);
    EXTI->PR=0x4;
}

int NUMBER=0;
void EXTI3_IRQHandler(void)
{
    confirmK++;
    if (confirmK==3) {
        work=1;
        confirmK=0;
        NVIC_DisableIRQ(EXTI2_IRQn);
        NVIC_EnableIRQ(TIM2_IRQn);
        NVIC_EnableIRQ(TIM4_IRQn);
        NUMBER=baseint;
    }
  EXTI->PR=0x8;
}

bool cubeflag=0;
void EXTI4_IRQHandler(void)
{
    cubeflag=1;
    EXTI->PR=0x10;
}



float rast[3];

void TIM2_IRQHandler(void){
    EncoderData[0] = TIM5->CNT;
    EncoderData[1] = TIM3->CNT;

    uglS[0] = ((float)EncoderData[0] * 360.0) / baseDiscrets;
    uglS[1] = ((float)EncoderData[1] * 360.0) / baseDiscrets;
    linS[0] = (uglS[0] * (float)length) / 360.0;
    linS[1] = (uglS[1] * (float)length) / 360.0;
    speed[0] = linS[0] * 10;
    speed[1] = linS[1] * 10;
    rast[0]=-linS[0]*1.11+rast[0];
    rast[1]=linS[1]*1.11+rast[1];
    rast[2]=rast[0]/2+rast[1]/2;

    TIM3->CNT = 0;
    TIM5->CNT= 0;

    ResetTimSR(TIM2);

}
/////////////////////////////////////////////////////////////////////////////
void godistance(float dist){
    rast[0]=0.0;
    rast[1]=0.0;

    while(((rast[0]+rast[1])/2)<(dist)){
    PIDstruct[0].target = 0.03;
    PIDstruct[1].target = 0.03;

    }
    PIDstruct[0].target = 0.0;
    PIDstruct[1].target = 0.0;
    rast[0]=0.0;
}


void rotatePlatform(float deg){
    float RotateDistance=0;
    rast[0]=0;
    rast[1]=0;

    if (deg>=180){
        deg=360-deg;
        RotateDistance=((float)(deg/360.0)*(LenCircle));
        while ((rast[1])<RotateDistance){
            PIDstruct[1].target=0.02;
            PIDstruct[0].target=-0.02;
        }

    }
    else{
        RotateDistance=((float)(deg/360.0)*(LenCircle));
        while ((rast[0])<RotateDistance){
            PIDstruct[0].target=0.03;
            PIDstruct[1].target=-0.03;
        }
    }
    PIDstruct[0].target=0;
    PIDstruct[1].target=0;
    rast[0]=0;
    rast[1]=0;

}

struct {
    bool leftW;
    bool rightW;
    bool forwardW;
    bool backW;
} ways;

void checkWays(){
    read(0);
    read(2);
    read(6);
    read(8);

    ways.backW=false;
    ways.forwardW=false;
    ways.leftW=false;
    ways.rightW=false;

    if (sens.top[1]<1700){ways.leftW=true;}
    if (sens.top[2]<2000){ways.rightW=true;}
    if (sens.top[0]<2000){ways.forwardW=true;}
    if (sens.top[3]<2000){ways.backW=true;}
}

void leftHand(){
    if (ways.leftW){
        rotatePlatform(95);
        checkWays();
        if (!ways.leftW){
                wallREG(0.15);
        }
        else{
                godistance(0.15);
        }
        checkWays();
       godistance(0.15);
       }
    else if (ways.forwardW){
        checkWays();
        if (!ways.leftW){wallREG(0.15);}
        else{godistance(0.15);}
        checkWays();
       godistance(0.15);}
    else if (ways.rightW){
            rotatePlatform(270);
            checkWays();
        if (!ways.leftW){wallREG(0.15);}
        else{godistance(0.15);}
        checkWays();
       godistance(0.15);}

//    else if (ways.rightW){
//        rotatePlatform(255);
//        delay_ms(100);
//        }
    else if (ways.backW){
            rotatePlatform(180);
        rotatePlatform(342);
          checkWays();
        if (!ways.leftW){wallREG(0.15);}
        else{godistance(0.15);}
        checkWays();
       godistance(0.15);}
    }

struct{
int leftsens, rightsens, error, defaultValue;
float pk, outputL,outputR, defaultspeed;
}cubREGstruct;

void cubREGinit(){
    cubREGstruct.pk=0.000000000034625;
    cubREGstruct.defaultValue=0;
    cubREGstruct.defaultspeed=0.3;

}


void cubeREG(){
    cubREGstruct.leftsens =((int)sens.bottom[1]);
    if (cubREGstruct.leftsens>4095) cubREGstruct.leftsens=4095;
    cubREGstruct.rightsens=(int)sens.bottom[3];
    cubREGstruct.error=cubREGstruct.rightsens-cubREGstruct.leftsens + ((sens.bottom[4]-sens.bottom[0])*0.7);

    cubREGstruct.outputR=cubREGstruct.defaultspeed+(cubREGstruct.pk)*cubREGstruct.error*cubREGstruct.error*cubREGstruct.error;
    cubREGstruct.outputL=cubREGstruct.defaultspeed+(-cubREGstruct.pk)*cubREGstruct.error*cubREGstruct.error*cubREGstruct.error;
    if (sens.bottom[2]<4096){
        SetSpeed(cubREGstruct.outputL,1);
        SetSpeed(cubREGstruct.outputR,0);

    }
    else {
        SetSpeed(0,0);
        SetSpeed(0,1);

    }
}

struct{
int error;
float kp;
float lspeed;
float rspeed;
}pregStruct;

bool mazeflag=0;
void preg(){
//    checkcolor();
    pregStruct.kp=0.0000025;
    pregStruct.error = sens.bottom[1] - sens.bottom[3];
    pregStruct.lspeed = pregStruct.error*pregStruct.kp + 0.03;
    pregStruct.rspeed = pregStruct.error*(-pregStruct.kp) + 0.03;
//    SetSpeed(pregStruct.lspeed,1);
//    SetSpeed(pregStruct.rspeed,0);

    PIDstruct[1].target=pregStruct.lspeed;
    PIDstruct[0].target=pregStruct.rspeed;



    if (sens.bottom[0]<3500 ){
        godistance(0.05);
        rotatePlatform(90);
    }
    else if(sens.bottom[0]<3500 && sens.bottom[4]<3500|| sens.bottom[4]<3500){
        godistance(0.2);
        read(8);

        if (sens.bottom[2]==4095 && sens.bottom[1]==4095 && sens.bottom[3]==4095){
            //godistance(0.15);
            rotatePlatform(180);
        }
    }

    read(8);
    if (sens.bottom[0]==4095 && sens.bottom[1]==4095 && sens.bottom[2]==4095 && sens.bottom[3]==4095 && sens.bottom[4]==4095){
         if (sens.top[0]>1600 || sens.top[1]>1600 || sens.top[2]>1600){
            mazeflag=1;
         }
    }
//    if (sens.bottom[0]==4095 && sens.bottom[1]==4095 && sens.bottom[2]==4095 && sens.bottom[3]==4095 && sens.bottom[4]==4095){rotatePlatform(270);}


//    if (sens.bottom[0]>3900 && sens.bottom[1]>3900 && sens.bottom[2]>3900 && sens.bottom[3]>3900 && sens.bottom[4]>3900){
//        if (sens.bottom[0]==4095 && sens.bottom[1]==4095 && sens.bottom[2]==4095 && sens.bottom[3]==4095 && sens.bottom[4]==4095){
//            godistance(0.2);
//            rotatePlatform(270);
//            if (sens.bottom[0]==4095 && sens.bottom[1]==4095 && sens.bottom[2]==4095 && sens.bottom[3]==4095 && sens.bottom[4]==4095) rotatePlatform(270);
//        }
//    }
//    if (sens.bottom[4]<3500){
//        rotatePlatform(270);
//    }
//


}







float distance, prevrast=0;

float wallK = 0.0032857,walld=0.03, wallerr = 0, wallpreverr=1;
bool iswall;
void wallREG (float distance1){


    rast[0]=0.0;
    prevrast=0;
    rast[1]=0.0;




    while((rast[2])<(distance1)){
            read(8);
    checkWays();
//
//    if (ways.leftW){
//            godistance(0.15);
//        rotatePlatform(98);
//        godistance(0.15);
//    }
//            if (11.8-dist[0]-wallpreverr>1.8){iswall=false; }
//                else{iswall=true;}
//            if (rast[2]-prevrast>0.01){
//                if (dist[0]>18){iswall=false; delay_ms(100);}
//                else{iswall=true;}
//                prevrast=rast[2];
//            }





            if(1){






        read(8);



//            if (dist[0]>18){iswall=false;}

    float wallerr=12.0-dist[0];
    if ((wallpreverr-wallerr)>1.0 ||(wallpreverr-wallerr)<(-1.0) ){
                PIDstruct[0].target=0.03;
        PIDstruct[1].target=0.03;
    }
    else{
        PIDstruct[0].target=wallerr*(-wallK)+0.03 - (wallpreverr-wallerr)*(-walld);
        PIDstruct[1].target=wallerr*wallK+0.03 - (wallpreverr-wallerr)*walld;
    }
    if ((wallerr*(-wallK)+0.03 - (wallpreverr-wallerr)*(-walld))>0.15) {PIDstruct[0].target=0.05;}
    if ((wallerr*(-wallK)+0.03 - (wallpreverr-wallerr)*(-walld))<(-0.1)) {PIDstruct[0].target=(-0.05);}


    wallpreverr=wallerr;
    prevrast=rast[2];


    }
    else{
         read(8);

//            distance = (float)sens.top[1] * 0.0008058608;
//            dist[0] = 29.988*powf(distance, -1.173);
//
//
//            distance = (float)sens.top[0] * 0.0008058608;
//            dist[1]= 29.988*powf(distance, -1.173);

        PIDstruct[0].target=0.03;
        PIDstruct[1].target=0.03;
        //delay_ms(1000);

    }


    }
        PIDstruct[0].target = 0.0;
        PIDstruct[1].target = 0.0;
//        rast[0]=0.0;
//        rast[1]=0.0;
//        rast[2]=0.0;




}
