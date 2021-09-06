#include "Lamp.h"
#include "AirConditioner.h"

#define LAMP_PIN 4
#define AIR_CONDITIONER_PIN 5

int hour = 23;
int minute = 49;

int temperature = 28;

int horaEncendido = 0, minEncendido = 30, horasDeLuz = 12 ;
byte wantedTemperatureDay = 26, maxTemperatureDay = 30; 
byte wantedTemperatureNight = 26, maxTemperatureNight = 35; 

Lamp Lamp1(4);
AirConditioner AirConditioner1(5);

int convertTimeToMinutes (byte hour, byte min = 0){
    const byte HOUR_IN_MINUTES = 60;
    if (hour){
        return hour * HOUR_IN_MINUTES + min;
    }   
    return min;
}

void setup() {
    Lamp1.setLampTime( horaEncendido, minEncendido, horasDeLuz );

    AirConditioner1.setAirConditionerDayTemperatures( wantedTemperatureDay, maxTemperatureDay);
    AirConditioner1.setAirConditionerNightTemperatures( wantedTemperatureNight, maxTemperatureNight);
}

void loop() {  
  bool lamp = Lamp1.updateLampState(hour, minute);
  bool AC = AirConditioner1.updateAcState(temperature, Lamp1.getLampState(), convertTimeToMinutes(hour, minute), Lamp1.getTurnOnMinute());
  delay(500);
  Serial.println("lammp: ");
  Serial.println(lamp);
  Serial.println("ACond: ");
  Serial.println(AC);
}
