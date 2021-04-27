qSM_Status_t State_LEDOff_Callback( qSM_Handler_t h ){
    switch( h->Signal ){
        case QSM_SIGNAL_ENTRY:
            BSP_LED_OFF();
            break;
        default:
            break;
    }
    return qSM_STATUS_EXIT_SUCCESS;
}
/*---------------------------------------------------------------------*/
qSM_Status_t State_LEDOn_Callback( qSM_Handler_t h ){
    switch( h->Signal ){
        case QSM_SIGNAL_ENTRY:
            BSP_LED_ON();
            break;
        default:
            break;    
    }
    return qSM_STATUS_EXIT_SUCCESS;
}
/*---------------------------------------------------------------------*/
qSM_Status_t State_LEDBlink_Callback( qSM_Handler_t h ){
    switch( h->Signal ){
        case SIGNAL_BLINK:
            BSP_LED_TOGGLE();
            break;
        default:
            break;        
    }
    return qSM_STATUS_EXIT_SUCCESS;
}