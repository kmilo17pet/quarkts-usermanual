qStateMachine_Setup( &LED_FSM, NULL, &State_LEDOff, NULL, NULL ); 
qStateMachine_StateSubscribe( &LED_FSM, &State_LEDOff, QSM_STATE_TOP, State_LEDOff_Callback, NULL, NULL ); 
qStateMachine_StateSubscribe( &LED_FSM, &State_LEDOn, QSM_STATE_TOP, State_LEDOn_Callback, NULL, NULL );
qStateMachine_StateSubscribe( &LED_FSM, &State_LEDBlink, QSM_STATE_TOP, State_LEDBlink_Callback, NULL, NULL ); 

qQueue_Setup( &LEDsigqueue, led_sig_stack, sizeof(qSM_Signal_t), qFLM_ArraySize(led_sig_stack) );
qStateMachine_InstallSignalQueue( &LED_FSM, &LEDsigqueue );

qStateMachine_InstallTimeoutSpec( &LED_FSM, &tm_spectimeout );
qStateMachine_Set_StateTimeouts( &State_LEDOn, LedOn_Timeouts, qFLM_ArraySize(LedOn_Timeouts) );
qStateMachine_Set_StateTimeouts( &State_LEDBlink, LEDBlink_timeouts, qFLM_ArraySize(LEDBlink_timeouts) );

qStateMachine_Set_StateTransitions( &State_LEDOff, LEDOff_transitions, qFLM_ArraySize(LEDOff_transitions) );
qStateMachine_Set_StateTransitions( &State_LEDOn, LEDOn_transitions, qFLM_ArraySize(LEDOn_transitions) );
qStateMachine_Set_StateTransitions( &State_LEDBlink, LEDBlink_transitions, qFLM_ArraySize(LEDBlink_transitions) );

qOS_Add_StateMachineTask(  &LED_Task, &LED_FSM, qMedium_Priority, 0.1f, qEnabled, NULL  );   