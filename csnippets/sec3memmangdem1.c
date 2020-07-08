#include <stdio.h>
#include <stdlib.h>
#include "QuarkTS.h"
#include "HAL.h"
#include "Core.h"

qTask_t taskA;
qMemMang_Pool_t another_heap;
void taskA_Callback( qEvent_t e );

void taskA_Callback( qEvent_t e ){
    int *xdata = NULL;
    int *ydata = NULL;
    int *xyoper = NULL;
    int n = 20;
    int i;
    
    xyoper = (int*)qMalloc( n*sizeof(int) );
    xdata = (int*)qMalloc( n*sizeof(int) );
    qMemMang_Pool_Select( &another_heap ); /*change the memory pool*/
    /*ydata will point to a segment allocated in another pool*/
    ydata = (int*)qMalloc( n*sizeof(int) ); 
    
    /*use the memory if could be allocated*/
    if( xdata && ydata && xyoper ){ 
        for(i=0; i<n; i++){
            xdata[i] = GetXData();
            ydata[i] = GetYData();
            xyoper[i] = xdata[i] * ydata[i];
        }
        UseTheMemmory(xyoper);
    }
    else{
        qTrace_Message("ERROR:ALLOCATION_FAIL");
    }

    qFree( ydata );
    qMemMang_Pool_Select( NULL ); /*return to the default pool*/
    qFree( xdata );
    qFree( xyoper );
}

int main(void){
    char area_another_heap[512]={0};
    qTrace_Set_OutputFcn( OutPutChar );
    /*Create a memory heap*/
    qMemMang_Pool_Setup( &another_heap, area_another_heap, 512); 
    qOS_Setup( HAL_GetTick, 0.001, IdleTaskCallback );
    qOS_Add_Task( &taskA, taskA_Callback, qLowest_Priority, 0.1, 
                  qPeriodic, qEnabled, NULL);
    qOS_Run();
    return 0;
}