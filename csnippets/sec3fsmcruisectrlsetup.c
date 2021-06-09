qStateMachine_Setup( &Top_SM, state_top_callback, &state_idle, NULL, NULL );
/*subscribe to the highest level states*/
qStateMachine_StateSubscribe( &Top_SM, &state_idle, QSM_STATE_TOP, state_idle_callback, NULL, NULL ); 
qStateMachine_StateSubscribe( &Top_SM, &state_initial, QSM_STATE_TOP, state_initial_callback, NULL, NULL ); 
qStateMachine_StateSubscribe( &Top_SM, &state_cruisingoff, QSM_STATE_TOP, state_cruisingoff_callback, NULL, NULL );
qStateMachine_StateSubscribe( &Top_SM, &state_automatedcontrol, QSM_STATE_TOP, state_automatedcontrol_callback, NULL, NULL );
/*subscribe to the states within the state_automatedcontrol*/
qStateMachine_StateSubscribe( &Top_SM, &state_accelerating, &state_automatedcontrol, state_accelerating_callback, NULL, NULL );
qStateMachine_StateSubscribe( &Top_SM, &state_resuming, &state_automatedcontrol, state_resuming_callback, NULL, NULL );
qStateMachine_StateSubscribe( &Top_SM, &state_cruising, &state_automatedcontrol, state_cruising_callback, NULL, NULL );

qQueue_Setup( &top_sigqueue, topsm_sig_stack, sizeof(qSM_Signal_t), qFLM_ArraySize(topsm_sig_stack) );
qStateMachine_InstallSignalQueue( &Top_SM, &top_sigqueue );

qStateMachine_Set_StateTransitions( &state_idle, idle_transitions, qFLM_ArraySize(idle_transitions) );
qStateMachine_Set_StateTransitions( &state_initial, initial_transitions, qFLM_ArraySize(initial_transitions) );
qStateMachine_Set_StateTransitions( &state_cruisingoff, cruisingoff_transitions, qFLM_ArraySize(cruisingoff_transitions) );
qStateMachine_Set_StateTransitions( &state_automatedcontrol, automated_transitions, qFLM_ArraySize(automated_transitions) );
qStateMachine_Set_StateTransitions( &state_accelerating, accel_transitions, qFLM_ArraySize(accel_transitions) );
qStateMachine_Set_StateTransitions( &state_resuming, resuming_transitions, qFLM_ArraySize(resuming_transitions) );
qStateMachine_Set_StateTransitions( &state_cruising, cruising_transitions, qFLM_ArraySize(cruising_transitions) );

qOS_Add_StateMachineTask(  &CruiseControlTask, &Top_SM, qMedium_Priority, 0.1f, qEnabled, NULL  );  