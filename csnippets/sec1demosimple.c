#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "BSP.h"

#include "QuarkTS.h"
#define TIMER_TICK   ( 0.001f )   /* 1ms */ 

qTask_t task1, task2, task3; /*task nodes*/
/*==================================================================*/
void interrupt Timer0_ISR( void ) {
    qClock_SysTick();   
}
/*==================================================================*/
void Task1_Callback( qEvent_t e ) {
    BSP_UART1_WriteString( "Task1" );

    if ( e->FirstIteration ) {
        qTask_Resume( &Task3 );    
    }
    
    if ( e->LastIteration ) {
        qTask_Suspend( &Task3 );
        qTask_Set_Time( &Task2, 0.5f );
    }
}
/*==================================================================*/
void Task2_Callback( qEvent_t e ) {
    BSP_UART1_WriteString( "Task2" );
}
/*==================================================================*/
void Task3_Callback( qEvent_t e ) {
    BSP_UART1_WriteString( "Task3" );
}
/*==================================================================*/
int main( void ) {    
    HardwareSetup();  /*hardware initialization function*/
    /*function to fire an interrupt at 1ms - timer tick*/
    Configure_Periodic_Timer0_Interrupt_1ms(); 
    
    qOS_Setup( NULL, TIMER_TICK, NULL );     
    qOS_Add_Task( &Task1, Task1_Callback, 50, 2.0f, 10, qEnabled, NULL );
    qOS_Add_Task( &Task2, Task2_Callback, 50, 3.0f, qPeriodic, qEnabled, NULL );
    qOS_Add_Task( &Task2, Task3_Callback, 50, 5.0f, qPeriodic, qDisabled, NULL );
    qOS_Run();
	
    return 0;
}