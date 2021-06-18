qStateMachine_Setup( &super, state_top_callback, &state1, NULL, NULL );
qStateMachine_StateSubscribe( &super, &state1, QSM_STATE_TOP, state1_callback, NULL, NULL ); 
qStateMachine_StateSubscribe( &super, &state2, QSM_STATE_TOP, state2_callback, &state3, NULL ); 
qStateMachine_StateSubscribe( &super, &state3, &state2, state3_callback, NULL, NULL ); 
qStateMachine_StateSubscribe( &super, &state4, &state2, state4_callback, &state5, NULL ); 
qStateMachine_StateSubscribe( &super, &state5, &state4, state5_callback, NULL, NULL ); 
qStateMachine_StateSubscribe( &super, &state6, &state4, state6_callback, NULL, NULL ); 

qQueue_Setup( &sigqueue, topsm_sig_stack, sizeof(qSM_Signal_t), qFLM_ArraySize(topsm_sig_stack) );
qStateMachine_InstallSignalQueue( &super, &sigqueue );

qStateMachine_Set_StateTransitions( &state1, state1_transitions, qFLM_ArraySize(state1_transitions) );
qStateMachine_Set_StateTransitions( &state2, state2_transitions, qFLM_ArraySize(state2_transitions) );
qStateMachine_Set_StateTransitions( &state3, state3_transitions, qFLM_ArraySize(state3_transitions) );
qStateMachine_Set_StateTransitions( &state5, state5_transitions, qFLM_ArraySize(state5_transitions) );

qOS_Add_StateMachineTask(  &SMTask, &super, qMedium_Priority, 0.1f, qEnabled, NULL  );   