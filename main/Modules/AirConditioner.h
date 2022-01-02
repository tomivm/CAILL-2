#include "Arduino.h"
class AirConditioner{  
    private:
        String name;
        int id;
        int pinOut;
        byte maxTemperatureOnDay;
        byte wantedTemperatureOnDay;
        byte maxTemperatureOnNight;
        byte wantedTemperatureOnNight;
        bool isOn;
        
        //offset to prevent big increase of temprerature when lamps turn on
        int offsetToDay = 60;

        bool manageAcDay(int indoorTemperature){
            return manageAc(indoorTemperature, maxTemperatureOnDay, wantedTemperatureOnDay);
        }

        bool manageAcNight(byte indoorTemperature){
            return manageAc(indoorTemperature, maxTemperatureOnNight, wantedTemperatureOnNight);
        }

        bool manageAcPrepareForDay(byte indoorTemperature){
            if (indoorTemperature > wantedTemperatureOnDay ){
                return turnOn();      
            }
            return turnOff();
        }

        bool manageAc(byte indoorTemperature, byte maxTemperature, byte wantedTemperature){
            if (indoorTemperature >= maxTemperature ){
                return turnOn();  
                
            }
            if(indoorTemperature <= wantedTemperature){
                return turnOff();
            }
            return isOn;
        }

        bool turnOn(){
            digitalWrite(pinOut, HIGH);
            isOn = 1;
            return isOn;
        }

        bool turnOff(){
            digitalWrite(pinOut, LOW);
            isOn = 0;
            return isOn;
        }
          
        bool isTimeToPrepare(int nowMinutes, int onMinutes){
            const int MINUTES_IN_A_DAY = 1439;
            int prepareToDay = onMinutes - offsetToDay;
            if(prepareToDay < 0){
                if(nowMinutes < onMinutes){
                  return 1;
                }
                prepareToDay = MINUTES_IN_A_DAY + prepareToDay;
            }
            if (nowMinutes >= prepareToDay){
                return 1;
            }
            return 0;
        }

      public:
        AirConditioner(byte pin){
            pinOut = pin;
            Serial.begin(115200);
            Serial.println("AirConditioner");
        }                  // Constructor
        
        void setAirConditionerPin(byte pin){
            pinOut = pin; 
        }
        
        void setAirConditionerDayTemperatures( byte wantedTemperature, byte maxTemperature){
            wantedTemperatureOnDay = wantedTemperature;
            maxTemperatureOnDay = maxTemperature;
        }

        void setPrepareToDay(int timeToPrepareDay){
            offsetToDay = timeToPrepareDay;
        }

        void setAirConditionerNightTemperatures( byte wantedTemperature, byte maxTemperature ){
            wantedTemperatureOnNight = wantedTemperature;
            maxTemperatureOnNight = maxTemperature;
        }

        bool updateAcState(byte indoorTemperature, byte lampState, int nowMinutes, int onMinutes){
            if(lampState){
                return manageAcDay(indoorTemperature);
            }
            if (isTimeToPrepare( nowMinutes, onMinutes )){
                return manageAcPrepareForDay(indoorTemperature);
            }
            return manageAcNight(indoorTemperature);
        }
   };
