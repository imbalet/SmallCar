    /*!
    *   --------------------------------------------------------------------------
    *                       ///Regulators\\\
    *   --------------------------------------------------------------------------
    *   @author RCR group developers - Evgeny Garanin
    *   @date 02/08/2022 - last update version Regulators
    *
    *       @note [RCR:Regulators] Configuration file Regulators
    */
#pragma once
#include "BoardSelection.h"
#if(CALC_REGULATOR == 1)

    typedef struct
    {
        char reg_on;
        float p_k;
        float i_k;
        float d_k;
        float max_sum_error;
        float reg_output_end;
        float reg_error_end;
        float min_output;
        float max_output;
    }RegulatorParameters;
    RegulatorParameters Settings[__config_RegulatorList];

    /*!
    *   @list P_Regulator Settings
    */
#ifndef __config_RegulatorListP
    #define P_List          1
#else
    #define P_List  __config_RegulatorListP
#endif /*__config_RegulatorListP*/

    typedef struct
    {
          float p_k; //П коэфициент
          float target; //Целевое значение
          float current; //Текущее (необходимо обновлять извне перед каждым расчетом)
          float error;
          float max_output; //Максимальный выход, что бы поправка не выходила за рамки
          float min_output;
          float output; //Поправка, результат работы П
          char p_on; //Вкл/Выкл П если выкл то output всегда равен 0, однако все остальное продолжает расчитываться
          char p_finish;
          float error_dir;
          float p_error_end;
          float p_output_end;
    }P_Regulator;
    P_Regulator P[P_List];

void RegulatorAdd_P_Settings(uint8_t Number, RegulatorParameters* Settings);

    /*!
    *   @list PI_Regulator Settings
    */
#ifndef __config_RegulatorListPI
    #define PI_List          1
#else
    #define PI_List  __config_RegulatorListPI
#endif /*__config_RegulatorListPI*/
    typedef struct
    {
          float p_k; //П коэфициент
          float i_k; //И коэфициент
          float target; //Целевое значение
          float current; //Текущее (необходимо обновлять извне перед каждым расчетом)
          float error;
          float sum_error; //Суммарная ошибка (для И регулятора)
          float max_sum_error; //Максимальная суммарная ошибка (что бы И регулятор не уходил до максимума если невозможно добиться требуемого значения)
          float max_output; //Максимальный выход, что бы поправка не выходила за рамки
          float min_output;
          float cut_output;
          float output; //Поправка, результат работы ПИ
          char pi_on; //Вкл/Выкл ПИ если выкл то output всегда равен 0, однако все остальное продолжает расчитываться
          char pi_finish;
          float pi_error_end;
          float pi_output_end;
    }PI_Regulator;
    PI_Regulator PI[PI_List];


    /*!
    *   @list PID_Regulator Settings
    */
#ifndef __config_RegulatorListPID
    #define PID_List          1
#else
    #define PID_List  __config_RegulatorListPID
#endif /*__config_RegulatorListPID*/
    typedef struct
    {
          float p_k; //П коэфициент
          float i_k; //И коэфициент
          float d_k; //Д коэфициент
          float target; //Целевое значение
          float current; //Текущее (необходимо обновлять извне перед каждым расчетом)
          float prev_error; //Предыдущее значение ошибки (для Д регулятора)
          float error;  // обычная ошибка
          float sum_error; //Суммарная ошибка (для И регулятора)
          float max_sum_error; //Максимальная суммарная ошибка (что бы И регулятор не уходил до максимума если невозможно добиться требуемого значения)
          float dif_error; // ошибка для дифференциальной составляющей регулятора
          float max_output; //Максимальный выход, что бы поправка не выходила за рамки
          float min_output;
          float output; //Поправка, результат работы ПИД
          char pid_on; //Вкл/Выкл ПИД если выкл то output всегда равен 0, однако все остальное продолжает расчитываться
          char pid_finish;
          float pid_error_end;
          float pid_output_end;
    }PID_Regulator;
    PID_Regulator PID[PID_List];

void RegulatorAdd_PID_Settings(uint8_t Number, RegulatorParameters* Settings);

void PID_Start(PID_Regulator* pid_control);

void PID_Stop(PID_Regulator* pid_control);

void PID_Calc(PID_Regulator* pid_control);

#endif /*CALC_REGULATOR*/
