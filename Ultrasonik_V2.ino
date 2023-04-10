#include <SoftwareSerial.h>
SoftwareSerial mySerial (2, 3);

#include <NewPing.h>
#define RPWM 9
#define LPWM 10
#define PWM 11
#define TRIGGER_PIN 12
#define ECHO_PIN 13
#define MAX_DISTANCE 200

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
int jarak;
int jarakSebelum;
unsigned int uS;
char data;


int jarakKendaraanKecil = 15;
int jarakKendaraanSedang = 17;
int jarakKendaraanBesar = 19;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(RPWM, OUTPUT);
  pinMode(PWM, OUTPUT);
  pinMode(LPWM, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:


  if (Serial.available() > 0) {
    data = Serial.read();
  }

  uS = sonar.ping();
  jarak = uS / US_ROUNDTRIP_CM;

  // Smoothing pembacaan ultrasonik
  if (jarak == 0 or jarak == 1149) {
    jarak = jarakSebelum;
  }
  else {
    jarak = jarak;
    jarakSebelum = jarak;
  }

  printJarak();


  // Decision Making
  if (data == '1') {
    digitalWrite(RPWM, HIGH);
    digitalWrite(LPWM, LOW);
    analogWrite(PWM, 500);

    // Pembatasan Maksimal
    if (jarak >= 19) {
      digitalWrite(RPWM, LOW);
      digitalWrite(LPWM, LOW);
      analogWrite(PWM, 0);
    }
  }
  else if (data == '2') {
    digitalWrite(RPWM, LOW);
    digitalWrite(LPWM, HIGH);
    analogWrite(PWM, 500);

    // Pembatasan Minimal
    if (jarak <= 5) {
      digitalWrite(RPWM, LOW);
      digitalWrite(LPWM, LOW);
      analogWrite(PWM, 0);
    }
  }
  else if (data == '3') {
    digitalWrite(RPWM, LOW);
    digitalWrite(LPWM, LOW);
    analogWrite(PWM, 0);
  }
  else if (data == '4') {
    if (jarak < jarakKendaraanKecil) {
      digitalWrite(RPWM, HIGH);
      digitalWrite(LPWM, LOW);
      analogWrite(PWM, 500);
    }
    else if (jarak > jarakKendaraanKecil) {
      digitalWrite(RPWM, LOW);
      digitalWrite(LPWM, HIGH);
      analogWrite(PWM, 500);
    }
    else if (jarak == jarakKendaraanKecil) {
      digitalWrite(RPWM, LOW);
      digitalWrite(LPWM, LOW);
      analogWrite(PWM, 0);
    }
  }

  else if (data == '5') {
    if (jarak < jarakKendaraanSedang) {
      digitalWrite(RPWM, HIGH);
      digitalWrite(LPWM, LOW);
      analogWrite(PWM, 500);
    }
    else if (jarak > jarakKendaraanSedang) {
      digitalWrite(RPWM, LOW);
      digitalWrite(LPWM, HIGH);
      analogWrite(PWM, 500);
    }
    else if (jarak == jarakKendaraanSedang) {
      digitalWrite(RPWM, LOW);
      digitalWrite(LPWM, LOW);
      analogWrite(PWM, 0);
    }
  }
  else if (data == '6') {
    if (jarak < jarakKendaraanBesar) {
      digitalWrite(RPWM, HIGH);
      digitalWrite(LPWM, LOW);
      analogWrite(PWM, 500);
    }
    else if (jarak > jarakKendaraanBesar) {
      digitalWrite(RPWM, LOW);
      digitalWrite(LPWM, HIGH);
      analogWrite(PWM, 500);
    }
    else if (jarak == jarakKendaraanBesar) {
      digitalWrite(RPWM, LOW);
      digitalWrite(LPWM, LOW);
      analogWrite(PWM, 0);
    }
  }
}



void printJarak() {
  Serial.print("Ketinggian: ");
  Serial.print(jarak);
  Serial.println("cm");
}
