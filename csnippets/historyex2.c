qStateMachine_Setup( &super, state_top_callback, &state1, NULL, NULL );
qStateMachine_StateSubscribe( &super, &state1, NULL, state1_callback, NULL, NULL ); 
qStateMachine_StateSubscribe( &super, &state2, NULL, state2_callback, &state3, NULL ); 
qStateMachine_StateSubscribe( &super, &state3, &state2, state3_callback, NULL, NULL ); 
qStateMachine_StateSubscribe( &super, &state4, &state2, state4_callback, &state5, NULL ); 
qStateMachine_StateSubscribe( &super, &state5, &state4, state5_callback, NULL, NULL ); 
qStateMachine_StateSubscribe( &super, &state6, &state4, state6_callback, NULL, NULL ); 

qQueue_Setup( &sigqueue, topsm_sig_stack, sizeof(qSM_Signal_t), qFLM_ArraySize(topsm_sig_stack) );
qStateMachine_InstallSignalQueue( &super, &sigqueue );
qStateMachine_InstallTransitionTable( &super, table, qFLM_ArraySize(table) );
          
qOS_Add_StateMachineTask(  &SMTask, &super, qMedium_Priority, 0.1f, qEnabled, NULL  );   