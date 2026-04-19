/*
 * File: TailSitter_Sim.c
 *
 * Code generated for Simulink model 'TailSitter_Sim'.
 *
 * Model version                  : 1.2
 * Simulink Coder version         : 25.2 (R2025b) 28-Jul-2025
 * C/C++ source code generated on : Sun Apr 19 19:52:54 2026
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-M
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "TailSitter_Sim.h"
#include <math.h>
#include "rtwtypes.h"
#include "TailSitter_Sim_private.h"

/* Exported data definition */

/* Data with Exported storage */
real_T TailSitter_Sim_Motor_PWM[4];    /* '<Root>/Motor_PWM' */
real_T TailSitter_Sim_Sensor_Verileri[4];/* '<Root>/Sensor_Verileri' */

/* Block signals (default storage) */
B_TailSitter_Sim_T TailSitter_Sim_B;

/* Continuous states */
X_TailSitter_Sim_T TailSitter_Sim_X;

/* Disabled State Vector */
XDis_TailSitter_Sim_T TailSitter_Sim_XDis;

/* Real-time model */
static RT_MODEL_TailSitter_Sim_T TailSitter_Sim_M_;
RT_MODEL_TailSitter_Sim_T *const TailSitter_Sim_M = &TailSitter_Sim_M_;

/*
 * This function updates continuous states using the ODE3 fixed-step
 * solver algorithm
 */
static void rt_ertODEUpdateContinuousStates(RTWSolverInfo *si )
{
  /* Solver Matrices */
  static const real_T rt_ODE3_A[3] = {
    1.0/2.0, 3.0/4.0, 1.0
  };

  static const real_T rt_ODE3_B[3][3] = {
    { 1.0/2.0, 0.0, 0.0 },

    { 0.0, 3.0/4.0, 0.0 },

    { 2.0/9.0, 1.0/3.0, 4.0/9.0 }
  };

  time_T t = rtsiGetT(si);
  time_T tnew = rtsiGetSolverStopTime(si);
  time_T h = rtsiGetStepSize(si);
  real_T *x = rtsiGetContStates(si);
  ODE3_IntgData *id = (ODE3_IntgData *)rtsiGetSolverData(si);
  real_T *y = id->y;
  real_T *f0 = id->f[0];
  real_T *f1 = id->f[1];
  real_T *f2 = id->f[2];
  real_T hB[3];
  int_T i;
  int_T nXc = 12;
  rtsiSetSimTimeStep(si,MINOR_TIME_STEP);

  /* Save the state values at time t in y, we'll use x as ynew. */
  (void) memcpy(y, x,
                (uint_T)nXc*sizeof(real_T));

  /* Assumes that rtsiSetT and ModelOutputs are up-to-date */
  /* f0 = f(t,y) */
  rtsiSetdX(si, f0);
  TailSitter_Sim_derivatives();

  /* f(:,2) = feval(odefile, t + hA(1), y + f*hB(:,1), args(:)(*)); */
  hB[0] = h * rt_ODE3_B[0][0];
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0]);
  }

  rtsiSetT(si, t + h*rt_ODE3_A[0]);
  rtsiSetdX(si, f1);
  TailSitter_Sim_step();
  TailSitter_Sim_derivatives();

  /* f(:,3) = feval(odefile, t + hA(2), y + f*hB(:,2), args(:)(*)); */
  for (i = 0; i <= 1; i++) {
    hB[i] = h * rt_ODE3_B[1][i];
  }

  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1]);
  }

  rtsiSetT(si, t + h*rt_ODE3_A[1]);
  rtsiSetdX(si, f2);
  TailSitter_Sim_step();
  TailSitter_Sim_derivatives();

  /* tnew = t + hA(3);
     ynew = y + f*hB(:,3); */
  for (i = 0; i <= 2; i++) {
    hB[i] = h * rt_ODE3_B[2][i];
  }

  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1] + f2[i]*hB[2]);
  }

  rtsiSetT(si, tnew);
  rtsiSetSimTimeStep(si,MAJOR_TIME_STEP);
}

