#include <Arduino.h>
#include "avr8-stub.h"
#include "ChainableLED.h"
//#include "DS1307.h"
#include "SoftwareSerial.h"
#include "Variable.h"

ChainableLED LED (3,4,1);

ISR(TIMER1_COMPA_vect) {
  if((flag1 || flag2) == 1 && mode != 1) {
    if(Compteur) {
      Compteur--;
    }
  }

  if(mode == 1) {
    if(Compteur) {
      Compteur--;
    } else {
      mode = 0;
      reactiveCapt();
    }
  }
}

void init_timer(long uSec) {
  noInterrupts();
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1 = 0;
  OCR1A = (16e6/(256+uSec));

}


void setup() {
  //Initialisation de la LED
  LED.init();
  //Serial.begin(9600);
  printf("%c",Bouton1);

  
}

void loop() {
  LED.setColorRGB(0,255,0,255);
}

