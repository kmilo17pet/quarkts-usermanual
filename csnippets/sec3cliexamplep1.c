#define CLI_MAX_INPUT_BUFF_SIZE         (128)
#define CLI_MAX_OUTPUT_BUFF_SIZE        (128)

qTask_t CLI_Task;
qATCLI_t CLI_Object;
qATCLI_Command_t AT_GPIO, AT_INFO;

char CLI_Input[AT_CLI_MAX_INPUT_BUFF_SIZE];
char CLI_Output[AT_CLI_MAX_OUTPUT_BUFF_SIZE];

/*Command callbacks*/
qATCLI_Response_t AT_GPIO_Callback( qATCLI_Handler_t h );
qATCLI_Response_t AT_INFO_Callback( qATCLI_Handler_t h );
