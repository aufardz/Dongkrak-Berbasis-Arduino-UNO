#include <NewPing.h>
#define RPWM 9
#define LPWM 10
#define PWM 11
#define TRIGGER_PIN 12
#define ECHO_PIN 13
#define MAX_DISTANCE 200

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

void setup()
{
    Serial.begin(9600);
    Serial.println("START");
    pinMode(RPWM, OUTPUT);
    pinMode(PWM, OUTPUT);
    pinMode(LPWM, OUTPUT);
}

void loop()
{
    if (Serial.available() > 0)
    {
        char data = Serial.read();
        unsigned int uS = sonar.ping();
        int jarak = uS / US_ROUNDTRIP_CM;
        if (data == 1)
            digitalWrite(RPWM, LOW);
        digitalWrite(LPWM, HIGH);
        analogWrite(PWM, 500);
        if (data == 2)
            digitalWrite(RPWM, HIGH);
        digitalWrite(LPWM, LOW);
        analogWrite(PWM, 500);
        if (data == 3)
            digitalWrite(RPWM, LOW);
        digitalWrite(LPWM, LOW);
        analogWrite(PWM, 0);
        if (data == 4)
            digitalWrite(RPWM, LOW);
        digitalWrite(LPWM, HIGH);
        analogWrite(PWM, 500);
        if (jarak == 15)
            digitalWrite(RPWM, LOW);
        digitalWrite(LPWM, LOW);
        analogWrite(PWM, 0);
        if (data == 5)
            digitalWrite(RPWM, LOW);
        digitalWrite(LPWM, HIGH);
        analogWrite(PWM, 500);
        if (jarak == 25)
            digitalWrite(RPWM, LOW);
        digitalWrite(LPWM, LOW);
        analogWrite(PWM, 0);
        if (data == 6)
            digitalWrite(RPWM, LOW);
        digitalWrite(LPWM, HIGH);
        analogWrite(PWM, 500);
        if (jarak == 35)
            digitalWrite(RPWM, LOW);
        digitalWrite(LPWM, LOW);
        analogWrite(PWM, 0);
        delay(1000);
        Serial.print("Jarak: ");
        Serial.print(jarak);
        Serial.println("cm");
    }
}
