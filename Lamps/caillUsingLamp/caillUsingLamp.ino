#include "Lamps.h"

#define LAMP_PIN 4

int Hora = 9;
int Min = 32;

int horaEncendido = 21, minEncendido = 30, horasDeLuz = 12 ; 

Lamps Lamp1(4);
void setup() {
    Lamp1.SetLampTime( horaEncendido, minEncendido, horasDeLuz );
}

void loop() {  
  bool lamp = Lamp1.getLampState(Hora, Min);
  
  delay(500);
}