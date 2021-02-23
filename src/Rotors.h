#ifndef ROTORS_H
#define ROTORS_H
#include <Arduino.h>
#include <ArduinoJson.h>

const int OFFSET_INCREMENT = 200;
const size_t ROTOR_NUM = JSON_ARRAY_SIZE(4);

class Rotors
{
private:
    void setM1Speed();
    void setM2Speed();
    void setM3Speed();
    void setM4Speed();
    void adjustOverUnderThrust();

public:
    void setSpeed(int roll, int pitch, int yaw, int thrust);
    StaticJsonDocument<ROTOR_NUM> speed;
    int thrust;
    int roll;
    int pitch;
    int yaw;
    enum
    {
        m1,
        m2,
        m3,
        m4
    };
};
#endif