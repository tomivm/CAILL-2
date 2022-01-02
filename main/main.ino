#include "./Modules/Lamp.h"
#include "./Modules/AirConditioner.h"
#include "./Modules/Clock.h"

/* This pin layout is for our nodemcu pcb desing
pay atention that is different for CAILL_nano*/

#define LAMP_PIN 0 //#define Lampara 4 in CAILL_nano
#define AIR_CONDITIONER_PIN 13

bool setTime = false; ///if true, the time of clock is seted with the next int vars
int hour = 1;
int minute = 49;

int temperature = 28;

int horaEncendido = 23, minEncendido = 0, horasDeLuz = 8 ;
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
  Serial.println("Time");
  Serial.print(hour);
  Serial.print(" : ");
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
