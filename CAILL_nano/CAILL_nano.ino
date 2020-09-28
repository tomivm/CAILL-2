
#include <Wire.h>
#include <RtcDS3231.h>
  RtcDS3231<TwoWire> Rtc(Wire);
  RtcDateTime now; 

#define Lampara 4

const byte HoraEncender = 22;
const byte MinEncender = 0;

const byte HorasDeLuz = 11;

int minutoQueSeEnciende;
int minutoQueSeApaga;
unsigned int minutosParciales; //Minuto en el que se encuentra el rtc 

bool apagarAlOtroDia=0;



void setup() {
Serial.begin(115200);
int Hora = 21;
int Min = 59;

Rtc.Begin();
RtcDateTime modify = RtcDateTime(now.Year(), now.Month(),now.Day(),Hora,Min,0); 
              Rtc.SetDateTime(modify);        //Set new values of time in the RTC
//
//RtcDateTime compiled = RtcDateTime(2020 , 9, 26, 8, 59, 00);
//          Rtc.SetDateTime(compiled);


  
minutoQueSeEnciende = convertToMin(HoraEncender)+ MinEncender;
minutoQueSeApaga = convertToMin(HorasDeLuz)+ minutoQueSeEnciende;

if (minutoQueSeApaga >= 23*60+59)
          {
            minutoQueSeApaga = minutoQueSeApaga - 23*60-59;
            apagarAlOtroDia = 1;
          }
}

void loop() {
  // put your main code here, to run repeatedly:
  now = Rtc.GetDateTime();  //get the time from the RTC     
  minutosParciales = now.Hour()*60+now.Minute();

  Serial.println("Hora:");
  Serial.println(now.Hour());
  Serial.println("Minuto:");
  Serial.println(now.Minute());

  ChequearLampara();
  delay(500);

  
}       

int convertToMin(byte hora) {
  return hora*60;
}

void ChequearLampara(void){
  if (apagarAlOtroDia == 1) //manera en que la lampara identifica su estado, si su momento de apagar esta al otro dia del momento de prender
      {        
        if(minutosParciales>=minutoQueSeEnciende || minutosParciales <= minutoQueSeApaga )
          {
            digitalWrite(Lampara,HIGH);
            //poa = 1;
          }
        else
          {
          digitalWrite(Lampara, LOW);
          //poa = 0;   
          }
        
      }
  else
      {
        if((minutosParciales >= minutoQueSeEnciende) && (minutosParciales <minutoQueSeApaga))
          {
            digitalWrite(Lampara, HIGH);
            //poa = 1;
          }
        else
          {
            digitalWrite(Lampara, LOW);
            //poa = 0;  
          }
      }
}      
