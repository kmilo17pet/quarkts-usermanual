/*define the FSM application event-signals*/
#define SIGNAL_BUTTON_PRESSED  ( (qSM_Signal_t)1 )
#define SIGNAL_TIMEOUT         ( (qSM_Signal_t)2 )

qTask_t LED_Task; /*The task node*/
qSM_t LED_FSM; /*The state-machine handler*/
qSM_TransitionTable_t LED_FSM_TransTable; /*the FSM transition table*/
/*create the transition table entries with the desired FSM behavior*/
qSM_Transition_t LED_FSM_TransEntries[] = {
{ State_LED_Off, SIGNAL_BUTTON_PRESSED, State_LED_On, NULL, NULL, NULL },
{ State_LED_On, SIGNAL_TIMEOUT, State_LED_Off, NULL, NULL, NULL },
{ State_LED_On, SIGNAL_BUTTON_PRESSED, State_LED_Blink, NULL, NULL, NULL },
{ State_LED_Blink, SIGNAL_TIMEOUT, State_LED_Off, NULL, NULL, NULL },
{ State_LED_Blink, SIGNAL_BUTTON_PRESSED, State_LED_Off, NULL, NULL, NULL }
};
/*create the instance and the memory area for the signal-queue*/
qQueue_t LED_SigQueue;
qSM_Signal_t LED_FSM_SignalArea[4];
/*the timeout object*/
qSTimer_t LED_FSM_Timeout = QSTIMER_INITIALIZER;