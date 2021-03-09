#ifndef LCD_H
#define LCD_H
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <ArduinoJson.h>

#define COLUMS 20
#define ROWS 4

class Lcd
{
private:
    // pins
    LiquidCrystal_I2C lcd = LiquidCrystal_I2C(PCF8574_ADDR_A21_A11_A01, 4, 5, 6, 16, 11, 12, 13, 14, POSITIVE);
    void writeLabels();

public:
    void start();
    void writeLines(int16_t pitch, int16_t roll, int16_t yaw, int16_t throttle);
};

#endif