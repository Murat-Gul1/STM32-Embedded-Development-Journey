/*
 * File: TailSitter_Sim.h
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

#ifndef TailSitter_Sim_h_
#define TailSitter_Sim_h_
#ifndef TailSitter_Sim_COMMON_INCLUDES_
#define TailSitter_Sim_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#include "math.h"
#endif                                 /* TailSitter_Sim_COMMON_INCLUDES_ */

#include "TailSitter_Sim_types.h"
#include <string.h>

/* Macros for accessing real-time model data structure */
#ifndef rtmGetContStateDisabled
#define rtmGetContStateDisabled(rtm)   ((rtm)->contStateDisabled)
#endif

#ifndef rtmSetContStateDisabled
#define rtmSetContStateDisabled(rtm, val) ((rtm)->contStateDisabled = (val))
#endif

#ifndef rtmGetContStates
#define rtmGetContStates(rtm)          ((rtm)->contStates)
#endif

#ifndef rtmSetContStates
#define rtmSetContStates(rtm, val)     ((rtm)->contStates = (val))
#endif

#ifndef rtmGetContTimeOutputInconsistentWithStateAtMajorStepFlag
#define rtmGetContTimeOutputInconsistentWithStateAtMajorStepFlag(rtm) ((rtm)->CTOutputIncnstWithState)
#endif

#ifndef rtmSetContTimeOutputInconsistentWithStateAtMajorStepFlag
#define rtmSetContTimeOutputInconsistentWithStateAtMajorStepFlag(rtm, val) ((rtm)->CTOutputIncnstWithState = (val))
#endif

#ifndef rtmGetDerivCacheNeedsReset
#define rtmGetDerivCacheNeedsReset(rtm) ((rtm)->derivCacheNeedsReset)
#endif

#ifndef rtmSetDerivCacheNeedsReset
#define rtmSetDerivCacheNeedsReset(rtm, val) ((rtm)->derivCacheNeedsReset = (val))
#endif

#ifndef rtmGetIntgData
#define rtmGetIntgData(rtm)            ((rtm)->intgData)
#endif

#ifndef rtmSetIntgData
#define rtmSetIntgData(rtm, val)       ((rtm)->intgData = (val))
#endif

#ifndef rtmGetOdeF
#define rtmGetOdeF(rtm)                ((rtm)->odeF)
#endif

#ifndef rtmSetOdeF
#define rtmSetOdeF(rtm, val)           ((rtm)->odeF = (val))
#endif

#ifndef rtmGetOdeY
#define rtmGetOdeY(rtm)                ((rtm)->odeY)
#endif

#ifndef rtmSetOdeY
#define rtmSetOdeY(rtm, val)           ((rtm)->odeY = (val))
#endif

#ifndef rtmGetPeriodicContStateIndices
#define rtmGetPeriodicContStateIndices(rtm) ((rtm)->periodicContStateIndices)
#endif

#ifndef rtmSetPeriodicContStateIndices
#define rtmSetPeriodicContStateIndices(rtm, val) ((rtm)->periodicContStateIndices = (val))
#endif

#ifndef rtmGetPeriodicContStateRanges
#define rtmGetPeriodicContStateRanges(rtm) ((rtm)->periodicContStateRanges)
#endif

#ifndef rtmSetPeriodicContStateRanges
#define rtmSetPeriodicContStateRanges(rtm, val) ((rtm)->periodicContStateRanges = (val))
#endif

#ifndef rtmGetZCCacheNeedsReset
#define rtmGetZCCacheNeedsReset(rtm)   ((rtm)->zCCacheNeedsReset)
#endif

#ifndef rtmSetZCCacheNeedsReset
#define rtmSetZCCacheNeedsReset(rtm, val) ((rtm)->zCCacheNeedsReset = (val))
#endif

#ifndef rtmGetdX
#define rtmGetdX(rtm)                  ((rtm)->derivs)
#endif

#ifndef rtmSetdX
#define rtmSetdX(rtm, val)             ((rtm)->derivs = (val))
#endif

#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

