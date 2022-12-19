    /*!
    *   --------------------------------------------------------------------------
    *                ///ModBus header file\\\
    *   --------------------------------------------------------------------------
    *   @author RCR group developers
    *   @date 14/10/2022 - last update version ModBus
    *
    */
#pragma once
#include "ModBus_conf.h"
#define STANDART_MODBUS_SIZE        (513)

/*!
*   [ModBus] Allocated prototypes indexes
*/
unsigned char* UART_Buffer;
unsigned char* UART_StartMsgPointer;
unsigned char* UART_AddressIndexPointer;    /*! Slave address Pointer */
unsigned char* UART_FunctionIndexPointer;   /*! Function code MSG Pointer */
unsigned char* UART_DataIndexPointer;       /*! @arg Data Pointer */
unsigned char* UART_CurrentIndexPointer;    /*! @arg Interrupt Pointer */
unsigned char* UART_LRCIndexPointer;        /*! @arg LRC Pointer (Longitudinal Redundancy Check) */
unsigned char* UART_EndMsgPointer;          /*! @arg 0D 0A Pointer */

#if(__configMODBUS_SlaveAddress == 0)
/*!
*   @note Master detected
*/
#define MASTER
#else
/*!
*   @note Slave detected
*/
#define SLAVE
__attribute__((unused)) static unsigned char ADDRESS = __configMODBUS_SlaveAddress;

#endif /*__configMODBUS_SlaveAddress*/
/*!
*   @brief ModBus_Init(void) - Initialize ModBus interface and allocate storage
*       @return nothing
*/
void ModBus_Init(void);

/*!
*   @brief ModBus_Init(void) - Reinitialize ModBus protocol and recover indexes position
*       @return nothing
*/
void ModBus_ReInit(void);

/*!
*   @brief ModBus_CloseTransmission(void) - Close ModBus interface and delete storage
*       @return nothing
*/
void ModBus_CloseTransmission(void);

/*!
*   @brief ModBus_ClearMsgs(void) - Clear allocated storage for ModBus transmission
*       @return nothing
*/
void ModBus_ClearMsgs(void);

/*!
*   @brief ModBus_CalculateLRC(unsigned char *buf, unsigned short bsize) - Calculate and return LRC
*       @arg *buf - buffer pointer
*       @arg bsize - buffer size
*       @return Calculated LRC (uint16_t)
*/
unsigned char ModBus_CalculateLRC(void);

/*!
*   @brief ModBus_CheckFrame(void) - Function of check begin and end MSG
*       @return Nothing
*/
bool ModBus_CheckFrame(void);

void ModBus_ParsePacket(unsigned char Address);

void ModBus_ReadRegisters(uint32_t *Register, uint8_t Bytes);
