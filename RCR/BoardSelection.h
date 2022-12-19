#pragma once
/*!
*
*   @file RCR_BoardSelection.h
*   @note [RCR] Setup project
*   @author RCR group developers - Caska
*   @date   28/07/2022 - last update
*
*/

/*!
*   @arg 0 - Minimal Kit
*   @arg 1 - RCR Development Board #1
*   @arg 2 - RCR Development Board #2
*   @arg 3 - RCR Development Board #3
*   @arg 4 - RCR Custom project
*   @arg 0xFF - Maximum Kit
*/
#define _configUSEBoards                (2)

#if (_configUSEBoards == 0)
    #include "MinimalKit.h"
#endif /*_configUSEBoards*/
#if (_configUSEBoards == 0xFF)
    #include "MaxPins.h"
    #include "MaxKit.h"
    #include "MaxSetup.h"
#endif /*_configUSEBoards*/
#if (_configUSEBoards > 0 && _configUSEBoards < 0xFF )
    #if (_configUSEBoards == 1) // Development Board №1(Custom project - STM32F407)
        #include "RCR_DevBoard_1_Setup.h"
    #endif /*Development Board №1*/
    #if (_configUSEBoards == 2) // Development Board №2 (Blue pill board - STM32Fxx)
        #include "RCR_DevBoard_2_Setup.h"
    #endif /*Development Board №2*/
    #if (_configUSEBoards == 3) // Development Board №3 (Green pill board - STM32F401)
        #include "RCR_DevBoard_3_Setup.h"
    #endif /*Development Board №3*/
    #if (_configUSEBoards == 4) // Development Board №4 (Coming soon - new project in this list)
        #include "Pins.h"
        #include "Setup.h"
    #endif /*Development Board №4*/
    #if ((_configUSEBoards < 0) || (_configUSEBoards > 0xFF))
        #error Invalid argument of Development Board
    #endif /*_configUSEBoards*/
    #include "dev.h"
    #include "dev_ws.h"
#endif /*_configUSEBoards*/


