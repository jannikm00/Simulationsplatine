#include <Adafruit_NeoPixel.h>
#define PIN A3
#define NUMPIXELS 10
Adafruit_NeoPixel led(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
int delayvalue = 100;
bool Anlage_ein = false;
bool sB10 = false;
bool sB11 = false;
bool sB12 = false;
bool sB13 = false;
bool sB14 = false;
bool sB15 = false;
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
int count = 0;
float countfuellstand = 5;
int countlauflicht = 0;

void setup() {
  led.begin();
  Serial.begin(9600);
}
void Grundstellung() {
  delay(1000);
  sB10 = true;
  sB11 = false;
  sB12 = false;
  sB13 = false;
  sB14 = false;
  delay(1000);
  sB15 = true;
  Relais_check();
  count++;
}
void Anlage_ein_check() {
  if (M2 == true) {  //Gebläse -M2 geht an mit anschalten der anlage. M2 check
    Anlage_ein = true;
    M2ok = true;
    if (count == 0) {
      Grundstellung();
    }
  } else {
    Anlage_ein = false;
    M2ok = false;
    for (int i = 0; i < 11; i++) {  //LEDs aus wenn Anlage aus
      led.setPixelColor(i, led.Color(0, 0, 0));
    }
    led.show();
    end();
    Relais_check();
  }
  M1ok = false;
  M3_1ok = false;
  M3_2ok = false;
  M4ok = false;
  E1ok = false;
}

void Programm() {
  if (Anlage_ein == true) {
    sB14 = true;  //B14 betätigen Signal Gebläse ok -->Heizung -E1 an
    Relais_check();
    if (E1 == true) {  //Heizung check
      E1ok = true;
    } else {
      E1ok = false;
    }

    if (E1ok == true) {  //Heizung RGB wird von Blau zu rot (fade)
      for (int i = 0; i < 200; i++) {
        if (countr <= 200 && countb >= 0) {
          led.setPixelColor(9, led.Color(countr, 0, countb));
          led.show();
          delay(10);
          countr++;
          countb--;
        }
      }

      sB13 = true;  //Temperatur erreicht -B13 -->nach betätigen von -S2 --> -M1 geht an Druckaufbau
      Relais_check();
    } else {
      sB13 = false;
      led.setPixelColor(9, led.Color(0, 0, 255));  //-E1 aus --> Heizung blau
      led.show();
      countr = 0;
      countb = 200;
    }

    if (M1 == true) {  //M1 check
      M1ok = true;
      if (sB12 == false) {
        delay(1000);
      }
      sB12 = true;  //Druck erreicht -B12 --> Ventil -M4 geht an
      Relais_check();
    } else {
      sB12 = false;
      M1ok = false;
    }


    if (M4 == true) {  //M4 check
      M4ok = true;
    } else {
      M4ok = false;
    }
    if (M3 == true) {  //Nach betätigen von -S3 --> Laufband -M3 geht an
      M3_1ok = true;
      //Niedriger Füllstand -B15 betätigen --> -M3 aus siehe void laufband
    } else {
      M3_1ok = false;
    }
  }
}

void Relais_check() {  //Übersetzung Schalter B10 --> Relais Q1
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
  Serial.write("M1=");
  Serial.print(M1ok);
  Serial.write("|M2=");
  Serial.print(M2ok);
  Serial.write("|!M3=");
  Serial.print(M3_2ok);
  Serial.write("|M4=");
  Serial.print(M4ok);
  Serial.write("|E1=");
  Serial.println(E1ok);
  if (countfuellstand == 0) {
    Serial.print("Prozessabfolge erfolgreich abgeschlossen!           ");
  } else {
    Serial.print("Prozessabfolge abgeschlossen!             ");
  }
}
void lauflichtm3() {  //Laufbandanimation -M3
  if (M3_1ok == true) {
    if (countlauflicht <=4) {
      for (int i = 0; i < 5; i++) {
        led.setPixelColor(i, led.Color(255, 255, 255));
        led.show();
        delay(100);
        led.setPixelColor(i, led.Color(0, 0, 0));
        led.show();
        delay(100);
            if (countfuellstand > 5) {
              countfuellstand=countfuellstand- 0.2;
            }
        pegelupdate();
      }
          countlauflicht++;
    }

  } else {
    countlauflicht = 0;
  }
}


void fuellstandm4() {
  if (M4ok == true) {
    if (countfuellstand <= 8) {
      led.setPixelColor(countfuellstand, led.Color(255, 255, 255));
      led.show();
      countfuellstand++;
      delay(50);
      if (countfuellstand >= 7) {
        sB11 = true;  //Füllstand hoch
        sB15 = false;
        Relais_check();
      } else if (countfuellstand <= 6) {
        sB11 = false;  //Füllstand nierdrig
        sB15 = true;
        Relais_check();
      }
    }
  }
}

void end() {
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
    Relais_check();
    Serial.println("Anlage aus");
    Programm();
    count = 0;
  }
}
void pegelupdate() {
  for (int i = 5; i < 9; i++) {
    led.setPixelColor(i, led.Color(0, 0, 0));
  }
  led.show();
  for (int i = 5; i < countfuellstand; i++) {
    led.setPixelColor(i, led.Color(255, 0, 0));
  }
  led.show();
}
void loop() {
  Motor_check();
  Anlage_ein_check();
  if (Anlage_ein == true) {
    Motor_check();
    Programm();
    printstatus();
    fuellstandm4();
    lauflichtm3();
  }
  end();
}
