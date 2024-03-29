/*
Simulations-Platine der AP Teil 1 Frühjahr 2022 Elektroniker für Betriebstechnik

WICHTIG:
Niemals mit angeschlossener 9V Batterie den Arduino mit einem PC verbinden
Nicht Widerstände kurzschließen

Pulldown Widerstände:
Spannungsteiler mit R1 = 10kOhm, R2 = 2,6kOhm

Bypass:
Bypass Pin (A5) auf High bringen (Schalter umlegen)
in void Bypass () gewünschte Sensorstellung, delay und was auch immer eingeben
Das Programm wird nichts machen, nur void Bypass () wird laufen
Will man nach Bypass Modus das normale Programm verwenden muss man Reset auf dem Arduino drücken
und die -S1 an und wieder aus machen

Programmablauf:
-S1 betätigen
Warten bis Heizung -E1 auf Temperatur
-S2 betätigen
Warten bis -M1 genug Druck aufgebaut hat
Warten bis der Sprühturm gefüllt ist -Ventil -M4 offen
-S3 betätigen
Warten bis der Sprühturm leer ist Förderschnecke -M3 Rechtslauf
(Optional: -S4 betätigen Förderschnecke -M3 Linkslauf)

Programmablauf ende:
Ist der Sprühturm entleert worden ist der Milchvorrat aufgebraucht, um ihn wieder zu befüllen 
muss man -S1 an und wieder aus machen oder den Reset Knopf auf dem Arduino betätigen
*/


