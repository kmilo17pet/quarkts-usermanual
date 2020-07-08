qOS_Add_Task( &TEMPERATURE_CONTROL_TASK, PIDControl_Callback,
              qHigh_Priority, TemperatureControl.dt , 
              qPeriodic, qEnabled, &TemperatureControl );
qOS_Add_Task( &HUMIDITY_CONTROL_TASK, PIDControl_Callback, 
              qHigh_Priority, HumidityControl.dt, 
              qPeriodic, qEnabled, &HumidityControl );
qOS_Add_Task( &LIGHT_CONTROL_TASK, PIDControl_Callback, 
              qHigh_Priority, LightControl.dt, 
              qPeriodic, qEnabled, &LightControl );