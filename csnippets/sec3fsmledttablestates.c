void SubState_LED_BeforeAny( qSM_Handler_t m ){
    if( qSTimer_Expired( &LED_FSM_Timeout ) ){
        qStateMachine_SendSignal( &LED_FSM, SIGNAL_TIMEOUT, qFalse );
    }
}
/*---------------------------------------------------------------------*/
qSM_Status_t State_LED_Off( qSM_Handler_t m ){
    switch( m->Signal ){
        case QSM_SIGNAL_ENTRY:
            BSP_LED_OFF();
            break;
        default:
            break;
    }
    return qSM_EXIT_SUCCESS;
}
/*---------------------------------------------------------------------*/
qSM_Status_t State_LED_On( qSM_Handler_t m ){
    switch( m->Signal ){
        case QSM_SIGNAL_ENTRY:
            qSTimer_Set( &LED_FSM_Timeout, 10.0 ); /*STimer gets armed*/
            BSP_LED_ON();
            break;
        default:
            break;    
    }
    return qSM_EXIT_SUCCESS;
}
/*---------------------------------------------------------------------*/
qSM_Status_t State_LED_Blink( qSM_Handler_t m ){
    static qSTimer_t blinktime;
    switch( m->Signal ){
        case QSM_SIGNAL_ENTRY:
            qSTimer_Set( &LED_FSM_Timeout, 10.0 );
            break;
        default:
            if( qSTimer_FreeRun( &blinktime, 0.5 ) ){
                BSP_LED_TOGGLE();
            }        
            break;        
    }
    return qSM_EXIT_SUCCESS;
}