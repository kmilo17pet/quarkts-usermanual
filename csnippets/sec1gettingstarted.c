#include "QuarkTS.h"
#define TIMER_TICK   0.001   /* 1ms */ 

void main( void ){
    /*start of hardware specific code*/
    HardwareSetup();  
    Configure_Periodic_Timer_Interrupt_1ms(); 
    /*end of hardware specific code*/
    qOS_Setup( NULL, TIMER_TICK, IdleTask_Callback ); 
    /*
    TODO: add Tasks to the scheduler scheme and run the OS
    */
}