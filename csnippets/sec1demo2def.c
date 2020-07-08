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
       0,0,0,0, /*Initial IO state of yt and ut*/
       1.5, /*time step*/
       28.5, /*Set-Point*/
       0.89, 0.122, 0.001 /*Kc, Ki, Kd*/
    };
    PID_Params_t HumidityControl= {
       0,0,0,0, /*Initial IO state of yt and ut*/
       1, /*time step*/
       60.0, /*Set-Point*/
       2.5, 0.2354, 0.0015 /*Kc, Ki, Kd*/
    };
    PID_Params_t LightControl= {
       0,0,0,0, /*Initial IO state of yt and ut*/
       0.5, /*time step*/
       45.0, /*Set-Point*/
       5.36, 0.0891, 0.0 /*Kc, Ki, Kd*/
    };