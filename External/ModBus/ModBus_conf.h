    /*!
    *   --------------------------------------------------------------------------
    *                ///ModBus configuration file\\\
    *   --------------------------------------------------------------------------
    *   @author RCR group developers
    *   @date 15/10/2022 - last update version ModBus
    *
    */
#pragma once
#if(__configEXT_ModBus == 1)
/*! Standart includes */
#include <stdlib.h>

/*! FIL driver files */
#include "FilConfig.h"
#include "BoardSelection.h"

/*! ModBus header file */
#include "ModBus_ASCII.h"

#if (__configMODBUS_AUTOPARSE == 1)
#ifndef __configMODBUS_TIMInterruptSourse
    #define __configMODBUS_TIMInterruptSourse       TIM4_IRQHandler
#endif /* __configMODBUS_TIMInterruptSourse */
#endif /* __configMODBUS_AUTOPARSE */
/*!
*   @brief ModBus Configuration parameters
*/
#define ModBus_Source                   __configMODBUS_Source
#define ModBus_Handler                  __configMODBUS_Handler
#define ModBus_MasterMode               __configMODBUS_MasterMode
#define ModBus_IRQ                      __configMODBUS_InterruptSource
#define ModBus_TimIRQ                   __configMODBUS_TIMInterruptSourse
#define ModBus_MAXREGS                  __configMODBUS_MAXREGISTERS
#define MINIMAL_OFFSET                  __configMODBUS_MINIMAL_OFFSET

/*!
*   @arg ModBus_BusyFlag - General Busy Flag
*/
bool ModBus_BusyFlag;

/*!
*   @arg REGISTERS - 8-bit Table registers
*/
uint8_t Registers_8Bit[ModBus_MAXREGS];
/*!
*   @arg Registers_8BitValues - 8-bit values registers
*/
uint8_t Registers_8BitValues[ModBus_MAXREGS];
/*!
*   @arg Registers_16Bit - 16-bit registers Table
*/
uint16_t Registers_16Bit[ModBus_MAXREGS];
/*!
*   @arg Registers_16BitValues - 16-bit values Table
*/
uint16_t Registers_16BitValues[ModBus_MAXREGS];
/*!
*   @arg Registers_32Bit - 32-bit registers Table
*/
uint32_t Registers_32Bit[ModBus_MAXREGS];
/*!
*   @arg Registers_32BitValues - 32-bit values Table
*/
uint32_t Registers_32BitValues[ModBus_MAXREGS];
#endif /*__configEXT_ModBus*/