#ifndef rtmGetStopRequested
#define rtmGetStopRequested(rtm)       ((rtm)->Timing.stopRequestedFlag)
#endif

#ifndef rtmSetStopRequested
#define rtmSetStopRequested(rtm, val)  ((rtm)->Timing.stopRequestedFlag = (val))
#endif

#ifndef rtmGetStopRequestedPtr
#define rtmGetStopRequestedPtr(rtm)    (&((rtm)->Timing.stopRequestedFlag))
#endif

#ifndef rtmGetT
#define rtmGetT(rtm)                   (rtmGetTPtr((rtm))[0])
#endif

#ifndef rtmGetTPtr
#define rtmGetTPtr(rtm)                ((rtm)->Timing.t)
#endif

#ifndef rtmGetTStart
#define rtmGetTStart(rtm)              ((rtm)->Timing.tStart)
#endif

/* Block signals (default storage) */
typedef struct {
  real_T dv[9];
  real_T rtb_MathFunction_m[4];
  real_T dv1[3];
  real_T Gain;                         /* '<S1>/Gain' */
  real_T Gain1;                        /* '<S1>/Gain1' */
  real_T Gain2;                        /* '<S1>/Gain2' */
  real_T Gain3;                        /* '<S1>/Gain3' */
  real_T Gain_c[4];                    /* '<S2>/Gain' */
  real_T Z_Ekseni_Hizi;                /* '<S1>/Z_Ekseni_Hizi' */
  real_T euler_hizlari[3];             /* '<S3>/MATLAB Function' */
} B_TailSitter_Sim_T;

/* Continuous states (default storage) */
typedef struct {
  real_T TransferFcn_CSTATE;           /* '<S2>/Transfer Fcn' */
  real_T TransferFcn1_CSTATE;          /* '<S2>/Transfer Fcn1' */
  real_T TransferFcn2_CSTATE;          /* '<S2>/Transfer Fcn2' */
  real_T TransferFcn3_CSTATE;          /* '<S2>/Transfer Fcn3' */
  real_T Integrator_CSTATE[3];         /* '<S3>/Integrator' */
  real_T Integrator1_CSTATE;           /* '<S3>/Integrator1' */
  real_T Roll_Hizi_CSTATE;             /* '<S1>/Roll_Hizi ' */
  real_T Pitch_Hizi_CSTATE;            /* '<S1>/ Pitch_Hizi' */
  real_T Yaw_Hizi_CSTATE;              /* '<S1>/Yaw_Hizi ' */
  real_T Z_Ekseni_Hizi_CSTATE;         /* '<S1>/Z_Ekseni_Hizi' */
} X_TailSitter_Sim_T;

/* State derivatives (default storage) */
typedef struct {
  real_T TransferFcn_CSTATE;           /* '<S2>/Transfer Fcn' */
  real_T TransferFcn1_CSTATE;          /* '<S2>/Transfer Fcn1' */
  real_T TransferFcn2_CSTATE;          /* '<S2>/Transfer Fcn2' */
  real_T TransferFcn3_CSTATE;          /* '<S2>/Transfer Fcn3' */
  real_T Integrator_CSTATE[3];         /* '<S3>/Integrator' */
  real_T Integrator1_CSTATE;           /* '<S3>/Integrator1' */
  real_T Roll_Hizi_CSTATE;             /* '<S1>/Roll_Hizi ' */
  real_T Pitch_Hizi_CSTATE;            /* '<S1>/ Pitch_Hizi' */
  real_T Yaw_Hizi_CSTATE;              /* '<S1>/Yaw_Hizi ' */
  real_T Z_Ekseni_Hizi_CSTATE;         /* '<S1>/Z_Ekseni_Hizi' */
} XDot_TailSitter_Sim_T;

