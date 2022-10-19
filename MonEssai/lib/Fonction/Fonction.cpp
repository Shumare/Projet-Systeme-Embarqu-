#include <stdio.h>
#include <stdlib.h>

#include "Fonction.h"

void voirEEPROM() {
    int address = 0;
    byte value;
    Serial.begin(9600);
    delay(3000);

    while (address < 20) {
        value = EEPROM.read(address);
        Serial.print("Address: ");
        Serial.print(String(address));
        Serial.print(", value: ");
        Serial.println(String(value));
        address++;
        delay(100);
    }
}

void resetEEPROM() {
    int address = 0;
    byte value; 
        while (address < 25) {
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
    
    Capt_Pression -> name = "Pression";
    Capt_Lumin -> name = "Lumin";
    Capt_Temp -> name = "Temp";
    Capt_Hygr -> name = "Hygr";
}

void configEEPROM(){
    EEPROM.put(0,Capt_Pression -> min);
    EEPROM.put(2,Capt_Pression-> max);
    EEPROM.put(4,Capt_Lumin -> min);
    EEPROM.put(6,Capt_Lumin-> max);
    EEPROM.put(8,Capt_Temp -> min +40);
    EEPROM.put(9, Capt_Temp -> max +40);
    EEPROM.put(10,Capt_Hygr -> min + 40);
    EEPROM.put(11,Capt_Hygr -> max + 40);
    EEPROM.put(12,TIME_OUT);
    EEPROM.put(13,LOG_INTERVAL);
    EEPROM.put(15,FILE_MAX_SIZE);
}

void stockVariable(){
    EEPROM.put(0,Capt_Pression -> minActuel);
    EEPROM.put(2,Capt_Pression-> maxActuel);
    EEPROM.put(4,Capt_Lumin -> minActuel);
    EEPROM.put(6,Capt_Lumin-> maxActuel);
    EEPROM.put(8,Capt_Temp -> minActuel+40);
    EEPROM.put(9, Capt_Temp -> maxActuel+40);
    EEPROM.put(10,Capt_Hygr -> minActuel+40);
    EEPROM.put(11,Capt_Hygr -> maxActuel+40);
    EEPROM.put(12,TIME_OUT);
    EEPROM.put(13,LOG_INTERVAL);
    EEPROM.put(15,FILE_MAX_SIZE);
}

void setupMaxMin(){
    Capt_Pression->minActuel = EEPROM.read(0)+EEPROM.read(1)*256;
    Capt_Pression->maxActuel = EEPROM.read(2)+EEPROM.read(3)*256;
    Capt_Lumin->minActuel = EEPROM.read(4)+EEPROM.read(5)*256;
    Capt_Lumin->maxActuel = EEPROM.read(6)+EEPROM.read(7)*256;
    Capt_Temp->minActuel= EEPROM.read(8) -40;
    Capt_Temp->maxActuel= EEPROM.read(9) -40;
    Capt_Hygr->minActuel=EEPROM.read(10) - 40 ;
    Capt_Hygr->maxActuel=EEPROM.read(11) - 40 ;
}

void voirMinMax(){
    Serial.println(Capt_Pression->minActuel);
    Serial.println(Capt_Pression->maxActuel);
    Serial.println(Capt_Lumin->minActuel);
    Serial.println(Capt_Lumin->maxActuel);
    Serial.println(Capt_Temp->minActuel);
    Serial.println(Capt_Temp->maxActuel);
    Serial.println(Capt_Hygr->minActuel);
    Serial.println(Capt_Hygr->maxActuel);
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

String demandeDonnee(capteur *Capt) {
    if(Capt->active){
        if (Capt->name == "Hygr"){
            while (isnan(bme.readHumidity())) {
                if (ActiveTimeOut == 0) {
                    Compteur = TIME_OUT;
                    ActiveTimeOut = 1;
                }
                if (Compteur == 0) {
                    ActiveTimeOut = 0;
                    return(String("NA"));
                }
            }
            ActiveTimeOut = 0;
            return String(bme.readHumidity(), DEC);
        }
        if (Capt->name == "Lumin"){
            while (isnan(analogRead(Capt->port))) {
                if (ActiveTimeOut == 0) {
                    Compteur = TIME_OUT;
                    ActiveTimeOut = 1;
                }
                if (Compteur == 0) {
                    ActiveTimeOut = 0;
                    return(String("NA"));
                }
            }
            ActiveTimeOut = 0;
            return String(analogRead(Capt->port), DEC);
        }

        if (Capt->name == "Pression") {
            while (isnan(bme.readPressure())) {
                if (ActiveTimeOut == 0) {
                    Compteur = TIME_OUT;
                    ActiveTimeOut = 1;
                }
                if (Compteur == 0) {
                    ActiveTimeOut = 0;
                    return(String("NA"));
                }
            }
            ActiveTimeOut = 0;
            return String(bme.readPressure());
        }

        if (Capt->name == "Temp"){
            while (isnan(bme.readTemperature())) {
                if (ActiveTimeOut == 0) {
                    Compteur = TIME_OUT;
                    ActiveTimeOut = 1;
                }
                if (Compteur == 0) {
                    ActiveTimeOut = 0;
                    return(String("NA"));
                }
            }
            ActiveTimeOut = 0;
            return String(bme.readTemperature(), DEC);
        }
    }
}

void desactiveCapteur(){
    Capt_Hygr->active = 0;
    Capt_Lumin->active = 0;
    Capt_Pression->active = 0;
    Capt_Temp->active = 0;
}

void reactiveCapteur(){
    Capt_Hygr->active = 1;
    Capt_Lumin->active = 1;
    Capt_Pression->active = 1;
    Capt_Temp->active = 1;
}

void enterNewParam(){
    
    String capteurModif;
    float valeurModif;
    Serial.print("Veuillez entrer la commande: ");
    while (Serial.available() == 0 );
    while (Serial.available() > 0)
    {
      capteurModif = Serial.readString();
      delay(100); 
    }
    capteurModif.trim();

    int i = capteurModif.indexOf("=");
    String v_inter = capteurModif.substring(i+1, capteurModif.length());
    v_inter.trim();
    valeurModif = v_inter.toFloat();
    capteurModif = capteurModif.substring(0, i);
    
    Serial.println("");
    checkParam(capteurModif, valeurModif);
}

void checkParam(String capteurModif, float valeurModif){
    if(capteurModif == "PRESSURE_MIN"){
        if(valeurModif > Capt_Pression->min){
        Capt_Pression -> minActuel = valeurModif;
        }
        else{
            Serial.println("Valeur non valide");
        }
    }
    if(capteurModif == "PRESSURE_MAX"){
        if(valeurModif < Capt_Pression->max){
        Capt_Pression -> maxActuel = valeurModif;
        }
        else{
            Serial.println("Valeur non valide");
        }
    }
    if(capteurModif == "LUMIN_LOW"){
        if(valeurModif > Capt_Lumin->min){
        Capt_Lumin -> min = valeurModif;
        }
        else{
            Serial.println("Valeur non valide");
        }
    }
    if(capteurModif == "LUMIN_HIGH"){
        if(valeurModif < Capt_Lumin->max){
        Capt_Lumin -> max = valeurModif;
        }
        else{
            Serial.println("Valeur non valide");
        }
    }
    if(capteurModif == "MIN_TEMP_AIR"){
        if(valeurModif > Capt_Temp->min){
        Capt_Temp -> min = valeurModif;
        }
        else{
            Serial.println("Valeur non valide");
        }
    }
    if(capteurModif == "MAX_TEMP_AIR"){
        if(valeurModif < Capt_Temp->max){
        Capt_Temp -> min = valeurModif;
        }
        else{
            Serial.println("Valeur non valide");
        }
    }
    if(capteurModif == "HYGR_MINT"){
        if(valeurModif > Capt_Hygr->min){
        Capt_Hygr -> min = valeurModif;
        }
        else{
            Serial.println("Valeur non valide");
        }
    }
    if(capteurModif == "HYGR_MAXT"){
        if(valeurModif < Capt_Hygr->max){
        Capt_Hygr -> max = valeurModif;
        }
        else{
            Serial.println("Valeur non valide");
        }
    }
    if(capteurModif == "TIME_OUT"){
        TIME_OUT = valeurModif;
    }
    if(capteurModif == "LOG_INTERVAL"){
        LOG_INTERVAL = valeurModif;
    }
    if(capteurModif == "FILE_MAX_SIZE"){
        FILE_MAX_SIZE = valeurModif;
    }
}