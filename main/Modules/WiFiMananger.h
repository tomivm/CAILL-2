#include "Arduino.h"

#ifdef ESP32
  #include <WiFi.h>
#elif defined(ESP8266)
    #include <WiFiClientSecure.h>
    #include <UniversalTelegramBot.h>   // Universal Telegram Bot Library written by Brian Lough: https://github.com/witnessmenow/Universal-Arduino-Telegram-Bot
    #include <ArduinoJson.h>
#endif

class WiFiMananger{  
    private:
        
        String name;
        void begin(){
        }
    public:

        Wifi(bool setTime = false, byte hour = 0, byte minute = 0){
            Serial.println("begin");
        }
        void test () {
            Serial.println("test");
        };
    
   };
