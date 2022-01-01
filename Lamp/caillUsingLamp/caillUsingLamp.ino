#include "Lamp.h"

#define LAMP_PIN 4

int Hora = 9;
int Min = 32;

int horaEncendido = 21, minEncendido = 30, horasDeLuz = 12 ; 

Lamp Lamp1(4);
void setup() {
    Lamp1.setLampTime( horaEncendido, minEncendido, horasDeLuz );
}

void loop() {  
  bool lamp = Lamp1.updateLampState(Hora, Min);
  
  delay(500);
}