#include <Adafruit_NeoPixel.h>
#define PIN A3
#define NUMPIXELS 12
Adafruit_NeoPixel led(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
int delayvalue = 100;       //Globaler Delay Wert
int countr = 0;             //RGB Heizung wert Rot
int countb = 200;           //RGB Heizung wert Blau
int count = 0;              //Grundstellung nur einmal ausführen variable
float countfuellstand = 5;  //Position Anfang Füllstand
float countblink = 0;       //Variable Niedriger Füllstand Blinken
int countlauflicht = 0;     //Anzahl Durchläufe Lauflicht
int ventilgruen = 5;        //Dauer bis Ventil Druck hat
float countventil = 0;      //Variable Ventil Druck vorhanden
bool Programmbypass;        //Programm überspringen Sensorstellung in void Bypass () festlegen
float countvorrat = 0;      //Variable Milchvorrat

///Programm Variablen///
bool Anlage_ein = false;
///Simulierte Sensoren Werte, in void Grundstellung () verändern
bool sB10 = false;  //Simulierter Sensor
bool sB11 = false;  //"
bool sB12 = false;  //"
bool sB13 = false;  //"
bool sB14 = false;  //"
bool sB15 = false;  //"
bool sB16 = false;  //"

///Abgefragte Motoren Status Variablen
bool M1 = false;   //Motoren Abfrage Variable NICHT VERÄNDERN!
bool M2 = false;   //"
bool M3 = false;   //"
bool M3L = false;  //"
bool M4 = false;   //"
bool E1 = false;   //"

///Serielle Debugging Variablen///
bool M1ok;
bool M2ok;
bool M3ok;
bool M3Lok;
bool M4ok;
bool E1ok;
bool Anlageok;

///Output Pins
int K3_1 = 2;    // -B10 Output (NO)
int K3_2 = 3;    // -B11 Output (NO)
int K3_3 = 4;    // -B12 Output (NO)
int K3_4 = 5;    // -B13 Output (NO)
int K3_5 = 6;    // -B14 Output (NO)
int K3_6 = 7;    // -B15 Output (NO)
int K3_7 = A1;   // -B16 Output (NC)
int SimM1 = A2;  // -M1 Simulierter Motor Output
int SimM2 = A0;  // -M2 Simulierter Motor Output

//Input Pins
int P10 = 12;     // -E1 Input
int P11 = 8;      // -M1 Input
int P12 = 9;      // -M2 Input
int P13 = A4;     // -M3 Input Linkslauf
int P14 = 10;     // -M4 Input
int P15 = 11;     // -M3 Input
int bypass = A5;  //Bypass schalter





void setup() {
  led.begin();
  Serial.begin(9600);
}





void Grundstellung() {  //Grundstellung Simulierte Sensoren
  sB10 = true;          //Milch vorhanden
  sB11 = false;         //Füllstand hoch
  sB12 = false;         //Druck vorhanden
  sB13 = false;         //Temperatur ok
  sB14 = false;         //Gebläse ok
  sB15 = false;         //Füllstand niedrig
  sB16 = false;         //CO-Meldung
  Relais_check();
  count++;
  pegelupdate();  //Füllstand Pegel Update
}





void Bypass() {  //Programm überspringen wenn Programmbypass true ist
  analogWrite(SimM1, 1023);
  analogWrite(SimM2, 1023);
  sB10 = true;   //Milch vorhanden
  sB11 = false;  //Füllstand hoch
  sB12 = false;  //Druck vorhanden
  sB13 = false;  //Temperatur ok
  sB14 = false;  //Gebläse ok
  sB15 = false;  //Füllstand niedrig
  sB16 = false;  //CO-Meldung
  Relais_check();
  delay(delayvalue);
  sB10 = false;  //Milch vorhanden
  sB11 = true;   //Füllstand hoch
  sB12 = false;  //Druck vorhanden
  sB13 = false;  //Temperatur ok
  sB14 = false;  //Gebläse ok
  sB15 = false;  //Füllstand niedrig
  sB16 = false;  //CO-Meldung
  Relais_check();
  delay(delayvalue);
  sB10 = false;  //Milch vorhanden
  sB11 = false;  //Füllstand hoch
  sB12 = true;   //Druck vorhanden
  sB13 = false;  //Temperatur ok
  sB14 = false;  //Gebläse ok
  sB15 = false;  //Füllstand niedrig
  sB16 = false;  //CO-Meldung
  Relais_check();
  delay(delayvalue);
  sB10 = false;  //Milch vorhanden
  sB11 = false;  //Füllstand hoch
  sB12 = false;  //Druck vorhanden
  sB13 = true;   //Temperatur ok
  sB14 = false;  //Gebläse ok
  sB15 = false;  //Füllstand niedrig
  sB16 = false;  //CO-Meldung
  Relais_check();
  delay(delayvalue);
  sB10 = false;  //Milch vorhanden
  sB11 = false;  //Füllstand hoch
  sB12 = false;  //Druck vorhanden
  sB13 = false;  //Temperatur ok
  sB14 = true;   //Gebläse ok
  sB15 = false;  //Füllstand niedrig
  sB16 = false;  //CO-Meldung
  Relais_check();
  delay(delayvalue);
  sB10 = false;  //Milch vorhanden
  sB11 = false;  //Füllstand hoch
  sB12 = false;  //Druck vorhanden
  sB13 = false;  //Temperatur ok
  sB14 = false;  //Gebläse ok
  sB15 = true;   //Füllstand niedrig
  sB16 = false;  //CO-Meldung
  Relais_check();
  delay(delayvalue);
  sB10 = false;  //Milch vorhanden
  sB11 = false;  //Füllstand hoch
  sB12 = false;  //Druck vorhanden
  sB13 = false;  //Temperatur ok
  sB14 = false;  //Gebläse ok
  sB15 = false;  //Füllstand niedrig
  sB16 = true;   //CO-Meldung
  Relais_check();
  delay(delayvalue);
  sB10 = true;  //Milch vorhanden
  sB11 = true;  //Füllstand hoch
  sB12 = true;  //Druck vorhanden
  sB13 = true;  //Temperatur ok
  sB14 = true;  //Gebläse ok
  sB15 = true;  //Füllstand niedrig
  sB16 = true;  //CO-Meldung
  Relais_check();
  for (int i = 0; i <= 11; i++) {
    led.setPixelColor(i, led.Color(255, 0, 0));
    led.show();
  }
  delay(100);
  for (int i = 0; i <= 11; i++) {
    led.setPixelColor(i, led.Color(0, 255, 0));
    led.show();
  }
  delay(100);
  for (int i = 0; i <= 11; i++) {
    led.setPixelColor(i, led.Color(0, 0, 255));
    led.show();
  }
  delay(100);
  for (int i = 0; i <= 11; i++) {
    led.setPixelColor(i, led.Color(255, 255, 255));
    led.show();
  }
  delay(100);
  Anlage_ein = false;
  Serial.println("B Y P A S S");
}





void Anlage_ein_check() {  //Ist -M2 an --> Simulation starten
  if (M2 == true) {        //Gebläse -M2 geht an mit anschalten der anlage. M2 check
    Anlage_ein = true;
    M2ok = true;
    analogWrite(SimM2, 1023);  //Motor -M2

    if (count == 0) {
      Grundstellung();
    }

  } else {  //Ist -M2 aus --> Simulation zurücksetzen und auf -M2 an warten
    Anlage_ein = false;
    M2ok = false;
    analogWrite(SimM2, 0);  //Motor -M2

    for (int i = 0; i <= 12; i++) {  //LEDs aus wenn Anlage aus
      led.setPixelColor(i, led.Color(0, 0, 0));
    }
    led.show();
    end();
    Relais_check();
  }
  M3ok = false;
  M3Lok = false;
  M4ok = false;
  E1ok = false;
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
    M3L = false;
    M4 = false;
    E1 = false;

    Relais_check();                //Relais zurücksetzen
    Serial.println("Anlage aus");  //Debugging
    Programm();                    //Neustart wenn Anlage_ein == true
    count = 0;                     //void Grundstellung () darf einmal laufen
    countvorrat = 0;               //Milchvorrat wieder voll
    countfuellstand = 5;           //Füllstand auf 0 setzen
    Motor_check();

    if (M1 == true) {  //M1 Simulation
      analogWrite(SimM1, 1023);

    } else {
      analogWrite(SimM1, 0);
    }
  }
}





