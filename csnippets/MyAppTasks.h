#ifndef MYAPPTASK_H
    #define MYAPPTASK_H
    
    #include "Globals.h"
    #include "QuarkTS.h"
    
    extern qTask_t CommunicationTask, HardwareCheckTask,
                  CheckUserEventsTask, SignalAnalisysTask;
    
    void CommunicationTask_Callback( qEvent_t );
    void HardwareCheckTask_Callback( qEvent_t );
    void CheckUserEventsTask_Callback( qEvent_t );
    void SignalAnalisysTask_Callback( qEvent_t );
#endif