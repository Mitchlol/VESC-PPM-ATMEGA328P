#ifndef VESCPPMATMEGA328P_H_
#define VESCPPMATMEGA328P_H_

#include "arduino.h"

#define PPM_PIN 5
#define ONE_MILLI 16000000/1000
#define MICROS_OFFSET_FIX (ONE_MILLI/1000) * 217

class VescPPM {

public:
  VescPPM();
  void setup();
  void setValue(float value);
private:
  
};

#endif
