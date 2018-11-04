#include "vesc-ppm-atmega328p.h"

uint16_t ppm_internal_value = ONE_MILLI *.5;

VescPPM::VescPPM(){
}

void VescPPM::setup(){
  // Set pin to output
  DDRD |= (1 << PPM_PIN);

  // Clear Timer/Counter1 Control Register A & B
  TCCR1A = 0;
  TCCR1B = 0;

  // Set Max count value
  OCR1A = ONE_MILLI *.5;

  // Set waveform generation mode/ Turn on CTC mode
  TCCR1B |= (1 << WGM12);

  // Set clock mode/prescaler, no prescale
  TCCR1B |= (1 << CS10);

  // Enable timer compare interrupt
  TIMSK1 = (1 << OCIE1A);
}

void VescPPM::setValue(float new_value){
  if(new_value > 1){
    new_value = 1;
  }else if(new_value < -1){
    new_value = -1;
  }
  ppm_internal_value = ONE_MILLI + ((ONE_MILLI + (new_value * ONE_MILLI)) / 2) - MICROS_OFFSET_FIX;
}

ISR(TIMER1_COMPA_vect) {
  if(PORTD & (1 << PPM_PIN) == 1){
    OCR1A = ONE_MILLI * .5;
  }else{
    OCR1A = ppm_internal_value;
  }
  PORTD ^= (1 << PPM_PIN);
}
