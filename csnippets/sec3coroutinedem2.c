#include "HAL.h"
#include "QuarkTS.h"
#include "AppLibrary.h"

#define NUM_ITEMS 32
#define BUFSIZE 8

qTask_t ProducerTask, ConsumerTask;
qCR_Semaphore_t mutex, full, empty;
/*===================================================================*/
void ProducerTask_Callback( qEvent_t e ){
  static int produced;
  
  qCR_Begin{
     for(produced = 0; produced < NUM_ITEMS; ++produced) {
        qCR_SemWait( &full );
        qCR_SemWait( &mutex );

        add_to_buffer( produce_item() );  
  
        qCR_SemSignal( &mutex );
        qCR_SemSignal( &empty );
     }
  }qCR_End;
}
/*===================================================================*/
void ConsumerTask_Callback( qEvent_t e ){{
  static int consumed;
  
  qCR_Begin{
      for(consumed = 0; consumed < NUM_ITEMS; ++consumed) {
        qCR_SemWait( &empty );
        qCR_SemWait( &mutex );    

        consume_item( get_from_buffer() );    

        qCR_SemSignal( &mutex ); 
        qCR_SemSignal( &full );
      }
  }qCR_End;
}
/*===================================================================*/
void IdleTask_Callback( qEvent_t e ){
    /*nothing to do*/
} 
/*===================================================================*/
int main(void){ 
  HAL_Init();

  qOS_Setup( HAL_GetTick, 0.001, IdleTask_Callback );
  qCR_SemInit( &empty, 0 );
  qCR_SemInit( &full, BUFSIZE );
  qCR_SemInit( &mutex, 1 );	
  
  qOS_Add_Task( &ProducerTask, ProducerTask_Callback,
                qMedium_Priority, 0.1, qPeriodic, qEnabled, NULL );
  qOS_Add_Task( &ConsumerTask, ConsumerTask_Callback,
                qMedium_Priority, 0.1, qPeriodic, qEnabled, NULL );
  qOS_Run(); 	
  return 0;
}