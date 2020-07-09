qATCLI_Response_t CMD_Callback( qATCLI_Handler_t h, qATCLI_PreCmd_t p ){
	qATCLI_Response_t Response = QATCLI_NORESPONSE;
	/*check the command-type*/
	switch(param->Type){
		case QATCLI_CMDTYPE_PARA:
			Response = QATCLI_OK;
			break;
		case QATCLI_CMDTYPE_TEST:
			Response = QATCLI_OK;
			break;
		case QATCLI_CMDTYPE_READ:
			strcpy( h->Output , "Test");
			Response = QATCLI_OK;
			break;
		case QATCLI_CMDTYPE_ACT:
			Response = QATCLI_OK;
			break;			
		default:
			Response = QATCLI_ERROR;
			break;
	}
	return Response;
}