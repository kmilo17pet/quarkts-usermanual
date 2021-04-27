qStateMachine_Setup( &LED_FSM, NULL, &State_LEDOff, NULL, NULL ); 
qStateMachine_StateSubscribe( &LED_FSM, &State_LEDOff, NULL, State_LEDOff_Callback, NULL, qFalse ); 
qStateMachine_StateSubscribe( &LED_FSM, &State_LEDOn, NULL, State_LEDOn_Callback, NULL, qFalse );
qStateMachine_StateSubscribe( &LED_FSM, &State_LEDBlink, NULL, State_LEDBlink_Callback, NULL, qFalse ); 

qQueue_Setup( &LEDsigqueue, led_sig_stack, sizeof(qSM_Signal_t), qFLM_ArraySize(led_sig_stack) );
qStateMachine_InstallSignalQueue( &LED_FSM, &LEDsigqueue );
qStateMachine_InstallTransitionTable( &LED_FSM, LED_TTableEntries, qFLM_ArraySize(LED_TTableEntries) );
qStateMachine_InstallTimeoutSpec( &LED_FSM, &tm_spectimeout, LED_timeouts, qFLM_ArraySize(LED_timeouts) );
qOS_Add_StateMachineTask(  &LED_Task, &LED_FSM, qMedium_Priority, 0.1f, qEnabled, NULL  );   