/* State disabled  */
typedef struct {
  boolean_T TransferFcn_CSTATE;        /* '<S2>/Transfer Fcn' */
  boolean_T TransferFcn1_CSTATE;       /* '<S2>/Transfer Fcn1' */
  boolean_T TransferFcn2_CSTATE;       /* '<S2>/Transfer Fcn2' */
  boolean_T TransferFcn3_CSTATE;       /* '<S2>/Transfer Fcn3' */
  boolean_T Integrator_CSTATE[3];      /* '<S3>/Integrator' */
  boolean_T Integrator1_CSTATE;        /* '<S3>/Integrator1' */
  boolean_T Roll_Hizi_CSTATE;          /* '<S1>/Roll_Hizi ' */
  boolean_T Pitch_Hizi_CSTATE;         /* '<S1>/ Pitch_Hizi' */
  boolean_T Yaw_Hizi_CSTATE;           /* '<S1>/Yaw_Hizi ' */
  boolean_T Z_Ekseni_Hizi_CSTATE;      /* '<S1>/Z_Ekseni_Hizi' */
} XDis_TailSitter_Sim_T;

#ifndef ODE3_INTG
#define ODE3_INTG

/* ODE3 Integration Data */
typedef struct {
  real_T *y;                           /* output */
  real_T *f[3];                        /* derivatives */
} ODE3_IntgData;

#endif

/* Constant parameters (default storage) */
typedef struct {
  /* Expression: M_alloc
   * Referenced by: '<S4>/Gain'
   */
  real_T Gain_Gain[16];
} ConstP_TailSitter_Sim_T;

/* Real-time Model Data Structure */
struct tag_RTM_TailSitter_Sim_T {
  const char_T *errorStatus;
  RTWSolverInfo solverInfo;
  X_TailSitter_Sim_T *contStates;
  int_T *periodicContStateIndices;
  real_T *periodicContStateRanges;
  real_T *derivs;
  XDis_TailSitter_Sim_T *contStateDisabled;
  boolean_T zCCacheNeedsReset;
  boolean_T derivCacheNeedsReset;
  boolean_T CTOutputIncnstWithState;
  real_T odeY[12];
  real_T odeF[3][12];
  ODE3_IntgData intgData;

  /*
   * Sizes:
   * The following substructure contains sizes information
   * for many of the model attributes such as inputs, outputs,
   * dwork, sample times, etc.
   */
  struct {
    int_T numContStates;
    int_T numPeriodicContStates;
    int_T numSampTimes;
  } Sizes;

  /*
   * Timing:
   * The following substructure contains information regarding
   * the timing information for the model.
   */
  struct {
    uint32_T clockTick0;
    time_T stepSize0;
    uint32_T clockTick1;
    time_T tStart;
    SimTimeStep simTimeStep;
    boolean_T stopRequestedFlag;
    time_T *t;
    time_T tArray[2];
  } Timing;
};

/* Block signals (default storage) */
extern B_TailSitter_Sim_T TailSitter_Sim_B;

/* Continuous states (default storage) */
extern X_TailSitter_Sim_T TailSitter_Sim_X;

/* Disabled states (default storage) */
extern XDis_TailSitter_Sim_T TailSitter_Sim_XDis;

/* Constant parameters (default storage) */
extern const ConstP_TailSitter_Sim_T TailSitter_Sim_ConstP;

/* Model entry point functions */
extern void TailSitter_Sim_initialize(void);
extern void TailSitter_Sim_step(void);
extern void TailSitter_Sim_terminate(void);

/* Exported data declaration */

/* Data with Exported storage */
extern real_T TailSitter_Sim_Motor_PWM[4];/* '<Root>/Motor_PWM' */
extern real_T TailSitter_Sim_Sensor_Verileri[4];/* '<Root>/Sensor_Verileri' */

/* Real-time Model object */
extern RT_MODEL_TailSitter_Sim_T *const TailSitter_Sim_M;

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'TailSitter_Sim'
 * '<S1>'   : 'TailSitter_Sim/Dinamik Model'
 * '<S2>'   : 'TailSitter_Sim/Itki Modeli'
 * '<S3>'   : 'TailSitter_Sim/Kinematik Model'
 * '<S4>'   : 'TailSitter_Sim/Kontrol Etkinlik Modeli'
 * '<S5>'   : 'TailSitter_Sim/Kinematik Model/MATLAB Function'
 */
#endif                                 /* TailSitter_Sim_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
