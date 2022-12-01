void IO_TASK_Callback( qEvent_t e ) {
    TemperatureControl.yt = SampleTemperatureSensor();
    HumidityControl.yt = SampleHumiditySensor();
    LightControl.yt = SampleLightSensor();
    WriteTemperatureActuatorValue( TemperatureControl.ut );
    WriteHumidityActuatorValue( HumidityControl.ut );
    WriteLightActuatorValue( LightControl.ut );
}