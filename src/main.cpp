#include "config.h"

Tx tx;
Lcd lcd;
void loopRate(int freq);
void hbConnectInterrupt();
uint32_t t;

void setup()
{
  Serial.begin(9600);
  Serial1.begin(38400);
  tx.start(hbConnectInterrupt);
  lcd.start();
  Serial1.flush();
}

void loop()
{
  t = micros();
  tx.prepare();
  tx.sendPacket();
  lcd.refreshDisplay(tx.packet);
  loopRate(200000); //do not exceed 2000Hz, all filter parameters tuned to 2000Hz by default
  // Serial1.flush();
}

void loopRate(int freq)
{
  //DESCRIPTION: Regulate main loop rate to specified frequency in Hz
  /*
   * It's good to operate at a constant loop rate for filters to remain stable and whatnot. Interrupt routines running in the
   * background cause the loop rate to fluctuate. This function basically just waits at the end of every loop iteration until 
   * the correct time has passed since the start of the current loop for the desired loop rate in Hz. 2kHz is a good rate to 
   * be at because the loop nominally will run between 2.8kHz - 4.2kHz. This lets us have a little room to add extra computations
   * and remain above 2kHz, without needing to retune all of our filtering parameters.
   */
  float invFreq = 1.0 / freq * 1000000.0;
  unsigned long checker = micros();

  //Sit in loop until appropriate time has passed
  while (invFreq > (checker - t))
  {
    checker = micros();
  }
}

void hbConnectInterrupt()
{
  lcd.writeLine("Connecting...", row::one);
  menu commands = tx.hummingbirdConnect();
  lcd.writeLine(commands.lineOne, row::one);
  lcd.writeLine(commands.lineTwo, row::two);
}