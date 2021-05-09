/*define the FSM application event-signals*/
#define SIGNAL_BUTTON_PRESSED   ( (qSM_Signal_t)1 )
#define SIGNAL_TIMEOUT          (QSM_SIGNAL_TIMEOUT(0))
#define SIGNAL_BLINK            (QSM_SIGNAL_TIMEOUT(1))

qTask_t LED_Task; /*The task node*/
qSM_t LED_FSM; /*The state-machine handler*/
qSM_State_t State_LEDOff, State_LEDOn, State_LEDBlink;
qQueue_t LEDsigqueue; /*the signal-queue*/ 
qSM_Signal_t led_sig_stack[5];  /*the signal-queue storage area*/

/*create the transition table entries with the desired FSM behavior*/
qSM_Transition_t LED_TTableEntries[] = {
    { &State_LEDOff,   SIGNAL_BUTTON_PRESSED, NULL, &State_LEDOn   ,0 },
    { &State_LEDOn,    SIGNAL_TIMEOUT,        NULL, &State_LEDOff  ,0 },
    { &State_LEDOn,    SIGNAL_BUTTON_PRESSED, NULL, &State_LEDBlink,0 },
    { &State_LEDBlink, SIGNAL_TIMEOUT,        NULL, &State_LEDOff  ,0 },
    { &State_LEDBlink, SIGNAL_BUTTON_PRESSED, NULL, &State_LEDOff  ,0 }
};
/*create the timeout specifications*/
qSM_TimeoutStateDefinition_t LED_timeouts[]={
    { &State_LEDOn,     10.0f,  QSM_TSOPT_INDEX(0) | QSM_TSOPT_SET_ENTRY | QSM_TSOPT_RST_EXIT  },
    { &State_LEDBlink,  10.0f,  QSM_TSOPT_INDEX(0) | QSM_TSOPT_SET_ENTRY | QSM_TSOPT_RST_EXIT  },
    { &State_LEDBlink,  0.5f,   QSM_TSOPT_INDEX(1) | QSM_TSOPT_SET_ENTRY | QSM_TSOPT_RST_EXIT | QSM_TSOPT_PERIODIC  },
};
