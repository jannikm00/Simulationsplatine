#include <Adafruit_NeoPixel.h>
#define PIN A3
#define NUMPIXELS 5
Adafruit_NeoPixel led(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
bool Anlage_ein = false;
bool sB10 = false;
bool sB11 = false;
bool sB12 = false;
bool sB13 = false;
bool sB14 = false;
bool sB15 = true;
bool M1 = false;
bool M2 = false;
bool M3 = false;
bool M4 = false;
bool E1 = false;
bool M1ok;
bool M2ok;
bool M3_1ok;
bool M3_2ok;
bool M4ok;
bool E1ok;
bool Anlageok;
int Q1 = 2;    //B10
int Q2 = 3;    //B11
int Q3 = 4;    //B12
int Q4 = 5;    //B13
int Q5 = 6;    //B14
int Q6 = 7;    //B15
int P10 = 12;  // -E1 input
int P11 = 8;   // -M1 input
int P12 = 9;   // -M2 input
int P14 = 10;  // -M4 input
int P15 = 11;  // -M3 input
int countr = 0;
int countb = 200;
void setup() {
  led.begin();
  Serial.begin(9600);
}

void Anlage_ein_check() {
  if (M2 == true) {  //Gebläse -M2 geht an mit anschalten der anlage. M2 check
    Anlage_ein = true;
    M2ok = true;
  } else {
    Anlage_ein = false;
    M2ok = false;
    for (int i = 0; i < 5; i++) {  //LEDs aus wenn Anlage aus
      led.setPixelColor(i, led.Color(0, 0, 0));
    }
    led.show();
  }
  M1ok = false;
  M3_1ok = false;
  M3_2ok = false;
  M4ok = false;
  E1ok = false;
}

void Programm() {

  sB14 = true;  //B14 betätigen Signal Gebläse ok -->Heizung -E1 an

  if (E1 == true) {  //Heizung check
    E1ok = true;
  } else {
    E1ok = false;
  }

  if (E1ok == true) {  //Heizung RGB
    for (int i = 0; i < 200; i++) {
      if (countr <= 200 && countb >= 0) {
        led.setPixelColor(4, led.Color(countr, 0, countb));
        led.show();
        delay(10);
        countr++;
        countb--;
      }
    }
  } else {
    led.setPixelColor(4, led.Color(0, 0, 255));
    led.show();
    countr = 0;
    countb = 200;
  }


  sB13 = true;       //Temperatur erreicht -B13 -->nach betätigen von -S2 --> -M1 geht an Druckaufbau
  if (M1 == true) {  //M1 check
    M1ok = true;
  } else {
    M1ok = false;
  }

  sB12 = true;       //Druck erreicht -B12 --> Ventil -M4 geht an
  if (M4 == true) {  //M4 check
    M4ok = true;
  } else {
    M4ok = false;
  }
  if (M3 == true) {  //Nach betätigen von -S3 --> Laufband -M3 geht an
    M3_1ok = true;
  } else {
    M3_1ok = false;
  }

  sB15 = true;        //Niedriger Füllstand -B15 betätigen --> -M3 aus
  if (M3 == false) {  //M3 check
    M3_2ok = true;
  } else {
    M3_2ok = false;
  }
}

void Relais_check() {  //Übersetzung Schalter B10 --> Relais Q1
  if (sB10 == false) {
    digitalWrite(Q1, LOW);
  } else {
    digitalWrite(Q1, HIGH);
  }

  if (sB11 == false) {
    digitalWrite(Q2, LOW);
  } else {
    digitalWrite(Q2, HIGH);
  }

  if (sB12 == false) {
    digitalWrite(Q3, LOW);
  } else {
    digitalWrite(Q3, HIGH);
  }

  if (sB13 == false) {
    digitalWrite(Q4, LOW);
  } else {
    digitalWrite(Q4, HIGH);
  }

  if (sB14 == false) {
    digitalWrite(Q5, LOW);
  } else {
    digitalWrite(Q5, HIGH);
  }

  if (sB15 == false) {
    digitalWrite(Q6, LOW);
  } else {
    digitalWrite(Q6, HIGH);
  }
}

void Motor_check() {  //Übersetzung LEDs auf Platine -P10 --> -E1

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
void printstatus() {
  Serial.write("M1");
  Serial.print(M1ok, DEC);
  Serial.write("M2");
  Serial.print(M2ok);
  Serial.write("M4");
  Serial.print(M4ok);
  Serial.write("E1");
  Serial.println(E1ok);
  if (M1ok == true && M2ok == true && M3_2ok == true && M4ok == true && E1ok == true) {
    Serial.print("Prozessabfolge erfolgreich abgeschlossen!       ");
  } else {
    Serial.print("Prozessabfolge fehlerhaft abgeschlossen!        ");
  }
}
void lauflichtm3() {  //Laufbandanimation -M3
  if (M3_1ok == true) {
    for (int i = 0; i < 4; i++) {
      led.setPixelColor(i, led.Color(255, 255, 255));
      led.show();
      delay(50);
    }
    for (int i = 0; i < 4; i++) {
      led.setPixelColor(i, led.Color(0, 0, 0));
      led.show();
      delay(50);
    }
  }
}
void loop() {

  Motor_check();
  Anlage_ein_check();
  Relais_check();
  if (Anlage_ein == true) {
    Programm();
  }
  printstatus();
  lauflichtm3();
}
