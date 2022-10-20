#ifndef Fonction_H_INCLUDED
#define Fonction_H_INCLUDED
#include "Variable.h"



String getTime();
void Standard();
void demarrage();
void voirEEPROM();
void resetEEPROM();
void initCapteur();
void configEEPROM();
void stockVariable();
void setupMaxMin();
void voirMinMax();
void stockSD(String saveSd);
void desactiveCapteur();
void reactiveCapteur();
String demandeDonnee(capteur *Capt_Hygr);
void enterNewParam();
void checkParam(String capteurModif, float valeurModif);



#endif