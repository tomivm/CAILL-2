#include "./Modules/Lamp.h"
#include "./Modules/AirConditioner.h"
#include "./Modules/Clock.h"
#include "./Modules/TemperatureHumidity.h"

#if defined(ESP8266)
// NODEMCU - ESP8266 specific code here
  #include "./Modules/WiFiMananger.h"
  #define SUPPORT_WIFI 1
  #include <WiFiClientSecure.h> // esp8266 version 2.7.4 or less
  extern WiFiClientSecure client;
  WiFiMananger WiFiMananger;
  #include "./Modules/TelegramBot.h"
  //TelegramBot bot(WiFiMananger.client);
  TelegramBot bot(client);

  #define LAMP_PIN D3
  #define LAMP_ON_LEVEL 0
  #define AIR_CONDITIONER_PIN 2
#else
// Nano or other code here
  #define LAMP_PIN 4//------------------ in CAILL_nano
  #define LAMP_ON_LEVEL 1 // ------ in CAILL_nano
  #define AIR_CONDITIONER_PIN 2
#endif


// DHT PINS DEFINE ALREADY NOT WORKING
// #define DHTPIN 12     
// //#define DHTTYPE DHT11   // DHT 11 
// #define DHTTYPE DHT22   // DHT 22  (AM2302)

bool setTime = false; ///if true, the time of clock is seted with the next int vars
int hour = 1;
int minute = 49;

byte temperature = 28;

int horaEncendido = 20, minEncendido = 0, horasDeLuz = 12 ;
byte wantedTemperatureDay = 30, maxTemperatureDay = 33; 
byte wantedTemperatureNight = 30, maxTemperatureNight = 33; 

// Checks for CAILL state every 10 second.
const int REFRESH_DELAY = 10000;
unsigned long lastTimeRefresh;

// Checks for new messages every 1 second.
int botRequestDelay = 1000;
unsigned long lastTimeBotRan;


Clock RealTimeClock(setTime, hour, minute);
Lamp Lamp1(LAMP_PIN, LAMP_ON_LEVEL);
AirConditioner AirConditioner1(AIR_CONDITIONER_PIN);

TemperatureHumidity TandHSensor1;

int convertTimeToMinutes (byte hour, byte min = 0){
    const byte HOUR_IN_MINUTES = 60;
    if (hour){
        return hour * HOUR_IN_MINUTES + min;
    }   
    return min;
}

void refreshTime(){
  RealTimeClock.getTimeStamp();
  hour = RealTimeClock.now.Hour();
  minute = RealTimeClock.now.Minute();
  Serial.println("Time");
  Serial.print(hour);
  Serial.print(" : ");
  Serial.println(minute);  
}

void refreshTemperature(){
  int t = TandHSensor1.getTemperature();
  if(t) {
    temperature = t;
    Serial.println("");
    Serial.print("T:");
    Serial.println(temperature);
    return;
  }
};

void checkWiFi(){
  bool isConnected = WiFiMananger.isConnected();
  if(isConnected == 0){
    WiFiMananger.beginConnection();
  }
}

void setup() {

    refreshTime();
    refreshTemperature();
    Lamp1.setLampTime( horaEncendido, minEncendido, horasDeLuz );

    AirConditioner1.setAirConditionerDayTemperatures( wantedTemperatureDay, maxTemperatureDay);
    AirConditioner1.setAirConditionerNightTemperatures( wantedTemperatureNight, maxTemperatureNight);

    if(SUPPORT_WIFI == 1) {
      bool wifiConnected = WiFiMananger.beginConnection();
    }
}

void loop() {  

  if (millis() > lastTimeRefresh + REFRESH_DELAY)  {
    //----------------
    refreshTime();
    refreshTemperature();

    bool lamp = Lamp1.updateLampState(hour, minute);
    bool AC = AirConditioner1.updateAcState(temperature, Lamp1.getLampState(), convertTimeToMinutes(hour, minute), Lamp1.getTurnOnMinute());
    Serial.print("Air:");
    Serial.print(AC);

   //-------------------------

    lastTimeRefresh = millis();
  }

  if (millis() > lastTimeBotRan + botRequestDelay)  {

    checkWiFi();

    lastTimeBotRan = millis();
  }
}
