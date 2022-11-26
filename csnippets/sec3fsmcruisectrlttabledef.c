#define  SIGNAL_ENGINE_ON           ((qSM_SigId_t)(1))   
#define  SIGNAL_ACCEL               ((qSM_SigId_t)(2))
#define  SIGNAL_RESUME              ((qSM_SigId_t)(3))
#define  SIGNAL_OFF                 ((qSM_SigId_t)(4))
#define  SIGNAL_BRAKE_PRESSED       ((qSM_SigId_t)(5))
#define  SIGNAL_CRUISE              ((qSM_SigId_t)(6))     
#define  SIGNAL_REACHED_CRUISING    ((qSM_SigId_t)(7))
#define  SIGNAL_ENGINE_OFF          ((qSM_SigId_t)(8))

qTask_t CruiseControlTask;
qSM_t Top_SM;

/*highest level states*/
qSM_State_t state_idle, state_initial, state_cruisingoff, state_automatedcontrol;
/*states inside the state_automatedcontrol*/
qSM_State_t state_accelerating, state_cruising, state_resuming;

qQueue_t top_sigqueue;
qSM_Signal_t topsm_sig_stack[10];

/*=======================================================================*/
/*                             TRANSITION TABLES                         */
/*=======================================================================*/
qSM_Transition_t idle_transitions[] =
{
{ SIGNAL_ENGINE_ON, SigAct_ClearDesiredSpeed, &state_initial      ,0, NULL }
};

qSM_Transition_t initial_transitions[] =
{
{ SIGNAL_ACCEL,     SigAct_BrakeOff,          &state_accelerating ,0, NULL }
};

qSM_Transition_t accel_transitions[] =
{
{ SIGNAL_CRUISE,     NULL,                    &state_cruising     ,0, NULL }
};

qSM_Transition_t cruising_transitions[] =
{
{ SIGNAL_OFF,       NULL,                     &state_cruisingoff  ,0, NULL }
{ SIGNAL_ACCEL,     NULL,                     &state_accelerating ,0, NULL }
};

qSM_Transition_t resuming_transitions[] =
{
{ SIGNAL_ACCEL,     NULL,                     &state_accelerating ,0, NULL }
};

qSM_Transition_t cruisingoff_transitions[] =
{   
{ SIGNAL_ACCEL,      SigAct_BrakeOff,         &state_accelerating ,0, NULL },
{ SIGNAL_RESUME,     SigAct_BrakeOff,         &state_resuming     ,0, NULL },
{ SIGNAL_ENGINE_OFF, NULL,                    &state_idle         ,0, NULL }      
};

qSM_Transition_t automated_transitions[] =
{       
{ SIGNAL_BRAKE_PRESSED,   NULL,               &state_cruisingoff  ,0, NULL } 
};
/*---------------------------------------------------------------------*/
