#include "Lcd.h"

void Lcd::start()
{
    while (screen.begin(COLUMS, ROWS, LCD_5x8DOTS) != 1) //colums - 20, rows - 4, pixels - 5x8
    {
        Serial.println(F("PCF8574 is not connected or screen pins declaration is wrong. Only pins numbers: 4,5,6,16,11,12,13,14 are legal."));
        delay(5000);
    }

    screen.print(F("PCF8574 is OK...")); //(F()) saves string to flash & keeps dynamic memory free
}

uint32_t Lcd::refreshDisplay(JsonVariant doc)
{
    // we should't update this often, but don't want to delay the whole program
    if (millis() - lastRefresh > 1000)
    {
        writeEuler(doc["pitch"], doc["roll"], doc["yaw"], doc["thrust"]);
        lastRefresh = millis();
    }
}

void Lcd::writeLabels()
{
    screen.clear();
    /* prints static text */
    screen.print(F("P:"));
    screen.setCursor(0, 1); //set 1-st colum & 2-nd row, 1-st colum & row started at zero
    screen.print(F("R:"));
    screen.setCursor(7, 0);
    screen.print(F("Y:"));
    screen.setCursor(7, 1);
    screen.print(F("T:"));
}

void Lcd::writeEuler(int16_t pitch, int16_t roll, int16_t yaw, int16_t throttle)
{
    writeLabels();
    screen.setCursor(2, 0);
    screen.print(pitch);
    screen.setCursor(2, 1);
    screen.print(roll);
    screen.setCursor(9, 0);
    screen.print(yaw);
    screen.setCursor(9, 1);
    screen.print(throttle);
}

void Lcd::writeLineOne(char *line)
{
    screen.clear();
    screen.home();
    screen.print(line);
}

void Lcd::writeLineOne(String line)
{
    screen.clear();
    screen.home();
    screen.print(line);
}

void Lcd::writeLineOne(const __FlashStringHelper *line)
{
    screen.clear();
    screen.home();
    screen.print(line);
}

void Lcd::writeLineTwo(char *line)
{
    screen.setCursor(0, 1);
    screen.print(line);
}

void Lcd::writeLineTwo(String line)
{
    screen.setCursor(0, 1);
    screen.print(line);
}

void Lcd::writeLineTwo(const __FlashStringHelper *line)
{
    screen.setCursor(0, 1);
    screen.print(line);
}

void Lcd::writeLine(char *line)
{
    screen.scrollDisplayLeft();
    screen.print(line);
}

void Lcd::writeLine(String line)
{
    screen.scrollDisplayLeft();
    screen.print(line);
}

void Lcd::writeLine(const __FlashStringHelper *line)
{
    screen.scrollDisplayLeft();
    screen.print(line);
}