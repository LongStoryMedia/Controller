#include "config.h"

Tx tx;
#ifndef TFT
Lcd lcd;
#endif
void loopRate(int freq);
void togglePower();
uint32_t t, p;

const char *ssid = "LONGZZ";
const char *password = "6u!tar00GG@ftw";
WiFiServer server(80);
String header;

void setup()
{
  Serial.begin(115200);
  // pinMode(searchPin, INPUT_PULLUP);
  // attachInterrupt(searchPin, togglePower, FALLING);
  tx.start();
  lcd.start();

  pinMode(GPIO_NUM_5, OUTPUT);
  digitalWrite(GPIO_NUM_5, HIGH);

  // esp_sleep_pd_config(ESP_PD_DOMAIN_RTC_PERIPH, ESP_PD_OPTION_OFF);
  esp_sleep_enable_ext0_wakeup(GPIO_NUM_27, 0);
  p = 0;
}

void loop()
{
  t = micros();
  digitalWrite(GPIO_NUM_5, HIGH);
  tx.prepare();
  tx.sendPacket();
  lcd.refreshDisplay(tx.packet);
  if (tx.packet.thrust == 0)
  {
    if (p > 5000)
    {
      lcd.stop();
      esp_deep_sleep_start();
    }
    else
    {
      p++;
    }
  }
  else
  {
    p = 0;
  }

  loopRate(2000);
}

void loopRate(int freq)
{
  // DESCRIPTION: Regulate main loop rate to specified frequency in Hz
  /*
   * It's good to operate at a constant loop rate for filters to remain stable and whatnot. Interrupt routines running in the
   * background cause the loop rate to fluctuate. This function basically just waits at the end of every loop iteration until
   * the correct time has passed since the start of the current loop for the desired loop rate in Hz. 2kHz is a good rate to
   * be at because the loop nominally will run between 2.8kHz - 4.2kHz. This lets us have a little room to add extra computations
   * and remain above 2kHz, without needing to retune all of our filtering parameters.
   */
  float invFreq = 1.0 / freq * 1000000.0;
  unsigned long checker = micros();

  // Sit in loop until appropriate time has passed
  while (invFreq > (checker - t))
  {
    checker = micros();
  }
}

void togglePower()
{
#ifndef TFT
  lcd.writeLine("Connecting...", row::one);
  menu commands = tx.hummingbirdConnect();
  lcd.writeLine(commands.lineOne, row::one);
  lcd.writeLine(commands.lineTwo, row::two);
#endif
}