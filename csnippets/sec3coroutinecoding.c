void CoroutineTask_Callback( qEvent_t e ){
    qCR_Begin{        
        if( EventNotComing() ){
            qCR_Yield;
        }
        DoTheEventProcessing();
    }qCR_End;
}