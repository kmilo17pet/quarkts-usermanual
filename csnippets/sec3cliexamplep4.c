qATCLI_Response_t AT_GPIO_Callback( qATCLI_Handler_t h ) {
	qATCLI_Response_t RetValue = qATCLI_ERROR;
    int pin, value;

	switch ( h->Type ) {
    	case qATCLI_CMDTYPE_ACT: /*< AT+gpio */
    		RetValue = qATCLI_OK;
    		break;
        case qATCLI_CMDTYPE_TEST: /*< AT+gpio=? */
            h->puts( "+gpio=<pin>,<value>\r\n" );
            h->puts( "+gpio?\r\n" );            
    		RetValue = qATCLI_NORESPONSE;
    		break;    		
    	case qATCLI_CMDTYPE_READ: /*< AT+gpio? */
    	    sprintf( h->Output, "0x%08X", HAL_GPIO_Read( GPIOA ) );
    		RetValue = qATCLI_NORESPONSE;
    		break;
        case qATCLI_CMDTYPE_PARA: /*< AT+gpio=<pin>,<value> */
    	    pin = h->GetArgInt( 1 );
    	    value = h->GetArgInt( 2 );
    	    HAL_GPIO_WRITE( GPIOA, pin, value );
    		RetValue = qATCLI_OK;
    		break;    		
    	default : break;
    }
    
	return RetValue;    
}
/*==================================================================*/
qATCLI_Response_t AT_INFO_Callback( qATCLI_Handler_t h ) {
	qATCLI_Response_t RetValue = qATCLI_ERROR;

	switch ( param->Type ) {
    	case qATCLI_CMDTYPE_ACT: /*< AT+info */
    	  strcpy( h->Output, "Compilation: " __DATE__ " " __TIME__ );
    		RetValue = qATCLI_NORESPONSE;
    		break;
    	default : break;
	}
	
	return RetValue;    
}
/*==================================================================*/