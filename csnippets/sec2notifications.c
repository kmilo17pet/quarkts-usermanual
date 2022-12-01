#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "HAL.h" /*hardware dependent code*/
#include "QuarkTS.h"

qTask_t taskA, taskB;
void taskA_Callback( qEvent_t e );
void taskB_Callback( qEvent_t e );

const char *app_events[] = {
                            "Timer1seg", 
                            "ButtonRisingEdge", 
                            "ButtonFallingEdge", 
                            "3Count_ButtonPush"
                            };

/*==================================================================*/
void interrupt Timer1Second_ISR( void ) {
    qTask_Notification_Send( &taskA, NULL );
    HAL_ClearInterruptFlags( HAL_TMR_ISR ); /*hardware dependent code*/
}
/*==================================================================*/
void interrupt ExternalInput_ISR( void ) {
    if ( RISING_EDGE == HAL_GetInputEdge() ) { /*hardware dependent code*/
        qTask_Notification_Queue( &taskA, app_events[ 1 ] );    
    }
    else {
        qTask_Notification_Queue( &taskA, app_events[ 2 ] );
    }
    HAL_ClearInterruptFlags( HAL_EXT_ISR ); /*hardware dependent code*/
}
/*==================================================================*/
void taskA_Callback( qEvent_t e ) {
    static int press_counter = 0;
    
    switch ( e->Trigger ) { /*check the source of the event*/
        case byNotificationSimple: 
            /*
            * Do something here to process the timer event
            */
            break;
        case byNotificationQueued:
            /*here, we only care the Falling Edge events*/
            if( 0 == strcmp( e->EventData, "ButtonFallingEdge" ) ){
                press_counter++; /*count the button press*/
                if( 3 == press_counter ){ /*after 3 presses*/
                    /*send the notification of 3 presses to taskB*/
                    qTask_Notification_Send( &taskB, app_events[ 3 ] );
                    press_counter = 0;
                }
            }
            break;
        default:
            break;
    }
}
/*==================================================================*/
void taskB_Callback( qEvent_t e ) {
    if ( byNotificationSimple == e->Trigger) {
        /*
         * we can do more here, but this is just an example,
         * so, this task will only print out the received 
         * notification event.
         */
        qDebug( e->EventData, Message );
    }
}
/*==================================================================*/
int main( void ) {
    HAL_Setup_MCU(); /*hardware dependent code*/
    qTrace_Set_OutputFcn( HAL_OutPutChar );
    /* setup the scheduler to handle up to 10 queued notifications*/
    qOS_Setup( HAL_GetTick, 0.001, NULL ); 
    qOS_Add_EventTask( &taskA, taskA_Callback, qLowest_Priority, NULL );
    qOS_Add_EventTask( &taskB, taskB_Callback, qLowest_Priority, NULL );                     
    qOS_Run();
    return 0;
}