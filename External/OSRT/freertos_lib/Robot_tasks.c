#include "Robot_tasks.h"

void vApplicationTickHook(void)
{
    /*!
    *   @brief vApplicationIdleHook(void) - ������� ����������� ����� ������� ���������� ����� ������
    *   @arg nothing - ������� ������ �� �������� � ������ �� ����������
    */

}

void vApplicationIdleHook(void)
{
    /*!
    *   @brief vApplicationTickHook(void) - ������� �����������, ����������� ����� ������������ ����� ����� �� ������
    *   @arg nothing - ������� ������ �� �������� � ������ �� ����������
    */
}

void vApplicationStackOverflowHook( TaskHandle_t xTask, char *pcTaskName )
{
/*!
*   @brief vApplicationIdleHook(void) - ������� ������������, ����������� ����� ���� ������ ������������
*   @arg xTask - ���������� ������, pcTaskName - �������� ������
*
*/
}
void vApplicationMallocFailedHook( void )
{

}



void vBlinkTest(void *pvParameters)
{

    for(;;)
    {

    }
vTaskDelete(NULL);
}

#endif /*FIL_FREERTOS*/
