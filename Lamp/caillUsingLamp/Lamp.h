#include "Arduino.h"
class Lamp{  
    private:
        String name;
        int id;
        int pinOut;
        int turnOnMinute;
        int turnOffMinute;
        bool turnOffTomorrow = false;
        byte lightHours;

        int onValue;   //Value on minutes that the lamp turn On
        int offValue; 
        const minutesInADay = 1439; /*23*60+59 TEST THIS*/
        int convertTimeToMinutes (byte hour, byte min = 0){
            {
            if (hour){
                return hour*60 + min;
            }   
            return 0;
            }
        }
        void minutesToSwitch( byte onHourParameter, byte onMinParameter, byte lightHoursParameter ){
            turnOnMinute = convertTimeToMinutes( onHourParameter, onMinParameter );
            turnOffMinute = convertTimeToMinutes(lightHoursParameter) + turnOnMinute;
            if (turnOffMinute >= minutesInADay){
                turnOffMinute = turnOffMinute - minutesInADay;
                turnOffTomorrow = true;
                return;
            }
            turnOffTomorrow = false;
        }
          
      public:
        Lamps(byte pin){
            pinOut = pin;
            Serial.begin(115200);
            Serial.println("lamp");
            //setLampTime();
        }                  // Constructor
        
        void setLampPin(byte pin){
            pinOut = pin; 
        }
        
        void SetLampTime( int onHourParameter, int onMinParameter, int lightHoursParameter ){
            lightHours = lightHoursParameter;
            minutesToSwitch( onHourParameter, onMinParameter, lightHoursParameter);
        }

        // int getLampTime(){ //toDo
        //     int hourAndMinutes[] = {0, 0};
        //     return hourAndMinutes;
        // };
        bool getLampState(byte nowHour, byte nowMinute){
            int nowTimeInMin = convertTimeToMinutes( nowHour, nowMinute);
            Serial.println("kliaa");
            Serial.println(nowTimeInMin);
            if (turnOffTomorrow){ //the way in that the lamp identify if it needs to turn on and off in differents day
                if(nowTimeInMin >= turnOnMinute || nowTimeInMin <= turnOffMinute ){
                    digitalWrite( pinOut, HIGH);
                    return 1;
                }
                digitalWrite( pinOut, LOW);
                return 0;   
                
            }
            if((nowTimeInMin >= turnOnMinute) && (nowTimeInMin < turnOffMinute)){
                digitalWrite(pinOut, HIGH);
                return 1;
            }
            digitalWrite(pinOut, LOW);
            return 0;  
        }
   };
    