#include <stdio.h>
#include <stdlib.h>

#include "Fonction.h"


void enterNewParam(){
    char capteurModif;
    float valeurModif;
    printf("\nVeillez entrer le capteur qui doit etre modifié: ");
    scanf("%c", capteurModif);
    printf("\nVeillez entrer la nouvelle valeur : ");
    scanf("%f", valeurModif);
}
void resetEEPROM() {
  int address = 0;
  byte value; 
    while (address < EEPROM.length()) {
      EEPROM.write(address,255);
      value = EEPROM.read(address);
      Serial.print("Address: ");
      Serial.print(String(address));
      Serial.print(", value: ");
      Serial.println(String(value));
      address++;
      delay(100);
   }
}
void initCapteur(){
Capt_Pression->active = 1;
Capt_Lumin->active = 1;
Capt_Temp->active = 1;
Capt_Hygr->active = 1;

Capt_Pression -> min = 850;
Capt_Pression -> max = 1080;
Capt_Lumin -> min = 256;
Capt_Lumin -> max = 768;
Capt_Temp -> min = -10;
Capt_Temp -> max = 60;
Capt_Hygr -> min = 0;
Capt_Hygr -> max = 50;

Capt_Pression -> minCapteur = 300;
Capt_Pression -> maxCapteur = 1100;
Capt_Lumin -> minCapteur = 0;
Capt_Lumin -> maxCapteur = 1023;
Capt_Temp -> minCapteur = -40;
Capt_Temp -> maxCapteur = 85;
Capt_Hygr -> minCapteur = -40;
Capt_Hygr-> maxCapteur = 85;

Capt_Pression -> next = Capt_Lumin;
Capt_Lumin -> next = Capt_Temp;
Capt_Temp -> next = Capt_Hygr;
Capt_Hygr-> next = NULL;
}

void configEEPROM(capteur *E,int addresse){
    if(E != NULL) {
        if(EEPROM.read (addresse) == 255){
            EEPROM.put(addresse,E -> min);
            E-> minActuel = E -> min;
            if(E -> min < 256){
            addresse++;
            }
            else{
                addresse = addresse +2;
            }
            EEPROM.put(addresse,E -> max);
            E-> maxActuel = E -> max;
            if(E -> max < 256){
            addresse++;
            }
            else{
                addresse = addresse +2;
            }
        } 
    configEEPROM(E-> next,addresse);
}
}


String getTime(){
    String time="";
    clock.getTime();
    time+=String(clock.hour, DEC);
    time+=String(":");
    time+=String(clock.minute, DEC);
    time+=String(":");
    time+=String(clock.second, DEC);
    time+=String("  ");
    time+=String(clock.month, DEC);
    time+=String("/");
    time+=String(clock.dayOfMonth, DEC);
    time+=String("/");
    time+=String(clock.year+2000, DEC);
    time+=String(" ");
    time+=String(clock.dayOfMonth);
    time+=String("*");
    switch (clock.dayOfWeek)// Friendly printout the weekday
    {
        case MON:
        time+=String("MON");
        break;
        case TUE:
        time+=String("TUE");
        break;
        case WED:
        time+=String("WED");
        break;
        case THU:
        time+=String("THU");
        break;
        case FRI:
        time+=String("FRI");
        break;
        case SAT:
        time+=String("SAT");
        break;
        case SUN:
        time+=String("SUN");
        break;
    }
    time+=String(" ");
    return time;
}