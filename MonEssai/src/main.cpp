#include <Arduino.h>
#include "avr8-stub.h"
#include "ChainableLED.h"
//#include "DS1307.h"
#include "SoftwareSerial.h"
#include "Variable.h"



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
  OCR1A = ((16e6 / 256L * uSecs) / (1e6) )- 1;
  TCCR1B |= (1 << WGM12);   
  TCCR1B |= (1 << CS12);     
  TIMSK1 |= (1 << OCIE1A);  
  interrupts();  
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

