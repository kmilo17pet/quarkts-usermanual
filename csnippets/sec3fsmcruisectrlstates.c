/*=======================================================================*/
/*                      EVENT-SIGNAL ACTIONS AND GUARDS                  */
/*=======================================================================*/
qBool_t SigAct_ClearDesiredSpeed( qSM_Handler_t h ){
    (void)h;
    Speed_ClearDesired();
    return qTrue;
}
/*---------------------------------------------------------------------*/
qBool_t SigAct_BrakeOff( qSM_Handler_t h ){
    (void)h; /*unused*/
    return ( BSP_BREAK_READ() == OFF )? qTrue : qFalse;  /*check guard*/
}
/*=======================================================================*/
/*                  STATE CALLBACK FOR THE TOP FSM                      */
/*=======================================================================*/
qSM_Status_t state_top_callback( qSM_Handler_t h ) {
    qSM_Status_t RetVal = qSM_STATUS_EXIT_SUCCESS;
    switch( h->Signal ) {
        case QSM_SIGNAL_ENTRY:
            break;
        case QSM_SIGNAL_EXIT:
            break;           
    } 
    return RetVal;
}
/*=======================================================================*/
/*                  CALLBACKS FOR THE STATES ABOVE TOP                    */
/*=======================================================================*/
qSM_Status_t state_idle_callback( qSM_Handler_t h ){
    /*TODO : state activities*/
    return qSM_EXIT_SUCCESS;
}
/*---------------------------------------------------------------------*/
qSM_Status_t state_initial_callback( qSM_Handler_t h ){
    /*TODO : state activities*/
    return qSM_EXIT_SUCCESS;
}
/*---------------------------------------------------------------------*/
qSM_Status_t state_cruisingoff_callback( qSM_Handler_t h ){
    /*TODO : state activities*/
    return qSM_EXIT_SUCCESS;
}
/*---------------------------------------------------------------------*/
qSM_Status_t state_automatedcontrol_callback( qSM_Handler_t h ){
    /*TODO : state activities*/
    return qSM_EXIT_SUCCESS;
}
/*=======================================================================*/
/*          STATE CALLBACKS FOR THE AUTOMATED CONTROL FSM                */
/*=======================================================================*/
qSM_Status_t state_accelerating_callback( qSM_Handler_t h ){
    switch( h->Signal ){
        case QSM_SIGNAL_EXIT:
            Speed_SelectDesired();
            break;
        default:
            Speed_Increase();
            break;        
    }
    return qSM_EXIT_SUCCESS;
}
/*---------------------------------------------------------------------*/
qSM_Status_t state_resuming_callback( qSM_Handler_t h ){
    Cruising_Resume();
    return qSM_EXIT_SUCCESS;
}
/*---------------------------------------------------------------------*/
qSM_Status_t state_cruising_callback( qSM_Handler_t h ){
    Speed_Maintain();
    return qSM_EXIT_SUCCESS;
}