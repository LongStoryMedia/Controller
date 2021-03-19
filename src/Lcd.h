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
    void writeLabels();
    uint32_t lastRefresh;

public:
    LiquidCrystal_I2C screen = LiquidCrystal_I2C(PCF8574_ADDR_A21_A11_A01, 4, 5, 6, 16, 11, 12, 13, 14, POSITIVE);
    void start();
    void writeEuler(int16_t pitch, int16_t roll, int16_t yaw, int16_t throttle);
    void writeLineOne(char *lineOne);
    void writeLineOne(String lineOne);
    void writeLineOne(const __FlashStringHelper *lineOne);
    void writeLineTwo(char *lineOne);
    void writeLineTwo(String lineOne);
    void writeLineTwo(const __FlashStringHelper *lineOne);
    void writeLine(const __FlashStringHelper *lineOne);
    void writeLine(char *lineOne);
    void writeLine(String lineOne);
    uint32_t refreshDisplay(JsonVariant doc);
};

#endif