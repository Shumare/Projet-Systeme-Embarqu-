#ifndef Fonction_H_INCLUDED
#define Fonction_H_INCLUDED
#include "Variable.h"

//void enterNewParam();
//void checkParam(char capteurModif,float valeurModif);
//void modifParam(char capteurModif,float valeurModif);
//float demandeDonnee(int port);

String getTime();
void enterNewParam();
void checkParam(char capteurModif, float valeurModif);
void configEEPROM();
void resetEEPROM();
void stockSD(String saveSd);
String demandeDonnee(capteur *Capt_Hygr);
void desactiveCapteur();
void reactiveCapteur();
    
#endif