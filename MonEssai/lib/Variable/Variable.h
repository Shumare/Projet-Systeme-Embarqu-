#ifndef Variable_H_INCLUDED
#define Variable_H_INCLUDED


#include "Arduino.h"
#include "string.h"
//#include "avr8-stub.h"
#include "ChainableLED.h"
#include "DS1307.h"
#include "SoftwareSerial.h"
#include <SPI.h>
#include <SD.h>
#include <EEPROM.h>
#include <Adafruit_BME280.h>



#define adresseI2CduBME280                0x76            // Adresse I2C du BME280 (0x76, qui est souvent la valeur par défaut)
#define pressionAuNiveauDeLaMerEnHpa      1024.90         // (1013.25 hPa en moyenne, valeur "par défaut")
#define delaiRafraichissementAffichage    1500            // Délai de rafraîchissement de l'affichage (en millisecondes)

SoftwareSerial SoftSerial(4, 5);
DS1307 clock;
// Instanciation de la librairie BME280
Adafruit_BME280 bme;

const int Bouton1 = 2; //Bouton rouge
const int Bouton2 = 3; //Bouton vert


//capteurs
typedef struct capt {
    unsigned short port;
    bool active;
    int min;
    int max;
    int minCapteur;
    int maxCapteur;
    int minActuel;
    int maxActuel;
    struct capt *next;
} capteur;

capteur Capt_Pression;
capteur Capt_Lumin;
capteur Capt_Temp;
capteur Capt_Hygr;

Capt_Pression = malloc(sizeof(capteur));
Capt_Lumin = malloc(sizeof(capteur));
capt_Temp = malloc(sizeof(capteur));
Capt_Hygr = malloc(sizeof(capteur));

Capt_Pression -> active = 1;
Capt_Lumin -> active = 1;
Capt_Temp -> active = 1;
Capt_Hygr -> active = 1;

Capt_Pression -> min = 850;
Capt_Pression -> max = 1080;
Capt_Lumin -> min = 255;
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
Capt_Pression -> next = NULL;


//volatile
volatile int flag1 = 0;
volatile int flag2 = 0;
volatile int mode = 0;
volatile unsigned long Compteur = 5000;

ChainableLED LED (7,8,1);


#endif