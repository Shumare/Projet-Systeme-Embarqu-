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

void init_timer(long uSecs) {
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

void switchMode() {
  if(flag1 == 1) {
    flag1 = 0;
    if(mode == (0 || 3) &&  Compteur == 0){
      mode = 2;
      LED.setColorRGB(0,255,165,0);
    } else {
      mode = 1;
      LED.setColorRGB(0,255,255,0);
      Compteur = 30 * 1000 * 60;
    }

    if(mode == 2 && Compteur == 0){
      mode = 0;
    }
    return;
  }

  if(flag1 == 0){
    Compteur = 5000;
    flag1 = 1;
    return;
  }

  if(flag2 == 1) {
    flag2 = 0;
    if(mode == 0 && Compteur == 0) {
      mode = 3;
      LED.setColorRGB(0,0,0,255);
    }

    if(mode == 3 && Compteur == 0) {
      mode = 0;
    }
    return;

  }

  if(flag2 == 0) {
    Compteur = 5000;
    flag2 = 1;
    return;
  }

}

void init_Interrupt() {
  attachInterrupt(digitalPinToInterrupt(Bouton1),switchMode(),CHANGE);
  attachInterrupt(digitalPinToInterrupt(Bouton2),switchMode(),CHANGE);
}


void setup() {
  //Initialisation de la LED
  LED.init();
  Serial.begin(9600);
  printf("%c",Bouton1);
  pinMode(Bouton1, INPUT);
  pinMode(Bouton2, INPUT);

  init_timer(5000);

  init_Interrupt();

  
}

void loop() {

}

