void interrupt HAL_UART_RxInterrupt( void ){
    char received;
    
    received = HAL_HUART_GetChar( UART1 );
    qATCLI_ISRHandler( &CLI_Object, received ); /*Feed the CLI input*/
}


