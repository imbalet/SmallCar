    /*!
    *   --------------------------------------------------------------------------
    *                ///ModBus source file\\\
    *   --------------------------------------------------------------------------
    *   @author RCR group developers
    *   @date 14/10/2022 - last update version ModBus
    *
    */
#include "ModBus_conf.h"
#if(__configEXT_ModBus == 1)
/*!
    @brief Code table of protocol ModBus RTU, ASCII and TCP/IP
        @code 0x01 (1) - чтение значений из нескольких регистров флагов - Read Coil Status.
        @code 0x02 (2) - чтение значений из нескольких дискретных входов - Read Discrete Inputs.
            @code 0x03 (3) - чтение значений из нескольких регистров хранени€ - Read Holding Registers.
        @code 0x04 (4) - чтение значений из нескольких регистров ввода - Read Input Registers.
        @code 0x05 (5) - запись значени€ одного флага - Force Single Coil.
            @code 0x06 (6) - запись значени€ в один регистр хранени€ - Preset Single Register.
        @code 0x07 (7) - чтение сигналов состо€ни€ - Read Exception Status.
            @code 0x08 (8) - диагностика - Diagnostic.
        @code 0x0B (11) - чтение счетчика событий - Get Com Event Counter.
        @code 0x0C (12) - чтение журнала событий - Get Com Event Log.
        @code 0x0F (15) - запись значений в несколько регистров флагов - Force Multiple Coils.
        @code 0x10 (16) - запись значений в несколько регистров хранени€ - Preset Multiple Registers.
        @code 0x11 (17) - чтение информации об устройстве - Report Slave ID.
        @code 0x14 (20) - чтение из файла - Read File Record.
        @code 0x15 (21) - запись в файл - Write File Record.
        @code 0x16 (22) - запись в один регистр хранени€ с использованием маски "»" и маски "»Ћ»" - Mask Write Register.
        @code 0x18 (24) - чтение данных из очереди - Read FIFO Queue.
        @code 0x2B (43) - Encapsulated Interface Transport.
*/

void ModBus_Handler(void)
{
    if(CheckUSARTReceiver(ModBus_Source) == 1 && !ModBus_BusyFlag)
    {
        if(UART_Buffer > (UART_EndMsgPointer + 1)) UART_Buffer = UART_StartMsgPointer;
        *UART_Buffer++ = GetUSARTDR(ModBus_Source);
    }
    if(ModBus_BusyFlag)
    {
        (void)GetUSARTDR(ModBus_Source);
    }
}

/*!
*   @brief Auto parser prototype (TIM4 default)
*/
#if (__configMODBUS_AUTOPARSE == 1)
void ModBus_TimIRQ(void)
{



}
#endif /* __configMODBUS_AUTOPARSE */

/*!
*   @brief ModBus_Init(void) - Initialize ModBus interface and allocate storage
*       @return nothing
*/
void ModBus_Init(void)
{
    /* Allocate buffer */
    UART_Buffer = (unsigned char *)malloc(STANDART_MODBUS_SIZE);

    /* Check allocation pointer */
    if(UART_Buffer == NULL) return;
    UART_CurrentIndexPointer = UART_Buffer;
    UART_StartMsgPointer = UART_Buffer;
    UART_AddressIndexPointer = UART_Buffer + 1;
    UART_FunctionIndexPointer = UART_Buffer + 3;
    UART_LRCIndexPointer = UART_Buffer + (STANDART_MODBUS_SIZE - 4);
    UART_EndMsgPointer = UART_Buffer + (STANDART_MODBUS_SIZE - 2);
    UART_DataIndexPointer = UART_Buffer + 5;
    ModBus_ClearMsgs();
    ModBus_BusyFlag = false;
}

