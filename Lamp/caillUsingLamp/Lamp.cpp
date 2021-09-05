// #include "Lamps.h"

// Lamps::Lamps(byte pin){
//     pinOut = pin;
//     //setLampTime();
// }      

// int Lamps::convertTimeToMinutes (byte hour, byte min = 0){
//     {
//     if (!hour){
//         return hour*60 + min;
//     }   
//     return 0;
//     }
// }

// void Lamps::minutesToSwitch( byte onHourParameter, byte onMinParameter, byte lightHoursParameter ){
//     turnOnMinute = convertTimeToMinutes( onHourParameter, onMinParameter );
//     turnOffMinute = convertTimeToMinutes(lightHoursParameter) + turnOnMinute;
//     if (turnOffMinute >= 1439/*23*60+59*/){
//         turnOffMinute = turnOffMinute - 1439;
//         turnOffTomorrow = true;
//         return;
//     }
//     turnOffTomorrow = false;
// }

// void Lamps::setLampPin(byte pin){
//             pinOut = pin; 
//         }

// void Lamps::SetLampTime( int onHourParameter, int onMinParameter, int lightHoursParameter ){
//             lightHours = lightHoursParameter;
//             minutesToSwitch( onHourParameter, onMinParameter, lightHoursParameter);
//         } 

// bool Lamps::getLampState(byte nowHour, byte nowMinute){
//             int nowTimeInMin = convertTimeToMinutes( nowHour, nowMinute);
//             if (turnOffTomorrow){ //manera en que la lampara identifica su estado, si su momento de apagar esta al otro dia del momento de prender
//                 if(nowTimeInMin >= turnOnMinute || nowTimeInMin <= turnOffMinute ){
//                     digitalWrite( pinOut, HIGH);
//                     return 1;
//                 }
//                 digitalWrite( pinOut, LOW);
//                 return 0;   
                
//             }
//             if((nowTimeInMin >= turnOnMinute) && (nowTimeInMin < turnOffMinute)){
//                 digitalWrite(pinOut, HIGH);
//                 return 1;
//             }
//             digitalWrite(pinOut, LOW);
//             return 0;  
//         } 
