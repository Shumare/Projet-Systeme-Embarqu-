


#ifndef Variable_H_INCLUDED
#define Variable_H_INCLUDED

#include "Arduino.h"
#include "string.h"

const int Bouton1 = 3; //Bouton rouge
const int Bouton2 = 2; //Bouton vert

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
capteur Capt_GPS;

//volatile
volatile int flag1;
volatile int flag2;
volatile int mode;


#endif