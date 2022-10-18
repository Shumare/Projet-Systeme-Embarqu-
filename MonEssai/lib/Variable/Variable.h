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



capteur *Capt_Pression = (capteur*)malloc(sizeof(capteur));
capteur *Capt_Lumin = (capteur*)malloc(sizeof(capteur));
capteur *Capt_Temp = (capteur*)malloc(sizeof(capteur));
capteur *Capt_Hygr = (capteur*)malloc(sizeof(capteur));

int TIME_OUT = 30000;
long int LOG_INTERVAL = 600000;
int FILE_MAX_SIZE = 4096;



//volatile
volatile int flag1 = 0;
volatile int flag2 = 0;
volatile int mode = 0;
volatile unsigned long Compteur = 5000;

ChainableLED LED (7,8,1);


#endif