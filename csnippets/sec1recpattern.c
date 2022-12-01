#include "QuarkTS.h"
#include "Globals.h"
#include "MyAppTasks.h"

void interrupt OnTimerInterrupt( void ) { //hardware specific code
    qClock_SysTick();
}

void main( void ) {
    /*start of hardware specific code*/
    HardwareSetup();
    Configure_Periodic_Timer_Interrupt_10ms(); 
    /*end of hardware specific code*/
    qOS_Setup( NULL, 0.01f, IdleTask_Callback ); 
    qOS_Add_Task( HardwareCheckTask, HardwareCheckTask_Callback,
                  qLowest_Priority, 0.25, qPeriodic, qEnabled, NULL );
    qOS_Add_Task( SignalAnalisysTask, SignalAnalisysTask_Callback, 
                  qHigh_Priority, 0.1, 200, qEnabled, NULL );
    qOS_Add_EventTask( CheckEventsTask, CheckEventsTask_Callback, 
                       qMedium_Priority, NULL ); 
    qOS_Add_Task( CommunicationTask, CommunicationTask_Callback, 
                  qHigh_Priority, qTimeImmediate, qPeriodic, 
                  qEnabled, NULL );
    qOS_Run();
    for(;;){}
}