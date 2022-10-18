#include <stdio.h>
#include <stdlib.h>

#include "Fonction.h"

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
void configEEPROM2(){
    if(EEPROM.read(10) == 255){
    EEPROM.put(10,TIME_OUT);      
    }
    if(EEPROM.read(11) == 255){
    EEPROM.put(11,LOG_INTERVAL);      
    }
    if(EEPROM.read(13) == 255){
    EEPROM.put(13,FILE_MAX_SIZE);      
    }
}


void enterNewParam(){
    char capteurModif;
    float valeurModif;
    printf("\nVeillez entrer le capteur qui doit etre modifiÃ©: ");
    scanf("%c", capteurModif);
    printf("\nVeillez entrer la nouvelle valeur : ");
    scanf("%f", valeurModif);
}

void checkParam(char capteurModif, float valeurModif){
    if(capteurModif == "Pression_Min"){
        if(valeurModif > Capt_Pression->min){
        EEPROM.put(0,valeurModif);
        Capt_Pression -> minActuel = valeurModif;
        }
        else{
            Serial.println("Valeur non valide");
        }
    }
    if(capteurModif == "Pression_Max"){
        if(valeurModif < Capt_Pression->max){
        EEPROM.put(2,valeurModif);
        Capt_Pression -> maxActuel = valeurModif;
        }
        else{
            Serial.println("Valeur non valide");
        }
    }
    if(capteurModif == "Lumin_Min"){
        if(valeurModif > Capt_Lumin->min){
        EEPROM.put(4,valeurModif);
        Capt_Lumin -> min = valeurModif;
        }
        else{
            Serial.println("Valeur non valide");
        }
    }
    if(capteurModif == "Lumin_Max"){
        if(valeurModif < Capt_Lumin->max){
        EEPROM.put(5,valeurModif);
        Capt_Lumin -> max = valeurModif;
        }
        else{
            Serial.println("Valeur non valide");
        }
    }
    if(capteurModif == "Temp_Min"){
        if(valeurModif > Capt_Temp->min){
        EEPROM.put(6,valeurModif);
        Capt_Temp -> min = valeurModif;
        }
        else{
            Serial.println("Valeur non valide");
        }
    }
    if(capteurModif == "Temp_Max"){
        if(valeurModif < Capt_Temp->max){
        EEPROM.put(7,valeurModif);
        Capt_Temp -> min = valeurModif;
        }
        else{
            Serial.println("Valeur non valide");
        }
    }
    if(capteurModif == "Hygr_Min"){
        if(valeurModif > Capt_Hygr->min){
        EEPROM.put(8,valeurModif);
        Capt_Hygr -> min = valeurModif;
        }
        else{
            Serial.println("Valeur non valide");
        }
    }
    if(capteurModif == "Hygr_Max"){
        if(valeurModif < Capt_Hygr->max){
        EEPROM.put(9,valeurModif);
        Capt_Hygr -> max = valeurModif;
        }
        else{
            Serial.println("Valeur non valide");
        }
    }
    if(capteurModif == "TIME_OUT"){
        EEPROM.put(10,valeurModif);
        TIME_OUT = valeurModif; 
    }
    if(capteurModif == "LOG_INTERVAL"){
        EEPROM.put(11,valeurModif);
        LOG_INTERVAL = valeurModif; 
    }
    if(capteurModif == "FILE_MAX_SIZE"){
        EEPROM.put(13,valeurModif);
        FILE_MAX_SIZE = valeurModif; 
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

void stockSD(String stockage) {
    //création du nom de fichier
    clock.getTime();
    String annee = String(clock.year + 2000, DEC);
    String mois = String(clock.month, DEC);
    String jour = String(clock.dayOfMonth, DEC);
    String filename = annee;
    filename += mois;
    filename += jour;
    filename += ("_0.LOG");
    char file[15];
    filename.toCharArray(file, 15);

    File datafile = SD.open(file);

    if (datafile) {
        //regarde si le fichier n'est pas plein
        if (datafile.size() >= FILE_MAX_SIZE) {
            Serial.println("Fichier plein, création d'un nouveau");
            datafile.seek(0);
            num_rev++;
            String oldData;
            while (datafile.available()) {
                oldData += String(datafile.read(), DEC);
                oldData += String("\n");
            }
            datafile.close();
            SD.remove(file);
            datafile = SD.open(file, FILE_WRITE);
            if (datafile) {
                datafile.println(stockage);
                datafile.close();
            }

            filename = annee;
            filename += mois;
            filename += jour;
            filename += String("_");
            filename += String(num_rev, DEC);
            filename += String(".LOG");
            char file2[15];
            filename.toCharArray(file2, 15);
            datafile = SD.open(file2, FILE_WRITE);
            if (datafile) {
                datafile.println(oldData);
                datafile.close();
            }
        } else {
            datafile.close();
            datafile = SD.open(file, FILE_WRITE);
            datafile.println(stockage);
            datafile.close();
        }
    }
}