qSM_SubStatesContainer_t substates;
substates.BeforeAnyState =  SubState_LED_BeforeAny;
substates.Success = NULL;
substates.Failure = NULL;
substates.Unexpected = NULL;
qOS_Add_StateMachineTask( &LED_Task, qHigh_Priority, 0.1, &LED_FSM, 
                          State_LED_Off, SubState_LED_BeforeAny, 
                          NULL, NULL, NULL, qEnabled, NULL );
                          
qStateMachine_TransitionTableInstall( &LED_FSM, &LED_FSM_TransTable,   
                                     LED_FSM_TransEntries, 5 );
qStateMachine_SignalQueueSetup( &LED_FSM, LED_FSM_SignalArea, 4 ):
/*improve the transition table signal-response*/                                    
qOS_StateMachineTask_SigCon( &LED_Task );  