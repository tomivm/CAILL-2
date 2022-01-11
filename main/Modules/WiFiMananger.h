#include "Arduino.h"
#include <WiFiClientSecure.h>

#ifdef ESP32
  #include <WiFi.h>
#elif defined(ESP8266)
    #include <ESP8266WiFi.h>
    #include <WiFiClientSecure.h>
    #include <UniversalTelegramBot.h>   // Universal Telegram Bot Library written by Brian Lough: https://github.com/witnessmenow/Universal-Arduino-Telegram-Bot
    #include <ArduinoJson.h>
#endif


class WiFiMananger{  

    private:
        String name;
            // Replace with your network credentials
        const char* ssid = "****";
        const char* password = "*****"; 
        WiFiClientSecure client;
        const byte MAX_ATTEMPTS = 15;

        bool checkConection(){
            if (WiFi.status() == WL_CONNECTED){
                return 1;
            }
            return 0;
        }

    public:

        WiFiMananger(){
            #ifdef ESP8266
                configTime(0, 0, "pool.ntp.org");      // get UTC time via NTP
                // client.setTrustAnchors(&cert); // Add root certificate for api.telegram.org
            #endif
            WiFi.mode(WIFI_STA);
        };

        bool beginConnection(){
            Serial.begin(115200);
            WiFi.begin(ssid, password);
            byte attempts = 0;
            while (WiFi.status() != WL_CONNECTED) {
                delay(1000);
                Serial.println("Connecting to WiFi..");
                if (attempts >= MAX_ATTEMPTS)
                {
                    break;
                }
                attempts = attempts++;
            }
            bool connected = checkConection();
            if(connected == 1){
                // Print ESP32 Local IP Address
                Serial.println(WiFi.localIP());
                return 1;
            }    
            Serial.println("Connecting wifi Error..");
            return 0;
        }
    
   };
