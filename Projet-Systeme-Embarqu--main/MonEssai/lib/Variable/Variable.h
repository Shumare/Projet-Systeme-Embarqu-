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
// Constantes du programme
#define adresseI2CduBME280                0x76            // Adresse I2C du BME280 (0x76, dans mon cas, ce qui est souvent la valeur par défaut)
#define pressionAuNiveauDeLaMerEnHpa      1024.90         // (1013.25 hPa en moyenne, valeur "par défaut")
#define delaiRafraichissementAffichage    1500            // Délai de rafraîchissement de l'affichage (en millisecondes)

SoftwareSerial SoftSerial(4, 5);

const int Bouton1 = 3; //Bouton rouge
const int Bouton2 = 2; //Bouton vert

volatile unsigned long Compteur = 5000;

//capteurs
typedef struct capt {
    unsigned short port;
    bool active;
    int min;
    int max;
    int valeurActuelle;
    int valeurParDefaut;
    struct el *next;
} capteur;

capteur Capt_Pression;
capteur Capt_Lumin;
capteur Capt_Temp;
capteur Capt_Hygr;

//volatile
volatile int flag1 = 0;
volatile int flag2 = 0;
volatile int mode = 0;

ChainableLED LED (7,8,1);




#endif