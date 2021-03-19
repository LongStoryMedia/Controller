#include "Tx.h"

void Tx::prepare(JsonVariant doc)
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
}

void Tx::hummingbirdConnect(strCb cb)
{
    cb(atCommand("at+conA4DA32550629"));
    connected = isConnected();
    delay(500);
}

void Tx::start(strCb cb, void (*func)())
{
    connected = false;
    // cb(atCommand("at+pio11"));
    cb(atCommand("at+renew"));
    cb(atCommand("at+noti1"));
    Serial1.end();
    Serial1.begin(9600);
    cb(atCommand("at+baud5"));
    Serial1.end();
    Serial1.begin(38400);
    cb(atCommand("at+baud?"));
    cb(atCommand("at+imme0"));
    cb(atCommand("at+role1"));
    cb(atCommand("at+mode0"));
    cb(atCommand("at+namecontroller"));
    cb(atCommand("at+reset"));
    // cb(atCommand("at+con882583F32582"));
    // cb(atCommand("at+conA4DA32550629"));
    // cb(atCommand("at+start"));

    pinMode(searchPin, INPUT_PULLUP);
    attachInterrupt(searchPin, func, CHANGE);
}

bool Tx::isConnected()
{
    bool c = digitalRead(10) == HIGH;
    connected = c;
    return c;
}

String Tx::atCommand(char *cmd)
{
    String atLine = "";
    char _cmd[20];
    strcpy(_cmd, cmd);
    strcat(_cmd, "\r\n");
    Serial1.print(_cmd);
    uint32_t t = millis();
    while (t > millis() - 3500)
    {
        if (Serial1.available() > 0)
        {
            atLine = Serial1.readStringUntil('\n');
            return atLine;
        }
    }
    return atLine;
}