/* Model step function */
void TailSitter_Sim_step(void)
{
  real_T rtb_Gain_idx_3;
  real_T rtb_Integrator1;
  real_T rtb_TransferFcn;
  real_T rtb_TransferFcn1;
  real_T rtb_TransferFcn2;
  int32_T i;
  int32_T rtb_Gain_idx_0_tmp;
  if (rtmIsMajorTimeStep(TailSitter_Sim_M)) {
    /* set solver stop time */
    rtsiSetSolverStopTime(&TailSitter_Sim_M->solverInfo,
                          ((TailSitter_Sim_M->Timing.clockTick0+1)*
      TailSitter_Sim_M->Timing.stepSize0));
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(TailSitter_Sim_M)) {
    TailSitter_Sim_M->Timing.t[0] = rtsiGetT(&TailSitter_Sim_M->solverInfo);
  }

  /* TransferFcn: '<S2>/Transfer Fcn' */
  rtb_TransferFcn = 50.0 * TailSitter_Sim_X.TransferFcn_CSTATE;

  /* TransferFcn: '<S2>/Transfer Fcn1' */
  rtb_TransferFcn1 = 50.0 * TailSitter_Sim_X.TransferFcn1_CSTATE;

  /* TransferFcn: '<S2>/Transfer Fcn2' */
  rtb_TransferFcn2 = 50.0 * TailSitter_Sim_X.TransferFcn2_CSTATE;

  /* TransferFcn: '<S2>/Transfer Fcn3' */
  rtb_Integrator1 = 50.0 * TailSitter_Sim_X.TransferFcn3_CSTATE;

  /* Math: '<S4>/Math Function' incorporates:
   *  SignalConversion generated from: '<S4>/Math Function'
   */
  TailSitter_Sim_B.rtb_MathFunction_m[0] = rtb_TransferFcn * rtb_TransferFcn;

  /* Gain: '<S4>/Gain' */
  rtb_TransferFcn = 0.0;

  /* Math: '<S4>/Math Function' incorporates:
   *  SignalConversion generated from: '<S4>/Math Function'
   */
  TailSitter_Sim_B.rtb_MathFunction_m[1] = rtb_TransferFcn1 * rtb_TransferFcn1;

  /* Gain: '<S4>/Gain' */
  rtb_TransferFcn1 = 0.0;

  /* Math: '<S4>/Math Function' incorporates:
   *  SignalConversion generated from: '<S4>/Math Function'
   */
  TailSitter_Sim_B.rtb_MathFunction_m[2] = rtb_TransferFcn2 * rtb_TransferFcn2;

  /* Gain: '<S4>/Gain' */
  rtb_TransferFcn2 = 0.0;

  /* Math: '<S4>/Math Function' incorporates:
   *  SignalConversion generated from: '<S4>/Math Function'
   */
  TailSitter_Sim_B.rtb_MathFunction_m[3] = rtb_Integrator1 * rtb_Integrator1;

  /* Gain: '<S4>/Gain' */
  rtb_Gain_idx_3 = 0.0;
  for (i = 0; i < 4; i++) {
    rtb_Integrator1 = TailSitter_Sim_B.rtb_MathFunction_m[i];
    rtb_Gain_idx_0_tmp = i << 2;
    rtb_TransferFcn += TailSitter_Sim_ConstP.Gain_Gain[rtb_Gain_idx_0_tmp] *
      rtb_Integrator1;
    rtb_TransferFcn1 += TailSitter_Sim_ConstP.Gain_Gain[rtb_Gain_idx_0_tmp + 1] *
      rtb_Integrator1;
    rtb_TransferFcn2 += TailSitter_Sim_ConstP.Gain_Gain[rtb_Gain_idx_0_tmp + 2] *
      rtb_Integrator1;
    rtb_Gain_idx_3 += TailSitter_Sim_ConstP.Gain_Gain[rtb_Gain_idx_0_tmp + 3] *
      rtb_Integrator1;

    /* Gain: '<S2>/Gain' incorporates:
     *  Inport: '<Root>/Motor_PWM'
     */
    TailSitter_Sim_B.Gain_c[i] = 15540.0 * TailSitter_Sim_Motor_PWM[i];
  }

  /* Gain: '<S1>/Gain' */
  TailSitter_Sim_B.Gain = 2.0 * rtb_TransferFcn;

  /* Gain: '<S1>/Gain1' */
  TailSitter_Sim_B.Gain1 = 200.0 * rtb_TransferFcn1;

  /* Gain: '<S1>/Gain2' */
  TailSitter_Sim_B.Gain2 = 200.0 * rtb_TransferFcn2;

  /* Gain: '<S1>/Gain3' */
  TailSitter_Sim_B.Gain3 = 111.11111111111111 * rtb_Gain_idx_3;

  /* Outport: '<Root>/Sensor_Verileri' incorporates:
   *  Integrator: '<S3>/Integrator1'
   */
  TailSitter_Sim_Sensor_Verileri[0] = TailSitter_Sim_X.Integrator1_CSTATE;

  /* MATLAB Function: '<S3>/MATLAB Function' incorporates:
   *  Integrator: '<S1>/ Pitch_Hizi'
   *  Integrator: '<S1>/Roll_Hizi '
   *  Integrator: '<S1>/Yaw_Hizi '
   *  Integrator: '<S3>/Integrator'
   */
  rtb_Integrator1 = tan(TailSitter_Sim_X.Integrator_CSTATE[1]);
  rtb_TransferFcn = cos(TailSitter_Sim_X.Integrator_CSTATE[0]);
  rtb_TransferFcn1 = sin(TailSitter_Sim_X.Integrator_CSTATE[0]);
  rtb_TransferFcn2 = cos(TailSitter_Sim_X.Integrator_CSTATE[1]);
  TailSitter_Sim_B.dv[0] = 1.0;
  TailSitter_Sim_B.dv[3] = rtb_TransferFcn1 * rtb_Integrator1;
  TailSitter_Sim_B.dv[6] = rtb_TransferFcn * rtb_Integrator1;
  TailSitter_Sim_B.dv[1] = 0.0;
  TailSitter_Sim_B.dv[4] = rtb_TransferFcn;
  TailSitter_Sim_B.dv[7] = -rtb_TransferFcn1;
  TailSitter_Sim_B.dv[2] = 0.0;
  TailSitter_Sim_B.dv[5] = rtb_TransferFcn1 / rtb_TransferFcn2;
  TailSitter_Sim_B.dv[8] = rtb_TransferFcn / rtb_TransferFcn2;
  TailSitter_Sim_B.dv1[0] = TailSitter_Sim_X.Roll_Hizi_CSTATE;
  TailSitter_Sim_B.dv1[1] = TailSitter_Sim_X.Pitch_Hizi_CSTATE;
  TailSitter_Sim_B.dv1[2] = TailSitter_Sim_X.Yaw_Hizi_CSTATE;

  /* Outport: '<Root>/Sensor_Verileri' incorporates:
   *  Integrator: '<S3>/Integrator'
   */
  TailSitter_Sim_Sensor_Verileri[1] = TailSitter_Sim_X.Integrator_CSTATE[0];

  /* MATLAB Function: '<S3>/MATLAB Function' */
  rtb_TransferFcn = 0.0;

  /* Outport: '<Root>/Sensor_Verileri' incorporates:
   *  Integrator: '<S3>/Integrator'
   */
  TailSitter_Sim_Sensor_Verileri[2] = TailSitter_Sim_X.Integrator_CSTATE[1];

  /* MATLAB Function: '<S3>/MATLAB Function' */
  rtb_TransferFcn1 = 0.0;

  /* Outport: '<Root>/Sensor_Verileri' incorporates:
   *  Integrator: '<S3>/Integrator'
   */
  TailSitter_Sim_Sensor_Verileri[3] = TailSitter_Sim_X.Integrator_CSTATE[2];

  /* MATLAB Function: '<S3>/MATLAB Function' */
  rtb_TransferFcn2 = 0.0;
  for (i = 0; i < 3; i++) {
    rtb_Integrator1 = TailSitter_Sim_B.dv1[i];
    rtb_TransferFcn += TailSitter_Sim_B.dv[3 * i] * rtb_Integrator1;
    rtb_TransferFcn1 += TailSitter_Sim_B.dv[3 * i + 1] * rtb_Integrator1;
    rtb_TransferFcn2 += TailSitter_Sim_B.dv[3 * i + 2] * rtb_Integrator1;
  }

  TailSitter_Sim_B.euler_hizlari[0] = rtb_TransferFcn;
  TailSitter_Sim_B.euler_hizlari[1] = rtb_TransferFcn1;
  TailSitter_Sim_B.euler_hizlari[2] = rtb_TransferFcn2;

  /* Integrator: '<S1>/Z_Ekseni_Hizi' */
  TailSitter_Sim_B.Z_Ekseni_Hizi = TailSitter_Sim_X.Z_Ekseni_Hizi_CSTATE;
  if (rtmIsMajorTimeStep(TailSitter_Sim_M)) {
    rt_ertODEUpdateContinuousStates(&TailSitter_Sim_M->solverInfo);

    /* Update absolute time for base rate */
    /* The "clockTick0" counts the number of times the code of this task has
     * been executed. The absolute time is the multiplication of "clockTick0"
     * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
     * overflow during the application lifespan selected.
     */
    ++TailSitter_Sim_M->Timing.clockTick0;
    TailSitter_Sim_M->Timing.t[0] = rtsiGetSolverStopTime
      (&TailSitter_Sim_M->solverInfo);

    {
      /* Update absolute timer for sample time: [0.01s, 0.0s] */
      /* The "clockTick1" counts the number of times the code of this task has
       * been executed. The resolution of this integer timer is 0.01, which is the step size
       * of the task. Size of "clockTick1" ensures timer will not overflow during the
       * application lifespan selected.
       */
      TailSitter_Sim_M->Timing.clockTick1++;
    }
  }                                    /* end MajorTimeStep */
}

