#include <stdio.h>
#include <stdlib.h>
void enterNewParam(){
    char capteurModif;
    float valeurModif;
    printf("\nVeillez entrer le capteur qui doit etre modifié: ");
    scanf("%c", capteurModif);
    printf("\nVeillez entrer la nouvelle valeur : ");
    scanf("%f", valeurModif);  
}