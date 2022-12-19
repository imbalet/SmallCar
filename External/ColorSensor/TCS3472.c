#include "TCS3472.h"
#define TCS3472_Reconnect_it        (100)
static uint32_t TCS3472_timeout;

bool TCS3472_Init(void)
{
    TCS3472.Source = __configTCS3472_SOURCE;
    /// Restore bad connection
    if(I2CBusBusyEvent(TCS3472.Source))
    {
        I2C_RestoreConnection(TCS3472.Source);
        I2CSimpleConfigure(TCS3472.Source,I2C_Fast);
    }
    #if(CALC_I2C_SCANNING == 1)
    TCS3472.status = 3;
    #endif/*CALC_I2C_SCANNING*/
    bool IsTCS3472 = TCS3472_Connect();
    if(!IsTCS3472) return false;
    #if(CALC_I2C_SCANNING == 1)
    TCS3472.status = 2;
    #endif/*CALC_I2C_SCANNING*/
    uint8_t Data;
    Data = I2C_MemoryReadSingle(TCS3472.Source,TCS3472_I2C,0x92);
    if(Data != TCS34723_ID && Data != TCS34721_ID &&
       Data != TCS34725_ID && Data != TCS34727_ID)  return false;
    #if(CALC_I2C_SCANNING == 1)
    TCS3472.status = 1;
    #endif/*CALC_I2C_SCANNING*/
    /// Set Properties
    delay_ms(2);
    IsTCS3472 = TCS3472_SetProperties(__configTCS3472_Gain, __configTCS3472_IntegrationTime, __configTCS3472_WaitTime);
    if(!IsTCS3472) return false;
    #if(CALC_I2C_SCANNING == 1)
    TCS3472.status = 0;
    #endif/*CALC_I2C_SCANNING*/
return true;
}

static bool TCS3472_ON(void)
{
    uint8_t Data;
    /// Activate internal oscillator
    Data = I2C_MemoryWriteSingle(TCS3472.Source,TCS3472_I2C,TCS3472_ENABLE,0x01);
    if(Data != 0x01) return false;
    delay_ms(3);
    /// Activate RGBC
    Data = I2C_MemoryWriteSingle(TCS3472.Source,TCS3472_I2C,TCS3472_ENABLE,(0x03));
    if(Data != (0x03)) return false;
      switch (__configTCS3472_IntegrationTime)
      {
          case 0xFF:
            delay_ms(3);
            break;
          case 0xF6:
            delay_ms(24);
            break;
          case 0xD5:
            delay_ms(101);
            break;
          case 0xC0:
            delay_ms(154);
            break;
          case 0x00:
            delay_ms(700);
            break;
      }
    return true;
}

static bool TCS3472_OFF(void)
{
    uint8_t Data;
    Data = I2C_MemoryReadSingle(TCS3472.Source,TCS3472_I2C,TCS3472_ENABLE);
    Data &= ~((uint8_t)0x3);

    Data = I2C_MemoryWriteSingle(TCS3472.Source,TCS3472_I2C,TCS3472_ENABLE,Data);
    if( (Data&0x03) == 0x03) return false;
    return true;
}

bool TCS3472_CalculateLux(void)
{
    float Illuminance;
    /* This only uses RGB ... how can we integrate clear or calculate lux */
    /* based exclusively on clear since this might be more reliable?      */
    Illuminance = (-0.32466F * TCS3472.RGB[0]) + (1.57837F * TCS3472.RGB[1]) + (-0.73191F * TCS3472.RGB[2]);
    TCS3472.Illuminance = Illuminance;
    return true;
}

bool TCS3472_CalculateColorTemperatureKelvin(void)
{
    float X, Y, Z; /* RGB to XYZ correlation      */
    float xc, yc;  /* Chromaticity co-ordinates   */
    double numb;       /* McCamy's formula            */
    float cct;
    if(TCS3472.RGB[0] == 0 && TCS3472.RGB[1] == 0 &&
       TCS3472.RGB[2] == 0) return false;
      /* 1. Map RGB values to their XYZ counterparts.    */
      /* Based on 6500K fluorescent, 3000K fluorescent   */
      /* and 60W incandescent values for a wide range.   */
      /* Note: Y = Illuminance or lux                    */
      X = (-0.14282F * TCS3472.RGB[0]) + (1.54924F * TCS3472.RGB[1]) + (-0.95641F * TCS3472.RGB[2]);
      Y = (-0.32466F * TCS3472.RGB[0]) + (1.57837F * TCS3472.RGB[1]) + (-0.73191F * TCS3472.RGB[2]);
      Z = (-0.68202F * TCS3472.RGB[0]) + (0.77073F * TCS3472.RGB[1]) + (0.56332F * TCS3472.RGB[2]);
      /* 2. Calculate the chromaticity co-ordinates      */
      xc = (X) / (X + Y + Z);
      yc = (Y) / (X + Y + Z);
      /* 3. Use McCamy's formula to determine the CCT    */
      numb = (xc - 0.3320F) / (0.1858F - yc);
      /* Calculate the final CCT */
      cct =
          (449.0F * (numb * numb * numb)) + (3525.0F * (numb * numb)) + (6823.3F * numb) + 5520.33F;
      /* Return the results in degrees Kelvin */
      TCS3472.ColorTemperature = (uint16_t)cct;
    return true;
}

