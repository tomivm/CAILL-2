#include "Lamp.h"
#include "AirConditioner.h"
#include "Clock.h"

#define LAMP_PIN 0
#define AIR_CONDITIONER_PIN 13

bool setTime = false; ///if true, the time of clock is seted with the next int vars
int hour = 1;
int minute = 49;

int temperature = 28;

int horaEncendido = 0, minEncendido = 30, horasDeLuz = 12 ;
byte wantedTemperatureDay = 26, maxTemperatureDay = 30; 
byte wantedTemperatureNight = 26, maxTemperatureNight = 35; 


Clock RealTimeClock(setTime, hour, minute);
Lamp Lamp1(LAMP_PIN);
AirConditioner AirConditioner1(5);

int convertTimeToMinutes (byte hour, byte min = 0){
    const byte HOUR_IN_MINUTES = 60;
    if (hour){
        return hour * HOUR_IN_MINUTES + min;
    }   
    return min;
}

void refreshTime(){
  RealTimeClock.getTimeStamp();
  hour = RealTimeClock.now.Hour();
  minute = RealTimeClock.now.Minute();
  Serial.println("Time Stamp");
  Serial.print(hour);
  Serial.println(":");
  Serial.println(minute);  
}

void setup() {
    refreshTime();
    
    Lamp1.setLampTime( horaEncendido, minEncendido, horasDeLuz );

    AirConditioner1.setAirConditionerDayTemperatures( wantedTemperatureDay, maxTemperatureDay);
    AirConditioner1.setAirConditionerNightTemperatures( wantedTemperatureNight, maxTemperatureNight);
}

void loop() {  
  refreshTime();
  bool lamp = Lamp1.updateLampState(hour, minute);
  bool AC = AirConditioner1.updateAcState(temperature, Lamp1.getLampState(), convertTimeToMinutes(hour, minute), Lamp1.getTurnOnMinute());
  delay(10000);
}
