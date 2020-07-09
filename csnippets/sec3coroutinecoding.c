void CoroutineTask_Callback( qEvent_t e ){
    qCR_Begin{        
        if( EventNotComing() ){
            qCR_Yield;
        }
        DoTheEventProcessing();
        qCRDelay( WAIT_TIME_S );
        PerformActions();
    }qCR_End;
}