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

void configEEPROM(capteur *E,addresse){
    if(E != NULL) {
        if(EEPROM.read (addresse) == 255){
            EEPROM.put(addresse,E -> min);
            E-> minActuel = E -> min
            if(E -> min < 256){
            addresse++
            }
            else{
                addresse = addresse +2;
            }
            EEPROM.put(addresse,E -> max);
            E-> maxActuel = E -> max
            if(E -> max < 256){
            addresse++
            }
            else{
                addresse = addresse +2;
            }
        } 
    }
    configEEPROM(E-> next,addresse);
}



String getTime()
{
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