#define QSM_SIGNAL_ENGINE_ON            ((qSM_Signal_t)(1))
#define QSM_SIGNAL_ACCEL                ((qSM_Signal_t)(2))
#define QSM_SIGNAL_CRUISE               ((qSM_Signal_t)(3))
#define QSM_SIGNAL_OFF                  ((qSM_Signal_t)(4))
#define QSM_SIGNAL_RESUME               ((qSM_Signal_t)(5))
#define QSM_SIGNAL_BRK_PRESSED          ((qSM_Signal_t)(6))
#define QSM_SIGNAL_REACHED_CRUISING     ((qSM_Signal_t)(7))
#define QSM_SIGNAL_ENGINE_OFF           ((qSM_Signal_t)(8))

qTask_t SMTask; /* The FSM task */
qSM_t Top_SM; /* Top state machine */
qSM_t AC_SM; /* Automated Control state-machine*/
qSM_TransitionTable_t Top_ttable, AC_ttable; /*transition table handlers*/

/*=======================================================================*/
/*                             TRANSITION TABLES                         */
/*=======================================================================*/
qSM_Transition_t Top_SM_ttable[]={

{ Top_Idle_State, QSM_SIGNAL_ENGINE_ON, Top_Initial_State,  
SigAct_ClearDesiredSpeed, NULL, NULL },

{ Top_Initial_State, QSM_SIGNAL_ACCEL, Top_AutomatedControl_State, 
SigAct_CheckBrake, &AC_SM, AC_Accelerating_State },

{ Top_AutomatedControl_State, QSM_SIGNAL_BRK_PRESSED, Top_CruisingOff_State, 
NULL, NULL, NULL },

{ Top_CruisingOff_State, QSM_SIGNAL_ENGINE_OFF, Top_Idle_State, 
NULL, NULL, NULL },

{ Top_CruisingOff_State, QSM_SIGNAL_ACCEL, Top_AutomatedControl_State, 
SigAct_CheckBrake, &AC_SM, AC_Accelerating_State },

{ Top_CruisingOff_State, QSM_SIGNAL_RESUME, Top_AutomatedControl_State, 
SigAct_CheckBrake, &AC_SM, AC_Resuming_State },

};
/*---------------------------------------------------------------------*/
qSM_Transition_t AutomatedControl_SM_ttable[]={

{ AC_Accelerating_State, QSM_SIGNAL_CRUISE, AC_Cruising_State,
NULL, NULL, NULL },

{ AC_Cruising_State, QSM_SIGNAL_ACCEL, AC_Accelerating_State,
NULL, NULL, NULL },

{ AC_Resuming_State, QSM_SIGNAL_ACCEL, AC_Accelerating_State, 
NULL, NULL, NULL },

{ AC_Resuming_State, QSM_SIGNAL_REACHED_CRUISING, AC_Cruising_State,
NULL, NULL, NULL },

{ AC_Resuming_State,  QSM_SIGNAL_OFF, NULL,  
NULL, &Top_SM, Top_CruisingOff_State },    

{ AC_Cruising_State, QSM_SIGNAL_OFF, NULL, 
NULL, &Top_SM, Top_CruisingOff_State },    

};