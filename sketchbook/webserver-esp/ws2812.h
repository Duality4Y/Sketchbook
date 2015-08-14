#ifndef WS2812_H
#define WS2812_H
#include <NeoPixelBus.h>
#include "fadeColor.h"

void setupWS2812(uint16_t, uint8_t);
void setWS2812Strip(int, int, int);
void fadeWS2812(int, int);
void updateWS2812();

#endif