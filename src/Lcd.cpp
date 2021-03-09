#include "Lcd.h"

void Lcd::start()
{
    while (lcd.begin(COLUMS, ROWS, LCD_5x8DOTS) != 1) //colums - 20, rows - 4, pixels - 5x8
    {
        Serial.println(F("PCF8574 is not connected or lcd pins declaration is wrong. Only pins numbers: 4,5,6,16,11,12,13,14 are legal."));
        delay(5000);
    }

    lcd.print(F("PCF8574 is OK...")); //(F()) saves string to flash & keeps dynamic memory free
    delay(2000);
    writeLabels();
}

void Lcd::writeLabels()
{
    lcd.clear();
    /* prints static text */
    lcd.print(F("P:"));
    lcd.setCursor(0, 1); //set 1-st colum & 2-nd row, 1-st colum & row started at zero
    lcd.print(F("R:"));
    lcd.setCursor(7, 0);
    lcd.print(F("Y:"));
    lcd.setCursor(7, 1);
    lcd.print(F("T:"));
}

void Lcd::writeLines(int16_t pitch, int16_t roll, int16_t yaw, int16_t throttle)
{
    writeLabels();
    lcd.setCursor(2, 0);
    lcd.print(pitch);
    lcd.setCursor(2, 1);
    lcd.print(roll);
    lcd.setCursor(9, 0);
    lcd.print(yaw);
    lcd.setCursor(9, 1);
    lcd.print(throttle);
}