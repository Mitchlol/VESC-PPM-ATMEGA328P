#include "vesc-ppm-atmega328p.h"

VescPPM vesc;

void setup() {
  vesc.setup();
}

float value = -1;
void loop() {
  value += .01;
  if(value > 1){
    value = -1;
  }
  vesc.setValue(value);
  delay(10);
}
