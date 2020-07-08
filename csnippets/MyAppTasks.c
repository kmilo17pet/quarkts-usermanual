#include "MyAppTasks.h"

qTask_t CommunicationTask, HardwareCheckTask, 
        CheckUserEventsTask, SignalAnalisysTask;

void CommunicationTask_Callback( qEvent_t e ){
    /*
    TODO: Communication Task code
    */
}

void HardwareCheckTask_Callback( qEvent_t e ){
    /*
    TODO: Hardware Check Task code
    */
}

void CheckUserEventsTask_Callback( qEvent_t e ){
    /*
    TODO: Check User Events Task code
    */
}

void SignalAnalisysTask_Callback( qEvent_t e ){
    /*
    TODO: Signal Analisys Task code
    */
}

/*this task doesnt need an Identifier*/
void IdleTask_Callback( qEvent_t e ){ 
    /*
    TODO: Idle Task code
    */
}