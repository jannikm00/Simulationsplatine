#include <Adafruit_NeoPixel.h>
#define PIN A3
#define NUMPIXELS 12
Adafruit_NeoPixel led(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

///Anpassbare Werte///
int delayvalue = 100;       //Globaler Delay Wert
int countr = 0;             //RGB Heizung wert Rot
int countb = 200;           //RGB Heizung wert Blau
int count = 0;              //Grundstellung nur einmal ausführen variable
float countfuellstand = 5;  //Position Anfang Füllstand
float countblink = 0;       //Variable Niedriger Füllstand Blinken
int countlauflicht = 0;     //Anzahl Durchläufe Lauflicht
int ventilgruen = 5;        //Dauer bis Ventil Druck hat
float countventil = 0;      //Variable Ventil Druck vorhanden

///Programm Variablen///
bool Anlage_ein = false;
///Simulierte Sensoren Werte, in void Grundstellung () verändern
bool sB10 = false;  //Simulierter Sensor
bool sB11 = false;  //"
bool sB12 = false;  //"
bool sB13 = false;  //"
bool sB14 = false;  //"
bool sB15 = false;  //"
///Abgefragte Motoren Status Variablen
bool M1 = false;  //Motoren Abfrage Variable NICHT VERÄNDERN!
bool M2 = false;  //"
bool M3 = false;  //"
bool M4 = false;  //"
bool E1 = false;  //"

///Serielle Debugging Variablen///
bool M1ok;
bool M2ok;
bool M3ok;
bool M4ok;
bool E1ok;
bool Anlageok;

///Relais Output Pins
int Q1 = 2;  // -B10 Output
int Q2 = 3;  // -B11 Output
int Q3 = 4;  // -B12 Output
int Q4 = 5;  // -B13 Output
int Q5 = 6;  // -B14 Output
int Q6 = 7;  // -B15 Output

//Motoren Input Pins
int P10 = 12;  // -E1 Input
int P11 = 8;   // -M1 Input
int P12 = 9;   // -M2 Input
int P14 = 10;  // -M4 Input
int P15 = 11;  // -M3 Input




void setup() {
  led.begin();
  Serial.begin(9600);
}





void Grundstellung() {  //Grundstellung Simulierte Sensoren
  sB10 = true;          //Milch vorhanden
  sB11 = false;
  sB12 = false;
  sB13 = false;
  sB14 = false;
  sB15 = true;
  Relais_check();
  count++;
}





void Anlage_ein_check() {  //Ist -M2 an --> Simulation starten
  if (M2 == true) {        //Gebläse -M2 geht an mit anschalten der anlage. M2 check
    Anlage_ein = true;
    M2ok = true;
    if (count == 0) {
      Grundstellung();
    }
  } else {  //Ist -M2 aus --> Simulation zurücksetzen und auf -M2 an warten
    Anlage_ein = false;
    M2ok = false;
    for (int i = 0; i <= 11; i++) {  //LEDs aus wenn Anlage aus
      led.setPixelColor(i, led.Color(0, 0, 0));
    }
    led.show();
    end();
    Relais_check();
  }
  M1ok = false;
  M3ok = false;
  M4ok = false;
  E1ok = false;
}





void Programm() {  //Funktion: Programm bis auf Füllstand hoch und niedrig in void fuellstandm4 ()

  sB14 = true;  //B14 betätigen Signal Gebläse ok -->Heizung -E1 an
  Relais_check();
  if (E1 == true) {  //Heizung -E1 check
    E1ok = true;     //Debugging
  } else {
    E1ok = false;  //Debugging
  }

  if (E1ok == true) {  //Heizung RGB wird von Blau zu rot (fade)
    for (int i = 0; i < 200; i++) {
      if (countr <= 200 && countb >= 0) {
        led.setPixelColor(11, led.Color(countr, 0, countb));
        led.show();
        delay(10);
        countr++;
        countb--;
      }
    }

    sB13 = true;  //Temperatur erreicht -B13 -->nach betätigen von -S2 --> -M1 geht an Druckaufbau siehe void ventilm1 (), void fuellstandm4 ()
    Relais_check();
  } else {
    sB13 = false;
    led.setPixelColor(11, led.Color(0, 0, 255));  //-E1 aus --> Heizung blau
    led.show();
    countr = 0;
    countb = 200;
  }

  if (M1 == true) {  //M1 check
    M1ok = true;     //Debugging
    if (sB12 == false) {
      delay(1000);  //Delay Druckaufbau
    }
    sB12 = true;  //Druck erreicht -B12 --> Ventil -M4 geht an
    Relais_check();
  } else {
    sB12 = false;
    Relais_check();
    M1ok = false;  //Debugging
  }

  if (M4 == true) {  //M4 check
    M4ok = true;     //Debugging
  } else {
    M4ok = false;  //Debugging
  }

  if (M3 == true) {  //Nach betätigen von -S3 --> Laufband -M3 geht an
    M3ok = true;     //Debugging
                     //Niedriger Füllstand -B15 betätigen --> -M3 aus siehe void lauflichtm3 ()//
  } else {
    M3ok = false;  //Debugging
  }
}





void Relais_check() {  //Funktion: Übersetzung Schalter B10 --> Relais Q1, aktualisiert Relais
  if (sB10 == false) {
    analogWrite(Q1, 0);
  } else {
    analogWrite(Q1, 1023);
  }

  if (sB11 == false) {
    analogWrite(Q2, 0);
  } else {
    analogWrite(Q2, 1023);
  }

  if (sB12 == false) {
    analogWrite(Q3, 0);
  } else {
    analogWrite(Q3, 1023);
  }

  if (sB13 == false) {
    analogWrite(Q4, LOW);
  } else {
    analogWrite(Q4, 1023);
  }

  if (sB14 == false) {
    analogWrite(Q5, 0);
  } else {
    analogWrite(Q5, 1023);
  }

  if (sB15 == false) {
    analogWrite(Q6, 0);
  } else {
    analogWrite(Q6, 1023);
  }
}





void Motor_check() {  //Funktion: Übersetzung LEDs auf Platine -P10 --> -E1 ...usw

  if (digitalRead(P10) == HIGH) {
    E1 = true;
  } else {
    E1 = false;
  }
  if (digitalRead(P11) == HIGH) {
    M1 = true;
  } else {
    M1 = false;
  }
  if (digitalRead(P12) == HIGH) {
    M2 = true;
  } else {
    M2 = false;
  }
  if (digitalRead(P15) == HIGH) {
    M3 = true;
  } else {
    M3 = false;
  }
  if (digitalRead(P14) == HIGH) {
    M4 = true;
  } else {
    M4 = false;
  }
}





void printstatus() {  //Funktion: Serieller Output für Debugging
  Serial.write("M1=");
  Serial.print(M1ok);
  Serial.write("|M2=");
  Serial.print(M2ok);
  Serial.write("|M3=");
  Serial.print(M3ok);
  Serial.write("|M4=");
  Serial.print(M4ok);
  Serial.write("|E1=");
  Serial.println(E1ok);
  if (countfuellstand == 0) {
    Serial.print("Prozessabfolge mit entleertem Füllturm abgeschlossen!           ");
  } else {
    Serial.print("Prozessabfolge abgeschlossen!                                   ");
  }
}





void fuellstandm4() {                      //Funktion: Füllstand
  if (M4ok == true && countventil >= 5) {  //Ventil -M4 offen --> Füllstand erhöht sich
    led.setPixelColor(4, led.Color(0, 0, 0));
    led.show();
    if (countfuellstand <= 10) {
      led.setPixelColor(countfuellstand, led.Color(255, 255, 255));
      led.show();
      countfuellstand = countfuellstand + 0.10;
      delay(50);
      if (countfuellstand >= 8) {
        sB11 = true;   //Füllstand hoch
        sB15 = false;  //"
        Relais_check();
      } else if (countfuellstand <= 6) {
        sB11 = false;  //Füllstand niedrig
        sB15 = true;   //"
        Relais_check();
      }
    }
  }
  Serial.print("  |  Füllstand:");
  Serial.println(countfuellstand - 5);
}





void lauflichtm3() {  //Funktion: Förderschnecke Animation -M3
  if (M3ok == true) {
    if (countlauflicht <= 3) {
      for (int i = 0; i < 5; i++) {
        led.setPixelColor(i, led.Color(255, 255, 255));
        led.show();
        delay(100);
        led.setPixelColor(i, led.Color(0, 0, 0));
        led.show();
        delay(100);
        if (countfuellstand > 5.3) {
          countfuellstand = countfuellstand - 0.30;  //0.2 = Schnelligkeit Entleerung
        }
        pegelupdate();
      }
      countlauflicht++;
    }

  } else {
    countlauflicht = 0;
  }
}





void pegelupdate() {  //Funktion: Füllstand Pegel senken
  for (int i = 5; i < 10; i++) {
    led.setPixelColor(i, led.Color(0, 0, 0));
  }
  led.show();
  for (int i = 5; i < countfuellstand; i++) {
    led.setPixelColor(i, led.Color(255, 255, 255));
  }
  led.show();
}





void ventilm1() {
  if (M1ok == true) {
    if (countventil < 5) {
      countventil = countventil + 0.1;
    }
    if (countventil > ventilgruen) {
      led.setPixelColor(10, led.Color(0, 255, 0));
      led.show();
    }
  } else {
    led.setPixelColor(10, led.Color(255, 0, 0));
    led.show();
    countventil = 0;
  }
  Serial.write("Ventil:");
  Serial.print(countventil);
}





void blink() {  //Funktion: Blinken bei Füllstand unter 2
  if (countfuellstand <= 5.5) {
    led.setPixelColor(5, led.Color(255, 0, 0));
    led.show();
    countblink = countblink + 0.10;
    if (countblink > 1) {
      led.setPixelColor(5, led.Color(0, 0, 0));
      led.show();
      countblink = 0;
    }
  }
}





void end() {  //Funktion: Reset bei Anlage aus
  if (Anlage_ein == false) {
    sB10 = false;
    sB11 = false;
    sB12 = false;
    sB13 = false;
    sB14 = false;
    sB15 = false;
    M1 = false;
    M2 = false;
    M3 = false;
    M4 = false;
    E1 = false;
    Relais_check();                //Relais zurücksetzen
    Serial.println("Anlage aus");  //Debugging
    Programm();                    //Neustart wenn Anlage_ein == true
    count = 0;                     //void Grundstellung () darf einmal laufen
  }
}





void loop() {
  Motor_check();       //Motoren Abfrage für Anlage_ein
  Anlage_ein_check();  //Check ob -M2 an ist
  if (Anlage_ein == true) {
    Motor_check();  //Motorenabfrage für Hauptprogramm
    Programm();     //Hauptprogramm
    //printstatus();   //Debugging
    fuellstandm4();  //Füllstand Animation
    lauflichtm3();   //Förderschnecke Animation
    ventilm1();        // -M4 Druck LED
    blink();         //Füllstand blinken
  } else {
    end();
  }  //Reset
}
