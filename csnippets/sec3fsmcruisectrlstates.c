/*=======================================================================*/
/*                      EVENT-SIGNAL ACTIONS AND GUARDS                  */
/*=======================================================================*/
qBool_t SigAct_ClearDesiredSpeed( qSM_Handler_t h ){
    (void)h;
    Speed_ClearDesired();
    return qTrue;
}
/*---------------------------------------------------------------------*/
qBool_t SigAct_CheckBrake( qSM_Handler_t h ){
    (void)h; /*unused*/
    return ( BSP_BREAK_READ() == OFF )? qTrue : qFalse;  /*check guard*/
}
/*=======================================================================*/
/*                  STATE CALLBACKS FOR THE TOP FSM                      */
/*=======================================================================*/
qSM_Status_t Top_Idle_State( qSM_Handler_t h ){
    /*TODO : state activities*/
    return qSM_EXIT_SUCCESS;
}
/*---------------------------------------------------------------------*/
qSM_Status_t Top_Initial_State( qSM_Handler_t h ){
    /*TODO : state activities*/
    return qSM_EXIT_SUCCESS;
}
/*---------------------------------------------------------------------*/
qSM_Status_t Top_CruisingOff_State( qSM_Handler_t h ){
    /*TODO : state activities*/
    return qSM_EXIT_SUCCESS;
}
/*---------------------------------------------------------------------*/
qSM_Status_t Top_AutomatedControl_State( qSM_Handler_t h ){
    /*TODO : state activities*/
    return qSM_EXIT_SUCCESS;
}
/*=======================================================================*/
/*          STATE CALLBACKS FOR THE AUTOMATED CONTROL FSM                */
/*=======================================================================*/
qSM_Status_t AC_Accelerating_State( qSM_Handler_t h ){
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
qSM_Status_t AC_Resuming_State( qSM_Handler_t h ){
    Cruising_Resume();
    return qSM_EXIT_SUCCESS;
}
/*---------------------------------------------------------------------*/
qSM_Status_t AC_Cruising_State( qSM_Handler_t h ){
    Speed_Maintain();
    return qSM_EXIT_SUCCESS;
}