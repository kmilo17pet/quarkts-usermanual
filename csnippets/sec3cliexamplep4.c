qATCLI_Response_t AT_GPIO_Callback( qATCLI_Handler_t h ){
	qATCLI_Response_t RetValue = QATCLI_ERROR;
    int pin, value;

	switch( h->Type ){
    	case QATCLI_CMDTYPE_ACT: /*< AT+gpio */
    		RetValue = QATCLI_OK;
    		break;
        case QATCLI_CMDTYPE_TEST: /*< AT+gpio=? */
            h->puts( "+gpio=<pin>,<value>\r\n" );
            h->puts( "+gpio?\r\n" );            
    		RetValue = QATCLI_NORESPONSE;
    		break;    		
    	case QATCLI_CMDTYPE_READ: /*< AT+gpio? */
    	    sprintf( h->Output, "0x%08X", HAL_GPIO_Read( GPIOA ) );
    		RetValue = QATCLI_NORESPONSE;
    		break;
        case QATCLI_CMDTYPE_PARA: /*< AT+gpio=<pin>,<value> */
    	    pin = h->GetArgInt( 1 );
    	    value = h->GetArgInt( 2 );
    	    HAL_GPIO_WRITE( GPIOA, pin, value );
    		RetValue = QATCLI_OK;
    		break;    		
    	default : break;
    }
    
	return RetValue;    
}
/*==================================================================*/
qATCLI_Response_t AT_INFO_Callback( qATCLI_Handler_t h ){
	qATCLI_Response_t RetValue = QATCLI_ERROR;

	switch( param->Type ){
    	case QATCLI_CMDTYPE_ACT: /*< AT+info */
    	  strcpy( h->Output, "Compilation: " __DATE__ " " __TIME__ );
    		RetValue = QATCLI_NORESPONSE;
    		break;
    	default : break;
	}
	
	return RetValue;    
}
/*==================================================================*/