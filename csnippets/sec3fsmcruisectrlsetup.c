qStateMachine_Setup( &Top_SM, state_top_callback, &state_idle, NULL, NULL );
/*subscribe to the highest level states*/
qStateMachine_StateSubscribe( &Top_SM, &state_idle, NULL, state_idle_callback, NULL, qFalse ); 
qStateMachine_StateSubscribe( &Top_SM, &state_initial, NULL, state_initial_callback, NULL, qFalse ); 
qStateMachine_StateSubscribe( &Top_SM, &state_cruisingoff, NULL, state_cruisingoff_callback, NULL, qFalse );
qStateMachine_StateSubscribe( &Top_SM, &state_automatedcontrol, NULL, state_automatedcontrol_callback, NULL, qFalse );
/*subscribe to the states within the state_automatedcontrol*/
qStateMachine_StateSubscribe( &Top_SM, &state_accelerating, &state_automatedcontrol, state_accelerating_callback, NULL, qFalse );
qStateMachine_StateSubscribe( &Top_SM, &state_resuming, &state_automatedcontrol, state_resuming_callback, NULL, qFalse );
qStateMachine_StateSubscribe( &Top_SM, &state_cruising, &state_automatedcontrol, state_cruising_callback, NULL, qFalse );

qQueue_Setup( &top_sigqueue, topsm_sig_stack, sizeof(qSM_Signal_t), qFLM_ArraySize(topsm_sig_stack) );
qStateMachine_InstallSignalQueue( &Top_SM, &top_sigqueue );
qStateMachine_InstallTransitionTable( &Top_SM, table, qFLM_ArraySize(table) );
qOS_Add_StateMachineTask(  &CruiseControlTask, &Top_SM, qMedium_Priority, 0.1f, qEnabled, NULL  );  