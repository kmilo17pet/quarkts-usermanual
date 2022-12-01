#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "QuarkTS.h"
#define TIMER_TICK   ( 0.001f )   /* 1ms */ 

/*event flags application definitions */
#define SWITCH_CHANGED  QEVENTFLAG_01
#define TIMER_EXPIRED   QEVENTFLAG_02
#define DATA_READY      QEVENTFLAG_03
#define DATA_TXMIT      QEVENTFLAG_04

qTask_t TaskDataProducer; 
qUINT8_t dataToTransmit[ 10 ] = { 0u };

/*-----------------------------------------------------------------------*/
void interrupt Timer0_ISR( void ){
    qClock_SysTick();   
}
/*-----------------------------------------------------------------------*/
void interrupt Timer1_ISR( void ) {
    qTask_EventFlags_Modify( &TaskDataProducer, TIMER_EXPIRED, 
                             QEVENTFLAG_SET );
}
/*-----------------------------------------------------------------------*/
void interrupt EXTI_ISR( void ) {
    if ( EXTI_IsRisingEdge() ) {
        qTask_EventFlags_Modify( &TaskDataProducer, SWITCH_CHANGED, 
                                 QEVENTFLAG_SET );
    }
}
/*-----------------------------------------------------------------------*/
void TaskDataProducer_Callback( qEvent_t e ) 
    qBool_t condition;
    condition = qTask_EventFlags_Check( &TaskDataProducer, 
                                        DATA_TXMIT, qTrue, qTrue );
    if ( qTrue == condition) {
        GenerateData( dataToTransmit );
        qTask_EventFlags_Modify( &TaskDataProducer, DATA_READY, 
                                 QEVENTFLAG_SET ); 
    }
    qTask_EventFlags_Check( &TaskDataProducer, 
                            DATA_READY | SWITCH_CHANGED | TIMER_EXPIRED,
                            qTrue, qTrue );
}
/*-----------------------------------------------------------------------*/
void IdleTask_Callback( qEvent_t e ) {
    
    TransmitData( dataToTransmit );
    qTask_EventFlags_Modify( &TaskDataProducer, 
                             DATA_TXMIT, QEVENTFLAG_SET ); 
}
/*-----------------------------------------------------------------------*/
int main( void ) {    
    HardwareSetup();  //hardware specific code
    /* next line is used to setup hardware with specific code to fire
     * interrupts at 1ms - timer tick*/
    Configure_Periodic_Timer0_Interrupt_1ms();
    Configure_Periodic_Timer1_Interrupt_2s();
    Configure_External_Interrupt();
    /*
    Idle task will be responsible to transmit the generate the data after 
    all conditions are meet
    */
    qOS_Setup( NULL, TIMER_TICK, IdleTask_Callback );
    /*
    The task will wait until data is transmitted to generate another set of
    data
    */
    qOS_Add_EventTask( &TaskDataProducer, TaskDataProducer_Callback,
                       qHigh_Priority, "DATAPRODUCER" );
    /*
    Set the flag DATA_TXMIT as initial condition to allow the data 
    generation at startup
    */
    qTask_EventFlags_Modify( &TaskDataProducer, DATA_TXMIT, QEVENTFLAG_SET ); 
    qOS_Run();
    for(;;){}
    return 0;
}