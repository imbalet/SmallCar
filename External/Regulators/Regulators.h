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
          float p_k; //� ����������
          float target; //������� ��������
          float current; //������� (���������� ��������� ����� ����� ������ ��������)
          float error;
          float max_output; //������������ �����, ��� �� �������� �� �������� �� �����
          float min_output;
          float output; //��������, ��������� ������ �
          char p_on; //���/���� � ���� ���� �� output ������ ����� 0, ������ ��� ��������� ���������� �������������
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
          float p_k; //� ����������
          float i_k; //� ����������
          float target; //������� ��������
          float current; //������� (���������� ��������� ����� ����� ������ ��������)
          float error;
          float sum_error; //��������� ������ (��� � ����������)
          float max_sum_error; //������������ ��������� ������ (��� �� � ��������� �� ������ �� ��������� ���� ���������� �������� ���������� ��������)
          float max_output; //������������ �����, ��� �� �������� �� �������� �� �����
          float min_output;
          float cut_output;
          float output; //��������, ��������� ������ ��
          char pi_on; //���/���� �� ���� ���� �� output ������ ����� 0, ������ ��� ��������� ���������� �������������
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
          float p_k; //� ����������
          float i_k; //� ����������
          float d_k; //� ����������
          float target; //������� ��������
          float current; //������� (���������� ��������� ����� ����� ������ ��������)
          float prev_error; //���������� �������� ������ (��� � ����������)
          float error;  // ������� ������
          float sum_error; //��������� ������ (��� � ����������)
          float max_sum_error; //������������ ��������� ������ (��� �� � ��������� �� ������ �� ��������� ���� ���������� �������� ���������� ��������)
          float dif_error; // ������ ��� ���������������� ������������ ����������
          float max_output; //������������ �����, ��� �� �������� �� �������� �� �����
          float min_output;
          float output; //��������, ��������� ������ ���
          char pid_on; //���/���� ��� ���� ���� �� output ������ ����� 0, ������ ��� ��������� ���������� �������������
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
