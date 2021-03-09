#include "Tx.h"

void Tx::prepare(Lcd lcd)
{
    // Servo.writeMicroseconds 1000 is off, 2000 is full
    thrust = map(analogRead(thrustPin), 55, 905, 1000, 2000);
    roll = map(analogRead(rollPin), 0, 1023, -180, 180);
    pitch = map(analogRead(pitchPin), 0, 1015, -180, 180);
    yaw = map(analogRead(yawPin), 90, 910, 180, -180);
    doc["roll"] = roll < 10 && roll > -10 ? 0 : roll;
    doc["pitch"] = pitch < 10 && pitch > -10 ? 0 : pitch;
    doc["yaw"] = yaw < 10 && yaw > -10 ? 0 : yaw;
    doc["thrust"] = thrust;

    // we should't update this often, but don't want to delay the whole program
    if (millis() - lastTransmissionTime > 1000)
    {
        lcd.writeLines(doc["pitch"], doc["roll"], doc["yaw"], doc["thrust"]);
    }
}

void Tx::send(Uart serial)
{
    lastTransmissionTime = millis();
    serializeJson(doc, serial);
}
