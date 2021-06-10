qATCLI_Response_t CMD_Callback( qATCLI_Handler_t h ){
	qATCLI_Response_t Response = qATCLI_NORESPONSE;
	int arg1 = 0;
	float arg2 = 0;
	/*check the command-type*/
	switch( h->Type ){
		case qATCLI_CMDTYPE_PARA:
		    if( h->NumArgs > 0 ){
			    arg1 = h->GetArgInt( 1 ); /*get the first argument as integer*/
			    if( h->NumArgs > 1){
			        arg2 = h->GetArgFlt( 2 ); /*get the second argument as float*/
			    }
		    }
		  sprintf( h->Output, "arg1 = %d arg2 = %f", arg1, arg2);
			Response = qATCLI_NORESPONSE;
			break;
		case qATCLI_CMDTYPE_TEST:
		  h->puts( "inmediate message" );
			Response = qATCLI_OK;
			break;
		case qATCLI_CMDTYPE_READ:
			strcpy( h->Output , "Test message after the callback");
			Response = qATCLI_OK;
			break;
		case qATCLI_CMDTYPE_ACT:
			Response = qATCLI_OK;
			break;			
		default:
			Response = qATCLI_ERROR;
			break;
	}
	return Response;
}