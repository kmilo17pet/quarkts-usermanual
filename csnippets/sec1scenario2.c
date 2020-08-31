#include "QuarkTS.h"
#include "DeviceHeader.h"

#define TIMER_TICK   0.001   /* 1ms */ 

void Interrupt_Timer0( void ){
    qClock_SysTick();
}

void main( void ){
    MCU_Init();
    BSP_Setup_Timer0(); 
    qOS_Setup( NULL, TIMER_TICK, IdleTask_Callback ); 
    
    /*
    TODO: add Tasks to the scheduler scheme and run the OS
    */
}