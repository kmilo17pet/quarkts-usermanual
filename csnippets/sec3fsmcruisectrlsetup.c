#include <stdlib.h>
#include <stdio.h>
#include "QuarkTS.h"
#include "HAL.h"
#include "CruiseControl_FSM.h"

#define     MAX_SM_SIGNALS     ( 10 )
qQueue_t SigQueue;
qSM_Signal_t topsm_sig_stack[ MAX_FSM_SIGNALS ];

int main( void ){
    qOS_Setup( HAL_GetTick, 0.001f, NULL ); 
    /*Setup the automated control FSM*/
    qStateMachine_Setup( &AC_SM, AC_Accelerating_State, NULL );
    qStateMachine_TransitionTableInstall( &AC_SM, &AC_ttable, 
                                          AutomatedControl_SM_ttable, 6 );
    /*Setup a FSM task for the Top FSM*/    
    qOS_Add_StateMachineTask(  &SMTask, qMedium_Priority, 0.1f, &Top_SM, 
                               Top_Idle_State, NULL, qEnabled, NULL); 
                               
    /*Setup the signal-queue for the Top FSM*/
    qStateMachine_SignalQueueSetup( &Top_SM, &SigQueue, 
                                    topsm_sig_stack, MAX_SM_SIGNALS );
    
    qStateMachine_TransitionTableInstall( &Top_SM, &Top_ttable, 
                                          Top_SM_ttable, 6 );
    /*Set the Automated Control state as composite using the AC_SM */
    qStateMachine_Set_CompositeState( &Top_SM, Top_AutomatedControl_State, 
                                      &AC_SM );
    /*Improve the FSM signal handling for the owner task*/
    qOS_StateMachineTask_SigCon( &SMTask );

    qOS_Run();
    return EXIT_SUCCESS;
}