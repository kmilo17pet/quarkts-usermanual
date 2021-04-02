#include "QuarkTS.h"
#include "HAL.h"

#define TIMER_TICK   0.001   /* 1ms */ 

void main( void ){
    HAL_Init(); 
    qOS_Setup( HAL_GetTick, TIMER_TICK, IdleTask_Callback );
    /* 
    TODO: add Tasks to the scheduler scheme and run the OS 
    */
}