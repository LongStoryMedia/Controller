#ifndef LCD_H
#define LCD_H

#define COLUMS 20
#define ROWS 4

typedef enum
{
    one,
    two
} row;

class Lcd
{
private:
    void writeLabels();
    uint32_t lastRefresh;

public:
    LiquidCrystal_I2C screen = LiquidCrystal_I2C(PCF8574_ADDR_A21_A11_A01, 4, 5, 6, 16, 11, 12, 13, 14, POSITIVE);
    void start();
    void writeEuler(int16_t pitch, int16_t roll, int16_t yaw, int16_t thrust);
    void writeLine(const __FlashStringHelper *lineOne, row row);
    void writeLine(char *lineOne, row row);
    void writeLine(String lineOne, row row);
    uint32_t refreshDisplay(Packet &packet);
};

#endif