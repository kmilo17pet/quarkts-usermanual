#define  SIGNAL_ENGINE_ON           ((qSM_Signal_t)(1))   
#define  SIGNAL_ACCEL               ((qSM_Signal_t)(2))
#define  SIGNAL_RESUME              ((qSM_Signal_t)(3))
#define  SIGNAL_OFF                 ((qSM_Signal_t)(4))
#define  SIGNAL_BRAKE_PRESSED       ((qSM_Signal_t)(5))
#define  SIGNAL_CRUISE              ((qSM_Signal_t)(6))     
#define  SIGNAL_REACHED_CRUISING    ((qSM_Signal_t)(7))
#define  SIGNAL_ENGINE_OFF          ((qSM_Signal_t)(8))

qTask_t CruiseControlTask;
qSM_t Top_SM;

/*highest level states*/
qSM_State_t state_idle, state_initial, state_cruisingoff, state_automatedcontrol;
/*states inside the state_automatedcontrol*/
qSM_State_t state_accelerating, state_cruising, state_resuming;

qQueue_t top_sigqueue;
qSM_Signal_t topsm_sig_stack[10];

/*=======================================================================*/
/*                             TRANSITION TABLE                          */
/*=======================================================================*/
qSM_Transition_t table[] =
{
{ &state_idle, SIGNAL_ENGINE_ON, SigAct_ClearDesiredSpeed, &state_initial },
{ &state_initial, SIGNAL_ACCEL, SigAct_BrakeOff, &state_accelerating },
{ &state_accelerating, SIGNAL_CRUISE, NULL, &state_cruising },    
{ &state_cruising, SIGNAL_OFF, NULL, &state_cruisingoff },  
{ &state_cruising, SIGNAL_ACCEL, NULL, &state_accelerating }, 
{ &state_resuming, SIGNAL_ACCEL, NULL, &state_accelerating }, 
{ &state_cruisingoff, SIGNAL_ACCEL, SigAct_BrakeOff, &state_accelerating }, 
{ &state_cruisingoff, SIGNAL_RESUME, SigAct_BrakeOff, &state_resuming },  
{ &state_cruisingoff, SIGNAL_ENGINE_OFF, NULL, &state_idle },      
{ &state_automatedcontrol, SIGNAL_BRAKE_PRESSED, NULL, &state_cruisingoff },   
};
/*---------------------------------------------------------------------*/
