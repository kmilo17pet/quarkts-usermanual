qSM_Status_t State_LED_Off( qSM_Handler_t m ){
    switch( m->Signal ){
        case QSM_SIGNAL_ENTRY:
            BSP_LED_OFF();
            break;
        default:
            if( BUTTON_PRESSED ){
                m->NextState = State_LED_On;
            }
            break;
    }
    return qSM_EXIT_SUCCESS;
}
/*---------------------------------------------------------------------*/
qSM_Status_t State_LED_On( qSM_Handler_t m ){
    static qSTimer_t timeout;
    switch( m->Signal ){
        case QSM_SIGNAL_ENTRY:
            qSTimer_Set( &timeout, 10.0 ); /*STimer gets armed*/
            BSP_LED_ON();
            break;
        default:
            if( qSTimer_Expired( &timeout) ){ /*check if the timeout expired*/
                m->NextState = State_LED_Off;
            }
            if( BUTTON_PRESSED ){
                m->NextState = State_LED_Blink;
            }
            break;
    }
    return qSM_EXIT_SUCCESS;
}
/*---------------------------------------------------------------------*/
qSM_Status_t State_LED_Blink( qSM_Handler_t m ){
    static qSTimer_t timeout;
    static qSTimer_t blinktime;
    
    switch( m->Signal ){
        case QSM_SIGNAL_ENTRY:
            qSTimer_Set( &timeout, 10.0 );
            break;
        default:
            if( qSTimer_Expired( &timeout ) || BUTTON_PRESSED ){
                m->NextState = State_LED_Off;
            }
            if( qSTimer_FreeRun( &blinktime, 0.5 ) ){
               BSP_LED_TOGGLE();
            }
            break;
    }
    return qSM_EXIT_SUCCESS;
}