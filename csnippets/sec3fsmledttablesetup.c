qOS_Add_StateMachineTask( &LED_Task, qHigh_Priority, 0.1, &LED_FSM, 
                          State_LED_Off, SurroundingState_LED,
                          qEnabled, NULL );
qStateMachine_TransitionTableInstall( &LED_FSM, &LED_FSM_TransTable,   
                                     LED_FSM_TransEntries, 5 );
qStateMachine_SignalQueueSetup( &LED_FSM, &LED_SigQueue, LED_FSM_SignalArea, 
                                qFLM_ArraySize(LED_FSM_SignalArea) ):
qOS_StateMachineTask_SigCon( &LED_Task ); /*improve table signal-response*/       