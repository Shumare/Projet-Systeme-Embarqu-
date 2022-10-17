#include "Variable.h"
#include <Adafruit_BME280.h>                            // Inclusion de la librairie BME280 d'Adafruit

// Instanciation de la librairie BME280
Adafruit_BME280 bme;
DS1307 clock;

ISR(TIMER1_COMPA_vect) {
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
}

void init_timer(long uSecs) {
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

void switchMode1() {
  if(flag1 == 1 && flag2==0) {
    flag1 = 0;
    flag2 = 0;
    if(Compteur == 0) {
      if(mode == (0 || 3)) {
        mode = 2;
        LED.setColorRGB(0,255,165,0);
      } else if(mode == 2) {
        mode = 0;
        LED.setColorRGB(0,0,255,0);
      }
    }
    return;
  }

  if (flag1 == 1 && flag2 == 0) {
    mode = 1;
    LED.setColorRGB(0,255,255,0);
    Compteur = 30 * 1e6 * 60;
    return;
  }


  if(flag1 == 0){
    Compteur = 5000;
    flag1 = 1;
    flag2 = 0;
  }

}

void switchMode2() {

  if(flag2 == 1 && flag1 == 0) {
    flag2 = 0;
    flag1 = 0;
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

  if(flag2 == 0) {
    Compteur = 5000;
    flag2 = 1;
    flag1 = 0;
  }

}


void init_Interrupt() {
  attachInterrupt(digitalPinToInterrupt(Bouton1),switchMode1,CHANGE);
  attachInterrupt(digitalPinToInterrupt(Bouton2),switchMode2,CHANGE);
}

String getTime()
{
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


void setup() {
  // Initialisation du port série (pour l'envoi d'infos via le moniteur série de l'IDE Arduino)
  Serial.begin(9600);
  while(!Serial);
  Serial.println("Programme de test du BME280");
  Serial.println("===========================");
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
  pinMode(4, INPUT);
  pinMode(5, OUTPUT);

  SoftSerial.begin(9600);

  //Initialize Clock
  clock.begin();
}

/*
void appelMode() {
  if (mode == 0) {
    Standard();
  } else if (mode == 1) {
    Configuration();
  } else if (mode == 2) {
    Maintenance();
  } else if (mode == 3) {
    Economique();
  }
}*/

void loop() {
  /*
  delay(1000);
  Serial.println(Compteur);
  Serial.println(mode);

  appelMode();
*/
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
  if (SoftSerial.available())                     // if data is coming from software serial port ==> data is coming from SoftSerial GPS
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
  delay(delaiRafraichissementAffichage);                // Avec x secondes d'attente, avant chaque rebouclage
  Serial.println(); 

}