bool TCS3472_GetRGB(void)
{
    uint16_t red,green,blue,clear;
    TCS3472_GetRawData();
    clear = (TCS3472.RawData[1] << 8) | TCS3472.RawData[0];
    red =   (TCS3472.RawData[3] << 8) | TCS3472.RawData[2];
    green = (TCS3472.RawData[5] << 8) | TCS3472.RawData[4];
    blue =  (TCS3472.RawData[7] << 8) | TCS3472.RawData[6];
    TCS3472.RGB[0] = (float)red / (uint32_t)clear * 255.0;
    TCS3472.RGB[1] = (float)green / (uint32_t)clear * 255.0;
    TCS3472.RGB[2] = (float)blue / (uint32_t)clear * 255.0;
return true;
}

bool TCS3472_GetRawData(void)
{
    bool state;
    state = TCS3472_ON();
    delay_ms(2);
    if(!state) return false;
    uint8_t Length;
    Length = I2C_MemoryReadMultiple(TCS3472.Source,TCS3472_I2C,TCS3472_CLEAR,TCS3472.RawData,8);
    switch (__configTCS3472_IntegrationTime)
      {
          case 0xFF:
            delay_ms(3);
            break;
          case 0xF6:
            delay_ms(24);
            break;
          case 0xD5:
            delay_ms(101);
            break;
          case 0xC0:
            delay_ms(154);
            break;
          case 0x00:
            delay_ms(700);
            break;
      }
    TCS3472_OFF();
    return (Length == 8);
}

bool TCS3472_SetProperties(uint8_t Gain, uint8_t IntegrationTime, uint8_t WaitTime)
{
    uint8_t Data;
    Data = I2C_MemoryWriteSingle(TCS3472.Source,TCS3472_I2C,TCS3472_CONTROL,Gain);
    TCS3472.Gain = Data;
    if(Data != Gain) return false;

    Data = I2C_MemoryWriteSingle(TCS3472.Source,TCS3472_I2C,TCS3472_ATIME,IntegrationTime);
    TCS3472.IntegrationTime = Data;
    if(Data != IntegrationTime) return false;

    Data = I2C_MemoryWriteSingle(TCS3472.Source,TCS3472_I2C,TCS3472_WTIME,WaitTime);
    TCS3472.WaitTime = Data;
    if(Data != WaitTime) return false;
    return true;
}

bool TCS3472_SetGain(uint8_t Gain)
{
    uint8_t Data;
    Data = I2C_MemoryWriteSingle(TCS3472.Source,TCS3472_I2C,TCS3472_CONTROL,Gain);
    TCS3472.Gain = Data;
    if(Data != Gain) return false;
return true;
}

bool TCS3472_SetIntegrationTime(uint8_t IntegrationTime)
{
    uint8_t Data;
    Data = I2C_MemoryWriteSingle(TCS3472.Source,TCS3472_I2C,TCS3472_ATIME,IntegrationTime);
    TCS3472.IntegrationTime = Data;
    if(Data != IntegrationTime) return false;
return true;
}

bool TCS3472_SetWaitTime(uint8_t WaitTime)
{
    uint8_t Data;
    Data = I2C_MemoryWriteSingle(TCS3472.Source,TCS3472_I2C,TCS3472_WTIME,WaitTime);
    TCS3472.WaitTime = Data;
    if(Data != WaitTime) return false;
return true;
}

bool TCS3472_Connect(void)
{
    for(int i = 0; i < TCS3472_Reconnect_it; i++)
    {
        //Start BIT
        I2CStart(TCS3472.Source);
        TCS3472_timeout = __configI2C_TIMEOUT;
        while(!I2CStartBitEvent(TCS3472.Source))
        {
            TCS3472_timeout--;
            if(TCS3472_timeout == 0x00)
            break;
        }
        if(!I2CStartBitEvent(TCS3472.Source)) { I2CStop(TCS3472.Source); continue; }
        // Sending address
        SetI2CAsk(I2C1);
        I2CSendCommand(I2C1,(TCS3472_I2C << 1));
        while(I2CAddressSentEvent(TCS3472.Source))
        {
            TCS3472_timeout--;
            if(TCS3472_timeout == 0x00)
            break;
        }
        if(I2CAddressSentEvent(TCS3472.Source)) { I2CStop(TCS3472.Source); continue; }
        I2CStop(TCS3472.Source);
        return true;
    }
    return false;
}
