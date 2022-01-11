
#include "DHT.h"

//#define DHTTYPE DHT21   // DHT 21 (AM2301)

// Initialize DHT sensor for normal 16mhz Arduino
DHT dht(12, DHT22);

class TemperatureHumidity{  
    private:
        // void createDht(byte DHTPIN, byte DHTTYPE){
        //     DHT dht(DHTPIN, DHTTYPE);
        // };
        
    public:
        TemperatureHumidity(){
            
            // createDht(dhtPin,dhtType);
            Serial.println("DHTxx test!");
            dht.begin();
        };
        
        int getTemperature () {
            float t = dht.readTemperature();
            if (isnan(t)) {
                Serial.println("Failed to read from DHT sensor!");
                return 0;
            }
            int temperature = round(t);  
            return temperature;
        };
        
        int getHumidity () {
            float h = dht.readHumidity();
            if (isnan(h)) {
                Serial.println("Failed to read from DHT sensor!");
                return 0;
            }
            int humidity = round(h);  
            return humidity;
        };
    
};
