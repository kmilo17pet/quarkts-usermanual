/*define the FSM application event-signals*/
#define SIGNAL_BUTTON_PRESSED   ( (qSM_Signal_t)1 )
#define SIGNAL_TIMEOUT          (QSM_SIGNAL_TIMEOUT(0))
#define SIGNAL_BLINK            (QSM_SIGNAL_TIMEOUT(1))

qTask_t LED_Task; /*The task node*/
qSM_t LED_FSM; /*The state-machine handler*/
qSM_State_t State_LEDOff, State_LEDOn, State_LEDBlink;
qQueue_t LEDsigqueue; /*the signal-queue*/ 
qSM_Signal_t led_sig_stack[5];  /*the signal-queue storage area*/
qSM_TimeoutSpec_t tm_spectimeout;

/*create the transition tables for every state*/
qSM_Transition_t LEDOff_transitions[] = {
    { SIGNAL_BUTTON_PRESSED, NULL, &State_LEDOn    ,0},
};

qSM_Transition_t LEDOn_transitions[] = {
    { SIGNAL_TIMEOUT,        NULL, &State_LEDOff   ,0},
    { SIGNAL_BUTTON_PRESSED, NULL, &State_LEDBlink ,0},
};

qSM_Transition_t LEDBlink_transitions[] = {
    { SIGNAL_TIMEOUT,        NULL, &State_LEDOff   ,0},
    { SIGNAL_BUTTON_PRESSED, NULL, &State_LEDOff   ,0}
};

/*define the timeout specifications */
qSM_TimeoutStateDefinition_t LedOn_Timeouts[]={
    { 10.0f,  QSM_TSOPT_INDEX(0) | QSM_TSOPT_SET_ENTRY | QSM_TSOPT_RST_EXIT  },
};

qSM_TimeoutStateDefinition_t LEDBlink_timeouts[]={
    { 10.0f,  QSM_TSOPT_INDEX(0) | QSM_TSOPT_SET_ENTRY | QSM_TSOPT_RST_EXIT  },
    { 0.5f,   QSM_TSOPT_INDEX(1) | QSM_TSOPT_SET_ENTRY | QSM_TSOPT_RST_EXIT | QSM_TSOPT_PERIODIC  },
};
