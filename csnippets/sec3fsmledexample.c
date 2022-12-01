qSM_Status_t State_LEDOff_Callback( qSM_Handler_t h ) {
    switch ( h->Signal ) {
        case QSM_SIGNAL_ENTRY:
            BSP_LED_OFF();
            break;
        case QSM_SIGNAL_EXIT: case QSM_SIGNAL_START: /*Ignore*/
            break;
        default:
            if ( BUTTON_PRESSED ) {
                h->NextState = &State_LEDOn;
            }
            break;
    }
    return qSM_STATUS_EXIT_SUCCESS;
}
/*---------------------------------------------------------------------*/
qSM_Status_t State_LEDOn_Callback( qSM_Handler_t h ) {
    static qSTimer_t timeout;
    switch ( h->Signal ) {
        case QSM_SIGNAL_ENTRY:
            qSTimer_Set( &timeout, 10.0f ); /*STimer gets armed*/
            BSP_LED_ON();
            break;
        case QSM_SIGNAL_EXIT: case QSM_SIGNAL_START: /*Ignore*/
            break;
        default:
            if ( qSTimer_Expired( &timeout) ) { /*check if the timeout expired*/
                h->NextState = &State_LEDOff;
            }
            if ( BUTTON_PRESSED ) {
                h->NextState = &State_LEDBlink;
            }
            break;
    }
    return qSM_STATUS_EXIT_SUCCESS;
}
/*---------------------------------------------------------------------*/
qSM_Status_t State_LEDBlink_Callback( qSM_Handler_t h ) {
    static qSTimer_t timeout;
    static qSTimer_t blinktime;
    
    switch ( m->Signal ) {
        case QSM_SIGNAL_ENTRY:
            qSTimer_Set( &timeout, 10.0f );
            break;
        case QSM_SIGNAL_EXIT: case QSM_SIGNAL_START: /*Ignore*/
            break;    
        default:
            if ( qSTimer_Expired( &timeout ) || BUTTON_PRESSED ) {
                h->NextState = &State_LEDOff;
            }
            if ( qSTimer_FreeRun( &blinktime, 0.5f ) ) {
               BSP_LED_TOGGLE();
            }
            break;
    }
    return qSM_STATUS_EXIT_SUCCESS;
}