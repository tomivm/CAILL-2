#include "Arduino.h"
class Lamps{  
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
            if (turnOffMinute >= 1439/*23*60+59*/){
                turnOffMinute = turnOffMinute - 1439;
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
        }     // Declaracion de funcion externa

        // int getLampTime(){ //toDo
        //     int hourAndMinutes[] = {0, 0};
        //     return hourAndMinutes;
        // };
        bool getLampState(byte nowHour, byte nowMinute){
            int nowTimeInMin = convertTimeToMinutes( nowHour, nowMinute);
            Serial.println("kliaa");
            Serial.println(nowTimeInMin);
            if (turnOffTomorrow){ //manera en que la lampara identifica su estado, si su momento de apagar esta al otro dia del momento de prender
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
        }           // Declaracion de funcion externa
   }; 