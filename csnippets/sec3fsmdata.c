qSM_Status_t Example_State( qSM_Handler_t m ){
    qEvent_t e = m->Data; 
    /* Get the event info of the task that owns this state-machine*/
    switch( m->Signal ){
        case QSM_SIGNAL_ENTRY:
            break;
        case QSM_SIGNAL_EXIT:
            break;
        default:
            switch( e->Trigger ){
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
    return qSM_EXIT_SUCCESS;
}