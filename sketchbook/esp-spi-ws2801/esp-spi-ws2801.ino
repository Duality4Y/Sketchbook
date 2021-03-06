#include <WiFiUdp.h>
#include <ESP8266WiFi.h>

#include "initials.h"
#include <otaupload.h>
#include <esputils.h>

#include <SPI.h>

#define NUMPIXELS 16
uint8_t buffer[3][NUMPIXELS];

int striplen = NUMPIXELS;

int colors[3] = {0, 0, 0};
int value = 0;
int pledselect = 0;
int ledselect = 0;

unsigned long ccurrent = 0;
unsigned long cprevious = 0;
int cinterval = 10;

void colorinc()
{
    value++;
    if(value > 255)
    {
        ledselect++;
        value = 1;
        if(ledselect == 3)
        {
            ledselect = 0;
            pledselect = 2;
        }
        else
        {
            pledselect = ledselect - 1;
        }
    }
    colors[pledselect] = 255 - value;
    colors[ledselect] = value;
}

void setupWS2801(int freq, int len)
{
    SPI.begin();
    SPI.setFrequency(1e6);
}

void setWS2801Pixel(int pos, int r, int g, int b)
{
    buffer[0][pos] = r;
    buffer[1][pos] = g;
    buffer[2][pos] = b;
}

void setWS2801Strip(int r, int g, int b)
{
    for(int i = 0; i < striplen; i++)
    {
        setWS2801Pixel(i, r, g, b);
    }
}

void fadeWS2801(int speed, int brightness)
{
    ccurrent = millis();
    if((ccurrent - cprevious) >= cinterval)
    {
        cprevious = ccurrent;
        colorinc();
    }

    cinterval = speed+1;
    float brightnessFactor = (float)(((float)brightness)/100);
    int r = colors[0] * brightnessFactor;
    int g = colors[1] * brightnessFactor;
    int b = colors[2] * brightnessFactor;

    setWS2801Strip(r, g, b);
}

void updateWS2801()
{
    for(int i = 0; i < striplen; i++)
    {
        SPI.transfer(buffer[0][i]);
        SPI.transfer(buffer[1][i]);
        SPI.transfer(buffer[2][i]);
    }
}

void setup()
{
    Serial.begin(115200);

    setupWS2801(1e6, NUMPIXELS);

    setupSTA();
    setupOta();
    setWS2801Strip(255, 255, 255);

    Serial.println("\nEntering Loop");
}

void loop()
{
    handleSketchUpdate();
    fadeWS2801(100, 100);
    setWS2801Strip(colors[0], colors[1], colors[2]);
    updateWS2801();
    delay(1);
}