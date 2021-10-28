#ifndef CONFIG_H
#define CONFIG_H

#define DEBUG false

#include <Arduino.h>
#include <Wire.h>
#if defined TFT
#include <TFT_eSPI.h> // Hardware-specific library
#else
#include <LiquidCrystal_I2C.h>
#endif
#include <ArduinoJson.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#include "Tx.h"
#include "Lcd.h"

#endif