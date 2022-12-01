qSM_Status_t Example_State( qSM_Handler_t h ) {
    qEvent_t e = h->Data; 
    /* Get the event info of the task that owns this state-machine*/
    switch ( h->Signal ) {
        case QSM_SIGNAL_ENTRY:
            break;
        case QSM_SIGNAL_EXIT:
            break;
        default:
            switch ( e->Trigger ) {
                case byTimeElapsed:
                    /* TODO: Code for this case */
                break;
                case byNotificationSimple:
                    /* TODO: Code for this case */
                break;
                case byQueueCount:
                    /* TODO: Code for this case */
                break;
                default: break;
            }
            /* TODO: State code */
            break;
    }
    return qSM_STATUS_EXIT_SUCCESS;
}