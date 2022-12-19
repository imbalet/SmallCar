#include "OLED.h"
#include "TCS3472.h"

void intstooled(uint16_t data[],int len){
    SSD1306_Fill(SSD1306_COLOR_BLACK);
    int y=20;
    for(int i=0; i<len; i++){
        int lenint=0;
        int temp=data[i];
        while(temp!=0){
            temp=temp/10;
            lenint++;
        }
        char ch[lenint];
        temp=data[i];
        for (int j=0; j<lenint; j++){
            int val=temp%10+48;
            ch[lenint-1-j]=val;
            temp=temp/10;
        }

        SSD1306_GotoXY(0,y);
        SSD1306_Puts(ch, &Font_7x10 , SSD1306_COLOR_WHITE);
        y+=12;
    }
    SSD1306_UpdateScreen();
}
void draw(){

SSD1306_Fill(SSD1306_COLOR_BLACK);
ssd1306_image(Sad_50x50, 50,50,0, 0);
SSD1306_UpdateScreen();
}

void writeint(int y, int data){
    int len=0;
    int data1=data;
    char cdata[len];
    while(data!=0){
    data=data/10;
    len++;
    }
    for(int i=0;i<4;i++){
        cdata[len-1-i]=('0'+data1%10);
        data1=data1/10;
        }
        SSD1306_Fill(SSD1306_COLOR_BLACK);

        SSD1306_GotoXY(0,y);
        SSD1306_Puts(cdata, &Font_11x18, SSD1306_COLOR_WHITE);
        SSD1306_UpdateScreen();
}
//void checkcolor(){
//    if ((TCS3472.RGB[2])>100){
//        SSD1306_Fill(SSD1306_COLOR_BLACK);
//        SSD1306_GotoXY(0,22);
//        SSD1306_Puts("blue", &Font_11x18, SSD1306_COLOR_WHITE);
//        SSD1306_UpdateScreen();
//    }
//    else if ((TCS3472.RGB[1])>88){
//        if ((TCS3472.RGB[0])>90){
//            SSD1306_Fill(SSD1306_COLOR_BLACK);
//            SSD1306_GotoXY(0,22);
//            SSD1306_Puts("yellow", &Font_11x18, SSD1306_COLOR_WHITE);
//            SSD1306_UpdateScreen();
//        }
//        else{
//            SSD1306_Fill(SSD1306_COLOR_BLACK);
//            SSD1306_GotoXY(0,22);
//            SSD1306_Puts("green", &Font_11x18, SSD1306_COLOR_WHITE);
//            SSD1306_UpdateScreen();
//        }
//
//    }
//    else if ((TCS3472.RGB[0])>100){
//            SSD1306_Fill(SSD1306_COLOR_BLACK);
//            SSD1306_GotoXY(0,22);
//            SSD1306_Puts("red", &Font_11x18, SSD1306_COLOR_WHITE);
//            SSD1306_UpdateScreen();
//    }
//     else if (((TCS3472.RGB[0])>100) || ((TCS3472.RGB[1])>100) || ((TCS3472.RGB[2])>100) ){
//            SSD1306_Fill(SSD1306_COLOR_BLACK);
//            SSD1306_GotoXY(0,22);
//            SSD1306_Puts("white", &Font_11x18, SSD1306_COLOR_WHITE);
//            SSD1306_UpdateScreen();
//     }
//
//
//}
