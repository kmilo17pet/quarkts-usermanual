void Sender_Task( qEvent_t e ) {
    static qSTimer_t timeout;
    qCR_Begin {                  
        Send_Packet();
        /* 
           Wait until an acknowledgment has been received, or until
           the timer expires. If the timer expires, we should send
           the packet again. 
        */
        qSTimer_Set( &timeout, TIMEOUT_TIME );
        qCR_WaitUntil( PacketACK_Received() || 
                       qSTimer_Expired(&timeout));
    } qCR_End;
}
/*===================================================================*/
void Receiver_Task( qEvent_t e ) {
    qCR_Begin {                  
        /* Wait until a packet has been received*/
        qCR_WaitUntil( Packet_Received() );
        Send_Acknowledgement();  
    } qCR_End;
}