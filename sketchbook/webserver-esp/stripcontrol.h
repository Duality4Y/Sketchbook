#ifndef STRIPCONTROL_H
#define STRIPCONTROL_H

#include <Arduino.h>
#include <Ticker.h>
#include "analogLedStrip.h"

// request.
// http://10.42.4.139/stripcontrol?pincode=1234&effect=0&brightness=128&var0=128&var1=64&var2=42

#define RGBCOLORS 0
#define FADING 1
#define DIGITALFADING 2

#define WS2801 0
#define WS2812 1
#define ANALOGSTRIP 2

#define RED 0
#define GREEN 1
#define BLUE 2

// holds data for led control.
typedef struct {
  int pincode;
  int effect;
  int brightness;
  int varZero;
  int varOne;
  int varTwo;
  bool changed;
} stripcontrol_t;

extern stripcontrol_t stripcontrol;

void setupStrips();
void handleStrips();
void debugPrintStripControl();

#endif