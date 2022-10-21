#include "Fonction.cpp"


ISR(TIMER1_COMPA_vect){
  if((flag1 || flag2) == 1 && mode != 1) {
    if(Compteur) {
      Compteur--;
    }
  }

  if(mode == 1) {
    if(Compteur) {
      Compteur--;
    } else {
      mode = 0;
      LED.setColorRGB(0,0,255, 0);
      //reactiveCapt();
    }
  }

  if (ActiveTimeOut) {
    Compteur--;
  }
}

void init_timer(long uSecs){
  noInterrupts();
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1 = 0;
  OCR1A = ((16e6 / 256L * uSecs) / (1e6) )- 1;
  TCCR1B |= (1 << WGM12);
  TCCR1B |= (1 << CS12);
  TIMSK1 |= (1 << OCIE1A);
  interrupts();
}

void switchMode1(){

  if (flag1 == 1 && mode != 1) {
    flag1 = !digitalRead(Bouton1);
    if (Compteur == 0) {
      if(mode == 2) {
        mode = 0;
        LED.setColorRGB(0,0,255, 0);
      }
      if(mode == 0 || mode == 3) {
        mode = 2;
        LED.setColorRGB(0,255,40,0);
      }
      return;
    }
    mode = 1;
    LED.setColorRGB(0, 255, 255, 0);
    Compteur = 30 * 60;
    return;
  }


  if (flag1 == 0 && mode != 1) {
    flag1 = !digitalRead(Bouton1);
    Compteur = 5;
  }

}

void switchMode2(){
  if (flag2 == 1 && mode != 1) {
    flag2 = !digitalRead(Bouton2);
    if(Compteur == 0) {
      if(mode == 0) {
        mode = 3;
        LED.setColorRGB(0,0,0,255);
      } else if(mode == 3) {
        mode = 0;
        LED.setColorRGB(0,0,255, 0);
      }
    }
    return;
  }

  if (flag2 == 0 && mode != 1) {
    flag2 = !digitalRead(Bouton2);
    Compteur = 5;
  }

}


void init_Interrupt(){
  attachInterrupt(digitalPinToInterrupt(Bouton1),switchMode1,CHANGE);
  attachInterrupt(digitalPinToInterrupt(Bouton2),switchMode2,CHANGE);
}



void Configuration() {
  desactiveCapteur();
  enterNewParam();
}

void Standard(){
    LED.setColorRGB(0,0,50,0);
    Serial.begin(9600);
    String StockageDonneeTempo;
    String Stockage = getTime();
    String DetectionAcces = "non";
    String DetectionInvalide = "non";
    delay(LOG_INTERVAL);
    Serial.println("On demarre");
    StockageDonneeTempo = demandeDonnee(Capt_Temp);
    if (!erreur(Capt_Temp, StockageDonneeTempo.toFloat())) {
        processusErreur(Capt_Temp->name, 1);
    }
    Stockage = Stockage + " " + String(StockageDonneeTempo);
    stockSD(Stockage);
}

void Economique() {
    Serial.begin(9600);
    String StockageDonneeTempo;
    String Stockage = getTime();
    String DetectionAcces = "non";
    String DetectionInvalide = "non";
    delay(LOG_INTERVAL*2);
    Serial.println("On demarre");
    StockageDonneeTempo = demandeDonnee(Capt_Pression);
    if (!erreur(Capt_Pression, StockageDonneeTempo.toFloat())) {
        processusErreur(Capt_Pression->name, 1);
    }
    Stockage = Stockage + " " + String(StockageDonneeTempo);
    stockSD(Stockage);
}

void Maintenance(){
    Serial.begin(9600);
    String StockageDonneeTempo;
    String Stockage = getTime();
    String DetectionAcces = "non";
    String DetectionInvalide = "non";
    delay(LOG_INTERVAL);
    Serial.println("On demarre");
    StockageDonneeTempo = demandeDonnee(Capt_Pression);
    if (!erreur(Capt_Pression, StockageDonneeTempo.toFloat())) {
        processusErreur(Capt_Pression->name, 1);
    }
    Stockage = Stockage + " " + String(StockageDonneeTempo);
    Serial.println(Stockage);
}
void setup(){
  // Initialisation du port série (pour l'envoi d'infos via le moniteur série de l'IDE Arduino)
  Serial.begin(9600);
  LED.init();
  pinMode(Bouton1, INPUT_PULLUP);
  pinMode(Bouton2, INPUT_PULLUP);
  pinMode(4, INPUT);
  pinMode(5, OUTPUT);

  init_timer(1e6);

  init_Interrupt();



  while(!Serial);
  Serial.println(F("Programme de test du BME280"));
  Serial.println(F("==========================="));
  Serial.println();

  // Initialisation du BME280
  Serial.print(F("Initialisation du BME280, à l'adresse [0x"));
  Serial.print(adresseI2CduBME280, HEX);
  Serial.println(F("]"));
  
  if(!bme.begin(adresseI2CduBME280)) {
    Serial.println(F("--> ÉCHEC…"));
  } else {
    Serial.println(F("--> RÉUSSIE !"));
  }
  Serial.println();
  

  SoftSerial.begin(9600);

  //Initialize Clock
  clock.begin();
  demarrage();
  
}

/*
void Maintenance() {
  String StockageDonneTempo;
  capteur *inter = (capteur *)malloc(sizeof(capteur));
  inter = Capt_Pression;
  while (inter != NULL) {
    StockageDonneTempo = demandeDonnee(inter);
    if (erreur(inter, StockageDonneTempo)) {
      Serial.println(StockageDonneTempo);
    }
    inter = inter->next;
  }
}
*/

/*
void appelMode() {
  if (mode == 0) {
    Standard();
  } else if (mode == 1) {
    Configuration();
  } else if (mode == 2) {
    Maintenance(LOG_INTERVAL);
  } else if (mode == 3) {
    Economique();
  }
}*/

void loop(){

  /*
    // appelMode();

    String dataString = getTime() + " ; ";
    Serial.println(dataString);
    // Affichage de la TEMPÉRATURE
    Serial.print(F("Température = "));
    Serial.print(bme.readTemperature());
    Serial.println(F(" °C"));

    // Affichage du TAUX D'HUMIDITÉ
    Serial.print(F("Humidité = "));
    Serial.print(bme.readHumidity());
    Serial.println(F(" %"));

    // Affichage de la PRESSION ATMOSPHÉRIQUE
    Serial.print(F("Pression atmosphérique = "));
    Serial.print(bme.readPressure() / 100.0F);
    Serial.println(F(" hPa"));

    // Affichage de l'estimation d'ALTITUDE
    Serial.print(F("Altitude estimée = "));
    Serial.print(bme.readAltitude(pressionAuNiveauDeLaMerEnHpa));
    Serial.println(F(" m"));

      // GPS Reading
    String gpsData = "";
    if (SoftSerial.available())
    {
        bool t=true;
        while(t){
          gpsData = SoftSerial.readStringUntil('\n');
          if (gpsData.startsWith("$GPGGA",0)){
            t=false;
          }
        }
    }
    Serial.println(gpsData);


  // ... et on répète ce cycle à l'infini !
  delay(delaiRafraichissementAffichage);                // Avec x secondes
  d'attente, avant chaque rebouclage Serial.println();
*/
}



