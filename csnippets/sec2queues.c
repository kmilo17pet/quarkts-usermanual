#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "QuarkTS.h"
#define TIMER_TICK   ( 0.001f )   /* 1ms */ 

/*-----------------------------------------------------------------------*/
void interrupt Timer0_ISR( void ) {
    qClock_SysTick();   
}
/*-----------------------------------------------------------------------*/
qTask_t TSK_PRODUCER, TSK_CONSUMER; /*task nodes*/
qQueue_t UserQueue; /*Queue Handle*/
/*-----------------------------------------------------------------------*/

/* The producer task puts data into the buffer if there is enough free 
 * space in it, otherwise the task block itself and wait until the queue 
 * is empty to resume. */
void TSK_Producer_Callback( qEvent_t e ) {
    static qUINT16_t unData = 0;
    unData++;	
    /*Queue is empty, enable the producer if it was disabled*/
    if ( byQueueEmpty == e->Trigger ) {
        qTask_Resume( qTask_Self() );
    }

    /*send data to the queue*/
    if ( qFalse == qQueue_SendToBack( &UserQueue, &unData ) ) { 
        /*
        * if the data insertion fails, the queue is full 
        * and the task disables itself
        */
	    qTask_Suspend( qTask_Self() ); 
    }
}
/*-----------------------------------------------------------------------*/
/* The consumer task gets one element from the queue.*/
void TSK_Consumer_Callback( qEvent_t e ) {
    qUINT16_t unData;
    qQueue_t *ptrQueue; /*a pointer to the queue that triggers the event*/
    if ( byQueueCount == e->Trigger ) {
	    ptrQueue = (qQueue_t *)e->EventData;
	    qQueue_Receive( ptrQueue, &unData );
	    return;
    }
}
/*-----------------------------------------------------------------------*/
void IdleTask_Callback( qEvent_t e ) {
    /*nothing to do...*/
}	
/*-----------------------------------------------------------------------*/
int main( void ) {    
    qUINT8_t BufferMem[ 16*sizeof(qUINT16_t) ] = { 0u };  
    HardwareSetup();  //hardware specific code
    /* next line is used to setup hardware with specific code to fire
     * interrupts at 1ms - timer tick*/
    Configure_Periodic_Timer0_Interrupt_1ms();
 
    qOS_Setup( NULL, TIMER_TICK, IdleTask_Callback );     
    /*Setup the queue*/
    qQueue_Setup( &UserQueue, BufferMem /*Memory block used*/, 
                  sizeof(qUINT16_t) /*element size*/, 
                  16 /* element count*/ );     
                 
    /*  Append the producer task with 100mS rate. */
    qOS_Add_Task( &TSK_PRODUCER, TSK_Producer_Callback, 
                  qMedium_Priority, 0.1f, qPeriodic, qEnabled, 
                  "producer" );
    /* Append the consumer as an event task. The consumer will
     * wait until an event trigger their execution
     */
    qOS_Add_EventTask( &TSK_CONSUMER, TSK_Consumer_Callback,
                       qMedium_Priority, "consumer" );
    /* the queue will be attached to the consumer task 
     * in qQueueMode_Count mode. This mode sends an event to the consumer
     * task when the queue fills to a level of 4 elements
     */
    qTask_Attach_Queue( &TSK_CONSUMER, &UserQueue, qQueueMode_Count, 4 );
    /* the queue will be attached to the producer task in
     * qQueueMode_Empty mode. This mode sends an event to the producer
     * task when the queue is empty
     */
     
    qTask_Attach_Queue( &TSK_PRODUCER, &UserQueue, qQueueMode_Empty, qATTACH );
    qOS_Run();
    return 0;
}