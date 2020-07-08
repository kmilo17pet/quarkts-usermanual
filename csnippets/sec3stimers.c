void Example_Task( qEvent_t e ){
    static qSTimer_t timeout = QSTIMER_INITIALIZER;
    if( e->FirstCall ){
        /*Arming the stimer for  3.5 seg*/
        qSTimer_Set( &timeout, 3.5 );
    }
    
    /*non-blocking delay, true when timeout expires*/
    if( qSTimer_Expired( &timeout ) ){
        /*
        TODO: Code when STimer expires
        */    
        qSTimer_Disarm( &timeout );
    }
    else return; /*Yield*/
}