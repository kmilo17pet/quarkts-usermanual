void CLI_OutputChar_Wrapper( void *sp, const char c ){ /*CLI output function*/
    (void)sp; /*unused*/
    HAL_UART_WriteChar( UART1, c );
}
/*==================================================================*/
int main( void ) {    
    HAL_Setup();
    qOS_Setup( HAL_GetTick, TIMER_TICK, NULL );   
    qATCLI_Setup( &CLI_Object, BSP_UART_PUTC, CLI_Input, sizeof(CLI_Input), 
                  CLI_Output, sizeof(CLI_Output),
			          "Example", NULL, NULL, NULL, NULL);
    
    qATCLI_CmdSubscribe( &CLI_Object, &AT_GPIO, "at+gpio", AT_GPIO_Callback, 
                         QATCLI_CMDTYPE_ACT | QATCLI_CMDTYPE_READ | 
                         QATCLI_CMDTYPE_TEST | QATCLI_CMDTYPE_PARA | 0x22, NULL );
    qATCLI_CmdSubscribe( &CLI_Object, &AT_GPIO, "at+gpio", AT_GPIO_Callback, 
                         QATCLI_CMDTYPE_ACT, NULL );
    qOS_Add_ATCLITask( &CLI_Task, &CLI_Object, qLowest_Priority );
    qOS_Run();
	
    return 0;
}