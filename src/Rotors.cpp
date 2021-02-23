#include "Rotors.h"

void Rotors::adjustOverUnderThrust()
{
    if (thrust <= 1000)
    {
        for (int i = 0; i < 4; i++)
        {
            speed[i] = 1000;
        }
        return;
    }
    for (int i = 0; i < 4; i++)
    {
        if (speed[i] > 2000)
        {
            int overThrust = speed[i].as<int>() - 2000;
            for (int i = 0; i < 4; i++)
            {
                speed[i] = speed[i].as<int>() - overThrust;
            }
            break;
        }
        if (speed[i] < 1000 && abs(speed[i].as<int>() - thrust) >= 10)
        {
            int underThrust = 1000 - speed[i].as<int>();
            for (int i = 0; i < 4; i++)
            {
                speed[i] = speed[i].as<int>() + underThrust;
            }
            break;
        }
    }
}

void Rotors::setM4Speed()
{
    int rollOffset = OFFSET_INCREMENT * roll;
    int pitchOffset = OFFSET_INCREMENT * pitch;
    int yawOffset = -(OFFSET_INCREMENT * yaw);
    speed[m4] = rollOffset + pitchOffset + yawOffset + thrust;
}

void Rotors::setM3Speed()
{
    int rollOffset = -(OFFSET_INCREMENT * roll);
    int pitchOffset = OFFSET_INCREMENT * pitch;
    int yawOffset = OFFSET_INCREMENT * yaw;
    speed[m3] = rollOffset + pitchOffset + yawOffset + thrust;
}

void Rotors::setM2Speed()
{
    int rollOffset = OFFSET_INCREMENT * roll;
    int pitchOffset = -(OFFSET_INCREMENT * pitch);
    int yawOffset = OFFSET_INCREMENT * yaw;
    speed[m2] = rollOffset + pitchOffset + yawOffset + thrust;
}

void Rotors::setM1Speed()
{
    int rollOffset = -(OFFSET_INCREMENT * roll);
    int pitchOffset = -(OFFSET_INCREMENT * pitch);
    int yawOffset = -(OFFSET_INCREMENT * yaw);
    speed[m1] = rollOffset + pitchOffset + yawOffset + thrust;
}

void Rotors::setSpeed(int roll, int pitch, int yaw, int thrust)
{
    this->roll = roll;
    this->pitch = pitch;
    this->yaw = yaw;
    this->thrust = thrust;
    setM1Speed();
    setM2Speed();
    setM3Speed();
    setM4Speed();
    adjustOverUnderThrust();
};
