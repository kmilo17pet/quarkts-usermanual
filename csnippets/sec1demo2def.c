   typedef struct{
        float yt; /*Measured variable (Controller Input)*/
        float ut; /*Controlled variable (Controller Output)*/
        float ie; /*Accumulated error*/
        float pe; /*Previous error*/
        float dt; /*Controller Time Step*/
        float sp; /*Set-Point*/
        float Kc, Ki, Kd; /*PID Gains*/ 
    }PID_Params_t;
    
    PID_Params_t TemperatureControl = {
       0.0f, 0.0f, 0.0f, 0.0f, /*Initial IO state of yt and ut*/
       1.5f, /*time step*/
       28.5f, /*Set-Point*/
       0.89f, 0.122f, 0.001f /*Kc, Ki, Kd*/
    };
    PID_Params_t HumidityControl= {
       0.0f, 0.0f, 0.0f, 0.0f, /*Initial IO state of yt and ut*/
       1.0f, /*time step*/
       60.0f, /*Set-Point*/
       2.5f, 0.2354f, 0.0015f /*Kc, Ki, Kd*/
    };
    PID_Params_t LightControl= {
       0.0f, 0.0f, 0.0f, 0.0f, /*Initial IO state of yt and ut*/
       0.5f, /*time step*/
       45.0f, /*Set-Point*/
       5.36f, 0.0891f, 0.0f /*Kc, Ki, Kd*/
    };