void Programm() {  //Funktion: Programm bis auf Füllstand hoch und niedrig in void fuellstandm4 ()
  sB14 = true;     //B14 betätigen Signal Gebläse ok -->Heizung -E1 an
  Relais_check();

  if (E1 == true) {  //Debugging
    E1ok = true;

  } else {
    E1ok = false;
  }

  if (E1 == true) {  //Heizung RGB wird von Blau zu rot (fade)

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

  } else if (Anlage_ein == true) {
    sB13 = false;
    led.setPixelColor(11, led.Color(0, 0, 255));  //-E1 aus --> Heizung blau
    led.show();
    countr = 0;
    countb = 200;
  }

  if (M1 == true) {  //M1 check
    M1ok = true;
    analogWrite(SimM1, 1023);

    if (sB12 == false) {

      if (countventil >= 5) {
        sB12 = true;  //Druck erreicht -B12 --> Ventil -M4 geht an
        Relais_check();
      }
    }

  } else {
    //sB12 = false;
    Relais_check();
    M1ok = false;
    analogWrite(SimM1, 0);
  }


  if (M4 == true) {  //Debugging
    M4ok = true;
    /*if (sB10 == true) {
      if (countvorrat >= 5) {
        sB10 = false;  //Milchvorrat leer
      }
    }*/
  }

  if (M3 == true) {  //Debugging Nach betätigen von -S3 --> Laufband -M3 geht an
    M3ok = true;
    //Niedriger Füllstand -B15 betätigen --> -M3 aus siehe void lauflichtm3 ()//
  } else {
    M3ok = false;
  }

  if (M3L == true) {  //Debugging
    M3Lok = true;
  } else {
    M3ok = false;
  }
}





