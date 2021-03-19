#ifndef TX_H
#define TX_H
#include <Arduino.h>
#include <ArduinoJson.h>
#include <Bounce2.h>

typedef void (*strCb)(String str);

class Tx
{
private:
    // pins
    const uint8_t thrustPin = A0;
    const uint8_t yawPin = A1;
    const uint8_t rollPin = A2;
    const uint8_t pitchPin = A3;
    const uint8_t searchPin = 9;
    int16_t thrust;
    int16_t roll;
    int16_t pitch;
    int16_t yaw;
    String atCommand(char *cmd);
    bool isConnected();

public:
    void prepare(JsonVariant doc);
    void start(strCb cb, void (*func)());
    void hummingbirdConnect(strCb cb);
    bool connected;
};
#endif