/* Derivatives for root system: '<Root>' */
void TailSitter_Sim_derivatives(void)
{
  XDot_TailSitter_Sim_T *_rtXdot;
  _rtXdot = ((XDot_TailSitter_Sim_T *) TailSitter_Sim_M->derivs);

  /* Derivatives for TransferFcn: '<S2>/Transfer Fcn' */
  _rtXdot->TransferFcn_CSTATE = -50.0 * TailSitter_Sim_X.TransferFcn_CSTATE;
  _rtXdot->TransferFcn_CSTATE += TailSitter_Sim_B.Gain_c[0];

  /* Derivatives for TransferFcn: '<S2>/Transfer Fcn1' */
  _rtXdot->TransferFcn1_CSTATE = -50.0 * TailSitter_Sim_X.TransferFcn1_CSTATE;
  _rtXdot->TransferFcn1_CSTATE += TailSitter_Sim_B.Gain_c[1];

  /* Derivatives for TransferFcn: '<S2>/Transfer Fcn2' */
  _rtXdot->TransferFcn2_CSTATE = -50.0 * TailSitter_Sim_X.TransferFcn2_CSTATE;
  _rtXdot->TransferFcn2_CSTATE += TailSitter_Sim_B.Gain_c[2];

  /* Derivatives for TransferFcn: '<S2>/Transfer Fcn3' */
  _rtXdot->TransferFcn3_CSTATE = -50.0 * TailSitter_Sim_X.TransferFcn3_CSTATE;
  _rtXdot->TransferFcn3_CSTATE += TailSitter_Sim_B.Gain_c[3];

  /* Derivatives for Integrator: '<S3>/Integrator' */
  _rtXdot->Integrator_CSTATE[0] = TailSitter_Sim_B.euler_hizlari[0];
  _rtXdot->Integrator_CSTATE[1] = TailSitter_Sim_B.euler_hizlari[1];
  _rtXdot->Integrator_CSTATE[2] = TailSitter_Sim_B.euler_hizlari[2];

  /* Derivatives for Integrator: '<S3>/Integrator1' */
  _rtXdot->Integrator1_CSTATE = TailSitter_Sim_B.Z_Ekseni_Hizi;

  /* Derivatives for Integrator: '<S1>/Roll_Hizi ' */
  _rtXdot->Roll_Hizi_CSTATE = TailSitter_Sim_B.Gain1;

  /* Derivatives for Integrator: '<S1>/ Pitch_Hizi' */
  _rtXdot->Pitch_Hizi_CSTATE = TailSitter_Sim_B.Gain2;

  /* Derivatives for Integrator: '<S1>/Yaw_Hizi ' */
  _rtXdot->Yaw_Hizi_CSTATE = TailSitter_Sim_B.Gain3;

  /* Derivatives for Integrator: '<S1>/Z_Ekseni_Hizi' */
  _rtXdot->Z_Ekseni_Hizi_CSTATE = TailSitter_Sim_B.Gain;
}