/*!
*   @brief ModBus_Init(void) - Reinitialize ModBus protocol and recover indexes position
*       @return nothing
*/
void ModBus_ReInit(void)
{
    if(UART_Buffer == NULL) return;
    UART_CurrentIndexPointer = UART_Buffer;
    UART_StartMsgPointer = UART_Buffer;
    UART_AddressIndexPointer = UART_Buffer + 1;
    UART_FunctionIndexPointer = UART_Buffer + 3;
    UART_LRCIndexPointer = UART_Buffer + (STANDART_MODBUS_SIZE - 4);
    UART_EndMsgPointer = UART_Buffer + (STANDART_MODBUS_SIZE - 2);
    UART_DataIndexPointer = UART_Buffer + 5;
    ModBus_ClearMsgs();
}

/*!
*   @brief ModBus_CloseTransmission(void) - Close ModBus interface and delete storage
*       @return nothing
*/
void ModBus_CloseTransmission(void)
{
    ModBus_ClearMsgs();
    /* Deallocate buffer and storage pointer variables */
    free(UART_Buffer);
    free(UART_StartMsgPointer);
    free(UART_AddressIndexPointer);
    free(UART_FunctionIndexPointer);
    free(UART_CurrentIndexPointer);
    free(UART_LRCIndexPointer);
    free(UART_EndMsgPointer);
}

/*!
*   @brief ModBus_ClearMsgs(void) - Clear allocated storage for ModBus transmission
*       @return nothing
*/
void ModBus_ClearMsgs(void)
{
    UART_Buffer = UART_StartMsgPointer;
    for(int i = 0; i <= ((UART_EndMsgPointer + 2) - UART_StartMsgPointer); i++) *UART_Buffer++ = 0;
    UART_Buffer = UART_StartMsgPointer;
}

static void ModBus_HEX_TO_ASCII_ConverterU32(unsigned char *Storage, uint32_t Value)
{
    unsigned char ASCII;
    for(int i = 1; i < 8; i++)
    {
        ASCII = (unsigned char)(Value >> (28 - 4*i))&0xF;
        if( ASCII > 0x9) { ASCII -= 0xA; ASCII += 0x41; }
        if( ASCII >= 0x00 && ASCII <= 0x9) { ASCII += 0x30; }
        *Storage++ = ASCII;

    }
}

static void ModBus_HEX_TO_ASCII_ConverterU8(unsigned char *Storage, uint8_t Value)
{
    unsigned char ASCII;
    for(int i = 1; i < 2; i++)
    {
        ASCII = (unsigned char)(Value >> (28 - 4*i))&0xF;
        if( ASCII > 0x9) { ASCII -= 0xA; ASCII += 0x41; }
        if( ASCII >= 0x00 && ASCII <= 0x9) { ASCII += 0x30; }
        *Storage++ = ASCII;
    }
}

static void ModBus_HEX_TO_ASCII_ConverterU16(unsigned char *Storage, uint16_t Value)
{
    unsigned char ASCII;
    for(int i = 1; i < 4; i++)
    {
        ASCII = (unsigned char)(Value >> (28 - 4*i))&0xF;
        if( ASCII > 0x9) { ASCII -= 0xA; ASCII += 0x41; }
        if( ASCII >= 0x00 && ASCII <= 0x9) { ASCII += 0x30; }
        *Storage++ = ASCII;

    }
}

static unsigned int ModBus_ASCII_TO_HEX_Converter(unsigned char *ASCII_Pointer, unsigned short bsize)
{
    unsigned int HEX, i, Result;
    Result = 0; HEX = 0; i = 0;
    for(i = 1; i <= bsize; i++)
    {
        HEX = ((unsigned int)*(ASCII_Pointer + (i - 1)));
        if (((unsigned int)(HEX)) > '9') { HEX = (unsigned int)(HEX&0xF) + 9; }
        else { HEX &= 0xF;}
        Result |= (unsigned int) (HEX << (4 * (bsize - i)));
    }
    return Result;
}

/*!
*   @brief ModBus_CalculateLRC(unsigned char *buf, unsigned short bsize) - Calculate and return LRC
*       @arg *buf - buffer pointer
*       @arg bsize - buffer size
*       @return Calculated LRC (uint16_t)
*/
unsigned char ModBus_CalculateLRC(void)
{
    unsigned char *pData = UART_StartMsgPointer;
    unsigned char LRC = 0;
    unsigned short bsize = ((unsigned short)(UART_LRCIndexPointer - UART_StartMsgPointer));
    while(bsize--)
    {
        LRC += *pData++;
    }
    return ((unsigned char)(-((char)LRC)));
}

