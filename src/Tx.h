#ifndef TX_H
#define TX_H
#include <Arduino.h>
#include <ArduinoJson.h>
#include "Lcd.h"

const int OFFSET_INCREMENT = 200;
const size_t DOC_SIZE = JSON_OBJECT_SIZE(8);

class Tx
{
private:
    // pins
    const uint8_t thrustPin = 9;
    const uint8_t yawPin = 1;
    const uint8_t pitchPin = 3;
    const uint8_t rollPin = 2;
    int16_t thrust;
    int16_t roll;
    int16_t pitch;
    int16_t yaw;
    uint32_t lastTransmissionTime;

public:
    void send(Uart serial);
    void prepare(Lcd lcd);
    StaticJsonDocument<DOC_SIZE> doc;
};
#endif