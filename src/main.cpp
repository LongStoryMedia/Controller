#include "Tx.h"
#include "Lcd.h"

Tx tx;
Lcd lcd;

void lPrintOne(String str)
{
  lcd.writeLineOne(str);
}

void lPrintTwo(String str)
{
  lcd.writeLineTwo(str);
}

void hbConnectInterrupt()
{
  if (!tx.connected)
  {
    lcd.writeLineOne("Connecting...");
    delay(2000);
    tx.hummingbirdConnect(lPrintTwo);
  }
}

void setup()
{
  Serial.begin(38400);
  Serial1.begin(38400);
  lcd.start();
  tx.start(lPrintOne, hbConnectInterrupt);
  Serial1.flush();
}

void loop()
{
  StaticJsonDocument<96> json;
  JsonVariant doc = json.to<JsonVariant>();
  tx.prepare(doc);
  lcd.refreshDisplay(doc);
  if (tx.connected)
  {
    serializeJson(doc, Serial1);
  }
  // delay(50);
  Serial1.flush();
}