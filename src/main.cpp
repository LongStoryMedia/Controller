#include "Tx.h"
#include "Lcd.h"

Tx tx;
Lcd lcd;

void setup()
{
  Serial.begin(115200);
  Serial1.begin(115200);
  lcd.start();
}

void loop()
{
  tx.prepare(lcd);
  tx.send(Serial1);
}