void PIDControl_Callback( qEvent_t e ){
    float Error, derivative;
    /* 
    Obtain the reference to the specific PID controller 
    using the TaskData field from the qEvent structure
    */
    PID_Params_t *Controller = (PID_Params_t *)e->TaskData; 
    /*Compute the error*/
    Error = Controller->sp - Controller->yt;
    /*Compute the accumulated error using backward integral approximation*/
    Controller->ie += Error*Controller->dt;
    /*update and compute the derivative term*/
    derivative = (Error - Controller->pe)/Controller->dt;
    /*update the previous error*/
    Controller->pe = Error;
    /*compute the pid control law*/
    Controller->ut = Controller->Kc*Error  +  
                     Controller->Ki*Controller->ie + 
                     Controller->Kd*derivative;
}