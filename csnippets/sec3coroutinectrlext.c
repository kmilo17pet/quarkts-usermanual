qCR_Handle_t xHandleCR = NULL; /*NULL initialization are strictly necessary*/

/*===================================================================*/
void AnotherTask_Callback( qEvent_t e){
    int UserInput = 0;
    if( e->FirstIteration ){
        qCR_ExternControl( xHandleCR, qCR_RESUME, 0 );
    }
    if( e->LastIteration ){
        qCR_ExternControl( xHandleCR, qCR_SUSPEND, 0 );
    }
    UserInput = GetTerminalInput( );
    if( UserInput == USR_RESTART ){
        qCR_ExternControl( xHandleCR, qCR_RESTART, 0 );
    }
    Perform_AnotherTask_Activities();
}
/*===================================================================*/
void CoroutineTask_Callback( qEvent_t e ){
    qCR_BeginWithHandle( xHandleCR ){ /*externally controlled*/       
        if( EventNotComing() ){
            qCR_Yield;
        }
        RunFirstJob();
        qCR_Delay( WAIT_TIME );
        SecondJobStatus = RunSecondJob();
        qCR_TimedWaitUntil( JobFlag == JOB_SUCCESS, JOB_TIMEOUT );
        CleanUpStatus = CleanupJob();
        qCR_WaitUntil( SomeVar > SomeValue );
    }qCR_End;
}