/* Model initialize function */
void TailSitter_Sim_initialize(void)
{
  /* Registration code */
  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&TailSitter_Sim_M->solverInfo,
                          &TailSitter_Sim_M->Timing.simTimeStep);
    rtsiSetTPtr(&TailSitter_Sim_M->solverInfo, &rtmGetTPtr(TailSitter_Sim_M));
    rtsiSetStepSizePtr(&TailSitter_Sim_M->solverInfo,
                       &TailSitter_Sim_M->Timing.stepSize0);
    rtsiSetdXPtr(&TailSitter_Sim_M->solverInfo, &TailSitter_Sim_M->derivs);
    rtsiSetContStatesPtr(&TailSitter_Sim_M->solverInfo, (real_T **)
                         &TailSitter_Sim_M->contStates);
    rtsiSetNumContStatesPtr(&TailSitter_Sim_M->solverInfo,
      &TailSitter_Sim_M->Sizes.numContStates);
    rtsiSetNumPeriodicContStatesPtr(&TailSitter_Sim_M->solverInfo,
      &TailSitter_Sim_M->Sizes.numPeriodicContStates);
    rtsiSetPeriodicContStateIndicesPtr(&TailSitter_Sim_M->solverInfo,
      &TailSitter_Sim_M->periodicContStateIndices);
    rtsiSetPeriodicContStateRangesPtr(&TailSitter_Sim_M->solverInfo,
      &TailSitter_Sim_M->periodicContStateRanges);
    rtsiSetContStateDisabledPtr(&TailSitter_Sim_M->solverInfo, (boolean_T**)
      &TailSitter_Sim_M->contStateDisabled);
    rtsiSetErrorStatusPtr(&TailSitter_Sim_M->solverInfo, (&rtmGetErrorStatus
      (TailSitter_Sim_M)));
    rtsiSetRTModelPtr(&TailSitter_Sim_M->solverInfo, TailSitter_Sim_M);
  }

  rtsiSetSimTimeStep(&TailSitter_Sim_M->solverInfo, MAJOR_TIME_STEP);
  rtsiSetIsMinorTimeStepWithModeChange(&TailSitter_Sim_M->solverInfo, false);
  rtsiSetIsContModeFrozen(&TailSitter_Sim_M->solverInfo, false);
  TailSitter_Sim_M->intgData.y = TailSitter_Sim_M->odeY;
  TailSitter_Sim_M->intgData.f[0] = TailSitter_Sim_M->odeF[0];
  TailSitter_Sim_M->intgData.f[1] = TailSitter_Sim_M->odeF[1];
  TailSitter_Sim_M->intgData.f[2] = TailSitter_Sim_M->odeF[2];
  TailSitter_Sim_M->contStates = ((X_TailSitter_Sim_T *) &TailSitter_Sim_X);
  TailSitter_Sim_M->contStateDisabled = ((XDis_TailSitter_Sim_T *)
    &TailSitter_Sim_XDis);
  TailSitter_Sim_M->Timing.tStart = (0.0);
  rtsiSetSolverData(&TailSitter_Sim_M->solverInfo, (void *)
                    &TailSitter_Sim_M->intgData);
  rtsiSetSolverName(&TailSitter_Sim_M->solverInfo,"ode3");
  rtmSetTPtr(TailSitter_Sim_M, &TailSitter_Sim_M->Timing.tArray[0]);
  TailSitter_Sim_M->Timing.stepSize0 = 0.01;

  /* InitializeConditions for TransferFcn: '<S2>/Transfer Fcn' */
  TailSitter_Sim_X.TransferFcn_CSTATE = 0.0;

  /* InitializeConditions for TransferFcn: '<S2>/Transfer Fcn1' */
  TailSitter_Sim_X.TransferFcn1_CSTATE = 0.0;

  /* InitializeConditions for TransferFcn: '<S2>/Transfer Fcn2' */
  TailSitter_Sim_X.TransferFcn2_CSTATE = 0.0;

  /* InitializeConditions for TransferFcn: '<S2>/Transfer Fcn3' */
  TailSitter_Sim_X.TransferFcn3_CSTATE = 0.0;

  /* InitializeConditions for Integrator: '<S3>/Integrator' */
  TailSitter_Sim_X.Integrator_CSTATE[0] = 0.0;
  TailSitter_Sim_X.Integrator_CSTATE[1] = 0.0;
  TailSitter_Sim_X.Integrator_CSTATE[2] = 0.0;

  /* InitializeConditions for Integrator: '<S3>/Integrator1' */
  TailSitter_Sim_X.Integrator1_CSTATE = 0.0;

  /* InitializeConditions for Integrator: '<S1>/Roll_Hizi ' */
  TailSitter_Sim_X.Roll_Hizi_CSTATE = 0.0;

  /* InitializeConditions for Integrator: '<S1>/ Pitch_Hizi' */
  TailSitter_Sim_X.Pitch_Hizi_CSTATE = 0.0;

  /* InitializeConditions for Integrator: '<S1>/Yaw_Hizi ' */
  TailSitter_Sim_X.Yaw_Hizi_CSTATE = 0.0;

  /* InitializeConditions for Integrator: '<S1>/Z_Ekseni_Hizi' */
  TailSitter_Sim_X.Z_Ekseni_Hizi_CSTATE = 0.0;
}

/* Model terminate function */
void TailSitter_Sim_terminate(void)
{
  /* (no terminate code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
