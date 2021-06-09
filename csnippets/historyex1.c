#define SIGNAL_A        ((qSM_Signal_t)(1))
#define SIGNAL_B        ((qSM_Signal_t)(2))
#define SIGNAL_C        ((qSM_Signal_t)(3))
#define SIGNAL_D        ((qSM_Signal_t)(4))
#define SIGNAL_E        ((qSM_Signal_t)(5))
#define SIGNAL_F        ((qSM_Signal_t)(6))

qQueue_t sigqueue;
qSM_Signal_t topsm_sig_stack[10];
qSM_t super;
qSM_State_t state1, state2, state3, state4, state5, state6;

qSM_Transition_t state3_transitions[] = {
{ SIGNAL_A, NULL,   &state4,  qSM_TRANSITION_SHALLOW_HISTORY  },  
{ SIGNAL_E, NULL,   &state4,  qSM_TRANSITION_NO_HISTORY  },  
{ SIGNAL_F, NULL,   &state4,  qSM_TRANSITION_DEEP_HISTORY  },      
};

qSM_Transition_t state4_transitions[] = {
{ SIGNAL_B, NULL,   &state3,  0 }, 
};

qSM_Transition_t state1_transitions[] = {
{ SIGNAL_C, NULL,   &state2,  0 },  
};

qSM_Transition_t state2a_transitions[] = {
{ SIGNAL_D, NULL,   &state2b, 0 },  
};