void Relais_check() {  //Funktion: Übersetzung Schalter B10 --> Relais K3_1, aktualisiert Relais
  if (sB10 == false) {
    analogWrite(K3_1, 0);

  } else {
    analogWrite(K3_1, 1023);
  }

  if (sB11 == false) {
    analogWrite(K3_2, 0);

  } else {
    analogWrite(K3_2, 1023);
  }

  if (sB12 == false) {
    analogWrite(K3_3, 0);

  } else {
    analogWrite(K3_3, 1023);
  }

  if (sB13 == false) {
    analogWrite(K3_4, LOW);

  } else {
    analogWrite(K3_4, 1023);
  }

  if (sB14 == false) {
    analogWrite(K3_5, 0);

  } else {
    analogWrite(K3_5, 1023);
  }

  if (sB15 == false) {
    analogWrite(K3_6, 0);

  } else {
    analogWrite(K3_6, 1023);
  }
  if (sB16 == false) {
    analogWrite(K3_7, 0);

  } else {
    analogWrite(K3_7, 1023);
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

  if (digitalRead(A4) == HIGH) {
    M3L = true;
  } else {
    M3L = false;
  }
}





void printstatus() {  //Funktion: Serieller Output für Debugging
 /*Serial.write("M1=");
  Serial.print(M1ok);
  Serial.write("|M2=");
  Serial.print(M2ok);
  Serial.write("|M3=");
  Serial.print(M3ok);
  Serial.write("|M3L=");
  Serial.print(M3Lok);
  Serial.write("|M4=");
  Serial.print(M4ok);
  Serial.write("|E1=");
  Serial.print(E1ok);*/
  Serial.write(" B10(Mvorhanden)=");
  Serial.print(sB10);
  Serial.write(" |B11(Fhoch)=");
  Serial.print(sB11);
  Serial.write(" |B12(Drvorhanden)=");
  Serial.print(sB12);
  Serial.write(" |B13(Tempok)=");
  Serial.print(sB13);
  Serial.write(" |B14(Geblok)=");
  Serial.print(sB14);
  Serial.write(" |B15(Fniedrig)=");
  Serial.print(sB15);
  Serial.write(" |B16(CO)=");
  Serial.print(sB16);
  Serial.print(" |Füllstand:");
  Serial.print(countfuellstand - 5);
  Serial.print(" |Vorrat:");
  Serial.println(5 - countvorrat);
}





void fuellstandm4() {                    //Funktion: Füllstand
  if (M4 == true && countventil >= 4) {  //Ventil -M4 offen --> Füllstand erhöht sich
    led.setPixelColor(4, led.Color(0, 0, 0));
    led.show();

    if (countfuellstand <= 10) {
      led.setPixelColor(countfuellstand, led.Color(255, 255, 255));
      led.show();
      countfuellstand = countfuellstand + 0.10;
      delay(50);

      if (countfuellstand >= 7.5) {  //Abfüllvorgang startbar machen Füllstand hoch B11 und B15 überschritten
        sB11 = true;
        Relais_check();
        sB15 = true;
        Relais_check();
        if (countfuellstand > 9.1) {
          countfuellstand = 10;
        }

      } else if (countfuellstand <= 5) {  //Abfüllvorgang stoppen Füllstand sB15 und sB11 unterschritten
        sB11 = false;
        Relais_check();
        sB15 = false;  //"
        Relais_check();
      }
    }
  }
}






void lauflichtm3() {  //Funktion: Förderschnecke Animation -M3
  if (M3 == true) {
    countventil = 0;

    for (int i = 0; i < 5; i++) {
      led.setPixelColor(i, led.Color(255, 255, 255));
      led.show();
      delay(100);
      led.setPixelColor(i, led.Color(0, 0, 0));
      led.show();
      delay(100);

      if (countfuellstand > 5) {
        countfuellstand = countfuellstand - 0.10;  //0.2 = Schnelligkeit Entleerung
      }
      pegelupdate();

      if (countfuellstand >= 7.5) {  //Abfüllvorgang startbar machen Füllstand hoch B11 und B15 überschritten
        sB11 = true;
        Relais_check();
        sB15 = true;
        Relais_check();

      } else if (countfuellstand <= 5.5) {  //Abfüllvorgang stoppen Füllstand sB15 und sB11 unterschritten
        sB15 = false;                       //Füllstand niedrig aus
        Relais_check();
      }

      if (countfuellstand < 7) {  //-P2 aus???
        sB11 = false;             //Füllstand hoch aus
        Relais_check();
      }
    }
  }
}





void ventilm1() {  //Funktion: Druckaufbau bei M1 an
  if (M1 == true) {

    if (countventil < 5) {
      countventil = countventil + 0.2;
    }
    /*Serial.write("Ventil:");
    Serial.print(countventil);*/
    if (countventil > ventilgruen) {  //Genug Druck --> LED Grün, B12 an
      led.setPixelColor(10, led.Color(0, 255, 0));
      led.show();
      sB12 = true;
      Relais_check();
    }

  } else {
    led.setPixelColor(10, led.Color(255, 0, 0));  //Zu wenig Druck --> LED Rot
    led.show();
    //sB12 = false;
    Relais_check();
  }
}





void vorrat() {  //Funktion: Milchvorrat senken bei M4 an
  if (M4 == true && countventil >= 5) {
    if (countvorrat < 5) {
      countvorrat = countvorrat + 0.12;
    }
  }

  if (countvorrat > 4.80) {
    sB10 = false;
    Relais_check();
    countvorrat = 5;

  } else {
    sB10 = true;
    Relais_check();
  }
}





void blink() {  //Funktion: Blinken bei Füllstand unter 2
  if (M4 == false) {

    if (countfuellstand <= 6) {
      led.setPixelColor(5, led.Color(255, 0, 0));
      led.show();
      countblink = countblink + 0.10;

      if (countblink > 0.5) {
        led.setPixelColor(5, led.Color(0, 0, 0));
        led.show();
        countblink = 0;
      }
    }
  }
}





void lauflichtm3L() {  //Funktion: -M3 Linkslauf animation
  if (M3L == true) {

    for (int i = 4; i >= 0; i--) {
      led.setPixelColor(i, led.Color(255, 255, 255));
      led.show();
      delay(50);
      led.setPixelColor(i, led.Color(0, 0, 0));
      led.show();
      delay(50);
    }
  }
}





void loop() {
  if (analogRead(A5) > 900) {  //Bypass Schalter
    Programmbypass = true;
  } else {
    Programmbypass = false;
  }
  if (Programmbypass == false) {
    Motor_check();       //Motoren Abfrage für Anlage_ein
    Anlage_ein_check();  //Check ob -M2 an ist
    if (Anlage_ein == true) {
      Motor_check();   //Motorenabfrage für Hauptprogramm
      Programm();      //Hauptprogramm
      printstatus();   //Debugging
      fuellstandm4();  //Füllstand Animation
      lauflichtm3();   //Förderschnecke Animation
      lauflichtm3L();  //Förderschnecke Animation Linkslauf
      ventilm1();      // -M4 Druck LED
      blink();         //Füllstand blinken
      vorrat();        //Milchvorrat

    } else {
      end();  //Reset
    }

  } else if (Programmbypass == true) {  //Bypass Programm
    Bypass();
  }
}
