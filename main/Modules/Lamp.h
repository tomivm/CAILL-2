#include "Arduino.h"
class Lamp{  
    private:
        String name;
        int id;
        int pinOut;
        bool onLevel;
        int turnOnMinute;
        int turnOffMinute;
        bool turnOffTomorrow = false;
        byte lightHours;
        bool isOn;

        int onValue;   //Value on minutes that the lamp turn On
        int offValue; 

        int manageLamp(int nowTimeInMin){
            if (turnOffTomorrow){ //the way in that the lamp identify if it needs to turn on and off in differents day
                if(nowTimeInMin >= turnOnMinute || nowTimeInMin <= turnOffMinute ){
                    return turnOn();
                }
                return turnOff();  
                
            }
            if((nowTimeInMin >= turnOnMinute) && (nowTimeInMin < turnOffMinute)){
                return turnOn();
            }
            return turnOff();
        }

        bool turnOn(){
            digitalWrite(pinOut, onLevel);
            isOn = 1;
            return isOn;
        }

        bool turnOff(){
            digitalWrite(pinOut, !onLevel);
            isOn = 0;
            return isOn;
        }
        
        int convertTimeToMinutes (byte hour, byte min = 0){
            const byte HOUR_IN_MINUTES = 60;
            if (hour){
                return hour * HOUR_IN_MINUTES + min;
            }   
            return min;
        }
        
        // int convertMinutesToTime (int minutes){
        //     int hour = minutes / HOUR_IN_MINUTES;
        //     int minute = minutes % HOUR_IN_MINUTES;
        //     return int [ hour, minute ]
        // }

        void minutesToSwitch( byte onHourParameter, byte onMinParameter, byte lightHoursParameter ){
            const int MINUTES_IN_A_DAY = 1439; /*23*60+59 TEST THIS*/

            turnOnMinute = convertTimeToMinutes( onHourParameter, onMinParameter );
            turnOffMinute = convertTimeToMinutes(lightHoursParameter) + turnOnMinute;
            if (turnOffMinute >= MINUTES_IN_A_DAY){
                turnOffMinute = turnOffMinute - MINUTES_IN_A_DAY;
                turnOffTomorrow = true;
                return;
            }
            turnOffTomorrow = false;
        }
          
      public:
        Lamp(byte pin, bool ON_LEVEL){
            pinOut = pin;
            pinMode(pinOut, OUTPUT);
            onLevel = ON_LEVEL;
            Serial.begin(115200);
            Serial.println("lamp");
            //setLampTime();
        }                  // Constructor
        
        void setLampPin(byte pin){
            pinOut = pin; 
        }
        
        void setLampTime( int onHourParameter, int onMinParameter, int lightHoursParameter ){
            lightHours = lightHoursParameter;
            minutesToSwitch( onHourParameter, onMinParameter, lightHoursParameter);
        }

        // int getOnLampTime(){ // consider utility!!!!
        //     return convertMinutesToTime(turnOnMinute)
        // };

        int getTurnOnMinute(){
            return turnOnMinute;
        }

        int getTurnOffMinute(){
            return turnOffMinute;
        }
        
        bool getLampState(){
            return isOn;
        }

        bool updateLampState(byte nowHour, byte nowMinute){
            return manageLamp(convertTimeToMinutes( nowHour, nowMinute));
        }
   };
