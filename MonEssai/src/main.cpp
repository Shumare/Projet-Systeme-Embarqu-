#include <Arduino.h>
#include "avr8-stub.h"
#include "ChainableLED.h"
//#include "DS1307.h"
#include "SoftwareSerial.h"
#include "Variable.h"




ChainableLED LED (3,4,1);

void setup() {
  //Initialisation de la LED
  LED.init();
  //Serial.begin(9600);
  printf("%c",Bouton1);

  
}

void loop() {
  LED.setColorRGB(0,255,0,255);
}

