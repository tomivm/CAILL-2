#include <UniversalTelegramBot.h>   // Universal Telegram Bot Library written by Brian Lough: https://github.com/witnessmenow/Universal-Arduino-Telegram-Bot
#include <ArduinoJson.h>
#include <WiFiClientSecure.h> // esp8266 version 2.7.4 or less

#define BOTtoken "***************************"  // your Bot Token (Get from Botfather)

// Use @myidbot to find out the chat ID of an individual or a group
// Also note that you need to click "start" on a bot before it can
// message you
#define CHAT_ID "***********"

#ifdef ESP8266
    X509List cert(TELEGRAM_CERTIFICATE_ROOT);
#endif

class TelegramBot{  
    private:
        String name;
        //UniversalTelegramBot bot;
        // UniversalTelegramBot bot(BOTtoken, client);
        // {
        //     UniversalTelegramBot bot(BOTtoken, client);
        //     return bot;
        // }
        //UniversalTelegramBot bot;
        UniversalTelegramBot *bot;//(BOTtoken, *client);
    public:

        TelegramBot(WiFiClientSecure client){
            #ifdef ESP8266
                configTime(0, 0, "pool.ntp.org");      // get UTC time via NTP
                client.setTrustAnchors(&cert); // Add root certificate for api.telegram.org
            #endif
            #ifdef ESP32
                client.setCACert(TELEGRAM_CERTIFICATE_ROOT); // Add root certificate for api.telegram.org
            #endif

            //UniversalTelegramBot bot(BOTtoken, client);
            // pinMode(ledPin, OUTPUT);
            // digitalWrite(ledPin, ledState);
            bot = new UniversalTelegramBot (BOTtoken, client);
        }
        // TelegramBot(UniversalTelegramBot telegramBot){
        //     bot = telegramBot;
        // }

        void handleNewMessages(int numNewMessages) {
            Serial.println("handleNewMessages");
            Serial.println(String(numNewMessages));

            for (int i=0; i<numNewMessages; i++) {
                //Chat id of the requester
                String chat_id = String(bot.messages[i].chat_id);
                // if (chat_id != CHAT_ID){
                //   bot.sendMessage(chat_id, "Unauthorized user", "");
                //   continue;
                // }
                
                // Print the received message
                String text = *bot.messages[i].text;
                Serial.println(text);

                String from_name = bot.messages[i].from_name;

                if (text == "/start") {
                String welcome = "Welcome, " + from_name + ".\n";
                welcome += "Use the following commands to control your outputs.\n\n";
                welcome += "/led_on to turn GPIO ON \n";
                welcome += "/led_off to turn GPIO OFF \n";
                welcome += "/state to request current GPIO state \n";
                bot.sendMessage(chat_id, welcome, "");
                }

                if (text == "/led_on") {
                bot.sendMessage(chat_id, "LED state set to ON", "");
                // ledState = HIGH;
                // digitalWrite(ledPin, ledState);
                }
                
                if (text == "/led_off") {
                bot.sendMessage(chat_id, "LED state set to OFF", "");
                // ledState = LOW;
                // digitalWrite(ledPin, ledState);
                }
                
                if (text == "/state") {
                // if (digitalRead(ledPin)){
                //     bot.sendMessage(chat_id, "LED is ON", "");
                // }
                // else{
                //     bot.sendMessage(chat_id, "LED is OFF", "");
                // }
                }
            }
        }
   };
