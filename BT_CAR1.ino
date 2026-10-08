#include "BluetoothSerial.h"
#include <Arduino.h>

BluetoothSerial serialBT;

// Bluetooth signal variable
char btSignal;

// Initial Speed
int Speed = 100;

// PWM Pins
int enA = 5;
int enB = 23;

// Motor control pins
int IN1 = 22;
int IN2 = 21;
int IN3 = 19;
int IN4 = 18;

void setup() {
  Serial.begin(115200);

  // Bluetooth Name
  serialBT.begin("BLUETOOTH NAME");

  // Set motor pins as output
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  // Attach PWM (ESP32 Core 3.x new API)
  ledcAttach(enA, 5000, 8);   // pin, frequency, resolution
  ledcAttach(enB, 5000, 8);

  // Initial stop
  stopCar();
}

void loop() {

  while (serialBT.available()) {
    btSignal = serialBT.read();

    Serial.println(btSignal);

    // Speed control
    if (btSignal == '0') Speed = 100;
    if (btSignal == '1') Speed = 110;
    if (btSignal == '2') Speed = 120;
    if (btSignal == '3') Speed = 130;
    if (btSignal == '4') Speed = 140;
    if (btSignal == '5') Speed = 150;
    if (btSignal == '6') Speed = 180;
    if (btSignal == '7') Speed = 200;
    if (btSignal == '8') Speed = 220;
    if (btSignal == '9') Speed = 240;
    if (btSignal == 'q') Speed = 255;

    // Direction control
    if (btSignal == 'F') forward();
    else if (btSignal == 'B') backward();
    else if (btSignal == 'L') left();
    else if (btSignal == 'R') right();
    else if (btSignal == 'S') stopCar();
  }
}

// ================= MOTOR FUNCTIONS =================

void forward() {
  ledcWrite(enA, Speed);
  ledcWrite(enB, Speed);

  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void backward() {
  ledcWrite(enA, Speed);
  ledcWrite(enB, Speed);

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void left() {
  ledcWrite(enA, Speed);
  ledcWrite(enB, Speed);

  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void right() {
  ledcWrite(enA, Speed);
  ledcWrite(enB, Speed);

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}
void baclk(){
  ledcWrite(enA,speed);
  ledcWrite(enB,speed);

  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);
}

void stopCar() {
  ledcWrite(enA, 0);
  ledcWrite(enB, 0);

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}