/*!
*   @brief ModBus_CheckFrame(void) - Function of check begin and end MSG
*       @return 0 - Not detected MSG
*               1 - Detected MSG
*/
static const unsigned char EndFrame[2] = {0x0D,0x0A};
bool ModBus_CheckFrame(void)
{
    bool IsMSG = false;
    unsigned char *UART_PredictPointer = UART_StartMsgPointer + MINIMAL_OFFSET;
    /*! Check start character */
    if(*UART_StartMsgPointer != 0x3A) return false;
    /*! Checking frame after pointer value more than MINIMAL_OFFSET */
    if(UART_Buffer < UART_PredictPointer) return false;
    /*! Check end character CR LF*/
    for(unsigned char *i = UART_PredictPointer; i < UART_EndMsgPointer; i++)
    {
        if(*i != EndFrame[0]) continue;
        if(*(i + 1) != EndFrame[1]) continue;
        IsMSG = true;
        UART_PredictPointer = i;
        break;
    }
    if(!IsMSG) return false;
    UART_LRCIndexPointer = UART_PredictPointer - 2;
    ModBus_BusyFlag = true;
    NVIC_DisableIRQ(ModBus_IRQ);
return true;
}

static uint8_t index = 0;
void ModBus_CounstructAnswer(unsigned int Code)
{
    switch(Code)
    {
    case 0x03:
        {
            /*! Insert number of transfer bytes */
           // ModBus_HEX_TO_ASCII_Converter(UART_DataIndexPointer,index);
            for(int i = 0; i < index; i++)
            {
//                ModBus_HEX_TO_ASCII_Converter(UART_DataIndexPointer, Registers_32BitValues[i]);
            }
            /*! Adding content */

            break;
        }


    }


}

static uint32_t *ModBus_ConstructRegister(unsigned char *RegisterPointer)
{
    uint32_t Result = 0x40000000;
    uint16_t REG = 0;
    for(int i = 0; i < 4; i++)
    {
        REG = ModBus_ASCII_TO_HEX_Converter(RegisterPointer, 2);
        REG = REG << (8 * (3 - i));
        Result |= (uint32_t)REG;
        RegisterPointer += 2;
    }
    if(Result > 0x5003FFFF) return 0x00;
return ((uint32_t *)Result);
}

uint32_t Value;
void ModBus_ParsePacket(unsigned char Address)
{
    /*! Check Address */
    unsigned char Tmp = ModBus_ASCII_TO_HEX_Converter(UART_AddressIndexPointer, 2);
    if(Tmp != Address) return;

    /*! Check LRC (Longitudinal Redundancy Check) */
    unsigned char LRC_Check = ModBus_CalculateLRC();
    Tmp = ModBus_ASCII_TO_HEX_Converter(UART_LRCIndexPointer, 2);
    if(Tmp != LRC_Check) return;

    /*! Check Function code */
    Tmp = ModBus_ASCII_TO_HEX_Converter(UART_FunctionIndexPointer, 2);
    if( Tmp != 0x03 && Tmp != 0x06) return;

    switch(Tmp)
    {

    /*! Read Holding registers */
    case 0x03:
        {
            uint32_t *Register;
            uint8_t Length = 0;
            Register = ModBus_ConstructRegister(UART_DataIndexPointer);
            Length = ModBus_ASCII_TO_HEX_Converter((UART_LRCIndexPointer - 2), 2);
            for(register uint8_t i = 0; i < Length; i++)
            {
                if(i > ModBus_MAXREGS) break;
                Value = *Register;
                Register = (uint32_t *)(((uint32_t)Register) + 0x04);
                Registers_32BitValues[i] = Value;
                index++;
            }
            break;
        }

        /*! @code NOT_SUPPORTED EXCEPTION */
        default: return;
    }
}
#endif /*__configEXT_ModBus*/
