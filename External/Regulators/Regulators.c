    /*!
    *   --------------------------------------------------------------------------
    *                       ///Regulators\\\
    *   --------------------------------------------------------------------------
    *   @author RCR group developers - Evgeny Garanin, Caska
    *   @date 02/08/2022 - last update version Regulators
    *
    *       @note [RCR:Regulators] Regulators source file
    */
#include "FilConfig.h"

#if (CALC_REGULATOR == 1)
#include "Regulators.h"

void RegulatorAdd_P_Settings(uint8_t Number, RegulatorParameters* Settings)
{
    if(--Number < 0 || Number > P_List) return;

    P[Number].p_k = Settings->p_k;
    P[Number].p_on = Settings->reg_on;
    P[Number].p_error_end = Settings->reg_error_end;
    P[Number].p_output_end = Settings->reg_output_end;
    P[Number].min_output = Settings->min_output;
    P[Number].max_output = Settings->max_output;

    P[Number].error = 0.0;
}

/*!
*   @note [FIL:Regulators] PI Regulator Sector
*/
void RegulatorAdd_PI_Settings(uint8_t Number, RegulatorParameters* Settings)
{
    if(--Number < 0 || Number > PI_List) return;

    PI[Number].p_k = Settings->p_k;
    PI[Number].i_k = Settings->i_k;
  	PI[Number].pi_on = Settings->reg_on;
  	PI[Number].pi_error_end  = Settings->reg_error_end;
  	PI[Number].pi_output_end = Settings->reg_output_end;
  	PI[Number].max_sum_error = Settings->max_sum_error;
  	PI[Number].max_output = Settings->max_output;
  	PI[Number].min_output = Settings->min_output;

    // zeroing errors
    PI[Number].error = 0.0;
    PI[Number].sum_error = 0.0;
}

void PI_Start(PI_Regulator* pi_control)
{
    pi_control->pi_on = 1;
}

void PI_Stop(PI_Regulator* pi_control)
{
    pi_control->pi_on = 0;
    pi_control->error = 0.0;
    pi_control->sum_error = 0.0;
}

/*!
*   @note [FIL:Regulators] PID Regulator Sector
*/

/*!
*   @brief RegulatorAdd_PID_Settings(uint8_t Number, RegulatorParameters* Settings)
*/
void RegulatorAdd_PID_Settings(uint8_t Number, RegulatorParameters* Settings)
{
    if(--Number < 0 || Number > PID_List) return;
    PID[Number].p_k = Settings->p_k;
    PID[Number].i_k = Settings->i_k;
  	PID[Number].d_k = Settings->d_k;
  	PID[Number].pid_on = Settings->reg_on;
  	PID[Number].pid_error_end  = Settings->reg_error_end;
  	PID[Number].pid_output_end = Settings->reg_output_end;
  	PID[Number].max_sum_error = Settings->max_sum_error;
  	PID[Number].max_output = Settings->max_output;
  	PID[Number].min_output = Settings->min_output;

    // zeroing errors
    PID[Number].prev_error = 0.0;
    PID[Number].error = 0.0;
    PID[Number].sum_error = 0.0;
    PID[Number].dif_error = 0.0;
}

void PID_Start(PID_Regulator* pid_control)
{
    pid_control->pid_on = 1;
}

void PID_Stop(PID_Regulator* pid_control)
{
    pid_control->pid_on = 0;
    pid_control->prev_error = 0.0;
    pid_control->error = 0.0;
    pid_control->sum_error = 0.0;
    pid_control->dif_error = 0.0;
}

/*!
*   @brief PID_Parse_EncoderData(int32_t encoderdata) - check value from encoder and calculate speed
*/
void PID_Calc(PID_Regulator* pid_control)
{
  pid_control->error = pid_control->target - pid_control->current;
  pid_control->dif_error = pid_control->error - pid_control->prev_error;
  pid_control->prev_error = pid_control->error;
  pid_control->sum_error += pid_control->error;

  if (pid_control->sum_error > pid_control->max_sum_error)
    pid_control->sum_error = pid_control->max_sum_error;
  if (pid_control->sum_error < -pid_control->max_sum_error)
    pid_control->sum_error = -pid_control->max_sum_error;

  if (pid_control->pid_on)
  {
    pid_control->output = ((float)(pid_control->p_k * pid_control->error)+(pid_control->i_k * pid_control->sum_error)+
            (pid_control->d_k * pid_control->dif_error));

    if (pid_control->output > pid_control->max_output)
      pid_control->output = pid_control->max_output;
    else if (pid_control->output < -pid_control->max_output)
      pid_control->output = -pid_control->max_output;

    if (pid_control->output < pid_control->min_output && pid_control->output > -pid_control->min_output)
      pid_control->output = 0;

    if ((pid_control->output <= pid_control->pid_output_end) &&(
        pid_control->output >= -pid_control->pid_output_end) &&(
        pid_control->error <= pid_control->pid_error_end) && (pid_control->error >= -pid_control->pid_error_end))
      pid_control->pid_finish = 1;
    else
      pid_control->pid_finish = 0;
  }
  else
  {
    pid_control->output = 0;
    pid_control->pid_finish = 0;
  }
}

#endif /*CALC_REGULATOR*/
