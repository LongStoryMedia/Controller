#include "config.h"

#ifndef TFT

void Lcd::start()
{
    screen.displayOn();
    while (screen.begin(COLUMS, ROWS, LCD_5x8DOTS) != 1) // colums - 20, rows - 4, pixels - 5x8
    {
        Serial.println(F("PCF8574 is not connected or screen pins declaration is wrong. Only pins numbers: 4,5,6,16,11,12,13,14 are legal."));
        delay(5000);
    }

    screen.print(F("PCF8574 is OK...")); //(F()) saves string to flash & keeps dynamic memory free
}

void Lcd::stop()
{
    screen.displayOff();
}

void Lcd::refreshDisplay(Packet &packet)
{
    // we should't update this often, but don't want to delay the whole program
    if (micros() - lastRefresh > 500000)
    {
        writeEuler(packet.pitch, packet.roll, packet.yaw, packet.thrust);
        lastRefresh = micros();
    }
}

void Lcd::writeLabels()
{
    screen.clear();
    /* prints static text */
    screen.print(F("P:"));
    screen.setCursor(0, 1); // set 1-st colum & 2-nd row, 1-st colum & row started at zero
    screen.print(F("R:"));
    screen.setCursor(7, 0);
    screen.print(F("Y:"));
    screen.setCursor(7, 1);
    screen.print(F("T:"));
}

void Lcd::writeEuler(int16_t pitch, int16_t roll, int16_t yaw, int16_t thrust)
{
    writeLabels();
    screen.setCursor(2, 0);
    screen.print(pitch);
    screen.setCursor(2, 1);
    screen.print(roll);
    screen.setCursor(9, 0);
    screen.print(yaw);
    screen.setCursor(9, 1);
    screen.print(thrust);
}

void Lcd::writeLine(char *line, row r)
{
    if (r == row::one)
    {
        screen.clear();
    }
    screen.setCursor(0, r);
    // screen.scrollDisplayLeft();
    screen.print(line);
}

void Lcd::writeLine(String line, row r)
{
    if (r == row::one)
    {
        screen.clear();
    }
    screen.setCursor(0, r);
    // screen.scrollDisplayLeft();
    screen.print(line);
}

void Lcd::writeLine(const __FlashStringHelper *line, row r)
{
    if (r == row::one)
    {
        screen.clear();
    }
    screen.setCursor(0, r);
    // screen.scrollDisplayLeft();
    screen.print(line);
}
#endif