#include "Arduino.h"

#ifdef ESP32
  #include <WiFi.h>
#elif defined(ESP8266)
    #include <ESP8266WiFi.h>
    #include <WiFiClientSecure.h>
#endif

class WiFiMananger{  
    private:
        String name;
            // Replace with your network credentials
        const char* ssid = "Tomas";
        const char* password = "23112001Agus";

        const byte MAX_ATTEMPTS = 15;

        bool checkConnection(){
            if (WiFi.status() == WL_CONNECTED){
                return 1;
            }
            return 0;
        }
        

    public:
        //WiFiClientSecure client;
        //*client

        
        WiFiMananger(){
            // #ifdef ESP8266
            //     configTime(0, 0, "pool.ntp.org");      // get UTC time via NTP
            // #endif
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
                attempts++;
            }
            bool connected = checkConnection();
            if(connected == 1){
                // Print ESP32 Local IP Address
                Serial.println(WiFi.localIP());
                return 1;
            }    
            Serial.println("Connecting wifi Error..");
            return 0;
        }

        bool isConnected(){
            return checkConnection();
        }

   };
