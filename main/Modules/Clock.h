#include "Arduino.h"
#include <Wire.h>
#include <RtcDS3231.h>
RtcDS3231<TwoWire> Rtc(Wire);


class Clock{  
    private:
        
        String name;
        void configureRtcHourAndMin( byte hour, byte min = 0 ){
            RtcDateTime modify = RtcDateTime(now.Year(), now.Month(),now.Day(),hour,min,0); 
            Rtc.SetDateTime(modify); 
        }
    public:

        RtcDateTime now; 
        Clock(bool setTime = false, byte hour = 0, byte minute = 0){
            Serial.begin(115200);
            Rtc.Begin(); 
            Serial.println("Clock Inited");
            
            if(setTime){
                configureRtcHourAndMin(hour, minute);  
            }
            getTimeStamp();
            
            
            Serial.print("Hour:");
            Serial.println(now.Hour());
            Serial.print("min:");
            Serial.println(now.Minute());
        }
        void getTimeStamp () {
            now = Rtc.GetDateTime();  //get the time from the RTC 
        };
    
   };
