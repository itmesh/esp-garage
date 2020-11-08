#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#include "credentials.h"

const int DOOR_PIN = 12;
const int GATE_PIN = 13;
const int LED_PIN = 15;
const int PRESS_DURATION = 200;

BlynkTimer switchDelayTimer;


void setup()
{
  Serial.begin(9600);
  Serial.println("Initializing...");
  Blynk.begin(AUTH, NETWORK, PASS);
  while (Blynk.connect() == false) {}
  pinMode(DOOR_PIN, OUTPUT);
  digitalWrite(DOOR_PIN, LOW);
  pinMode(GATE_PIN, OUTPUT);
  digitalWrite(GATE_PIN, LOW);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
}

void loop()
{
  Blynk.run();
  switchDelayTimer.run();
}

BLYNK_WRITE(V20) {
  int value = param.asInt();
  Serial.print("Received door value: ");
  Serial.println(value);
  if(value) {
    digitalWrite(DOOR_PIN, HIGH);
    digitalWrite(LED_PIN, HIGH);
    switchDelayTimer.setTimeout(PRESS_DURATION, releasePress);
  }
}

BLYNK_WRITE(V21) {
  int value = param.asInt();
  Serial.print("Received gate value: ");
  Serial.println(value);
  if(value) {
    digitalWrite(GATE_PIN, HIGH);
    digitalWrite(LED_PIN, HIGH);
    switchDelayTimer.setTimeout(PRESS_DURATION, releasePress);
  }
}

void releasePress() {
    digitalWrite(DOOR_PIN, LOW);
    digitalWrite(GATE_PIN, LOW);
    digitalWrite(LED_PIN, LOW);
}
