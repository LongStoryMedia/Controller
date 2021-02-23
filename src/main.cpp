#define DEBUG true

#include <SoftwareSerial.h>
#include "Rotors.h"

// pins
const uint8_t rollPin = 0;
const uint8_t pitchPin = 1;
const uint8_t yawPin = 2;
const uint8_t thrustPin = 3;
const uint8_t joyBtnPin = 9;

// memory allocation
SoftwareSerial bt(2, 3);
Rotors rotors;
int roll;
int pitch;
int yaw;
int thrust;

void setup()
{
  pinMode(joyBtnPin, INPUT_PULLUP);
  Serial.begin(9600);
  bt.begin(115200);
}

void loop()
{
  // Servo.writeMicroseconds 1000 is off, 2000 is full
  thrust = map(analogRead(thrustPin), 50, 905, 1000, 2000);
  // offset values - add extra to the top to account for inaccurate joystick ??
  roll = map(analogRead(rollPin), 0, 1000, 0, 4) - 2;
  pitch = map(analogRead(pitchPin), 0, 1000, 0, 4) - 2;
  yaw = map(analogRead(yawPin), 50, 900, 0, 4) - 2;

  // set rotor values
  rotors.setSpeed(roll, pitch, yaw, thrust);

#if DEBUG
  Serial.print(" | m1: ");
  Serial.print(rotors.speed[rotors.m1].as<int>());
  Serial.print(" | m2: ");
  Serial.print(rotors.speed[rotors.m2].as<int>());
  Serial.print(" | m3: ");
  Serial.print(rotors.speed[rotors.m3].as<int>());
  Serial.print(" | m4: ");
  Serial.print(rotors.speed[rotors.m4].as<int>());
  Serial.print(" | roll: ");
  Serial.print(roll);
  Serial.print(" | pitch: ");
  Serial.print(pitch);
  Serial.print(" | yaw: ");
  Serial.print(yaw);
  Serial.print(" | thrust target: ");
  Serial.print(thrust);
  Serial.print(" | thrust actual: ");
  Serial.print((int)(((int)rotors.speed[rotors.m1] + (int)rotors.speed[rotors.m2] + (int)rotors.speed[rotors.m3] + (int)rotors.speed[rotors.m4]) / 4));
  Serial.println(' ');
#endif
  // char serializedSpeed[ROTOR_NUM];
  // bt.write(serializedSpeed);

  serializeJson(rotors.speed, bt);
  delay(500);
}