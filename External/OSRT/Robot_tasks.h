#pragma once
#include "FilConfig.h"
#if (FIL_FREERTOS == 1)

/*!
*   @brief vBlinkTest(void *pvParameters) - ���� ���������� ������ ������������ ������� FreeRTOS
*       @arg nothing
*       @note [FIL:FreeRTOS] ����� �������� ������������ � ������������� �� ���� https://www.freertos.org/features.html
*/
xTaskHandle xBlinkHandle;
void vBlinkTest(void *pvParameters);

#endif /*FIL_FREERTOS*/
