#include "stripcontrol.h"

void setupStrips()
{
    setupAnalogStrip();
    setupWS2801(1e6, 16);
    setupWS2812(150, 14);
}

void handleStrips()
{
    // check which effect is select.
    // and do pattern dependend on ledstrip.
    if(stripcontrol.effect == RGBCOLORS)
    {
        int r = stripcontrol.varZero;
        int g = stripcontrol.varOne;
        int b = stripcontrol.varTwo;
        if(stripselect == ANALOGSTRIP)
        {
            writeRgb(r, g, b);
        }
        else if(stripselect == WS2801)
        {
            setWS2801Strip(r, g, b);
            updateWS2801();
        }
        else if(stripselect == WS2812)
        {
            setWS2812Strip(r, g, b);
            updateWS2812();
        }
    }
    else if(stripcontrol.effect == FADING)
    {
        int speed = stripcontrol.varZero+1;
        int brightness = stripcontrol.brightness;
        if(stripselect == ANALOGSTRIP)
        {
            fadeRgb(speed, brightness);
        }
        else if(stripselect == WS2801)
        {
            fadeWS2801(speed, brightness);
            updateWS2801();
            // takes to long for the processor.
            // so call delay(1) to give it some time.
            delay(1);
        }
        else if(stripselect == WS2812)
        {
            fadeWS2812(speed, brightness);
            updateWS2812();
            // takes to long for the processer.
            // so call delay(1) to give it some time.
            delay(1);
        }
    }
    else if(stripcontrol.effect == DIGITALFADING)
    {

    }
}

void debugPrintStripControl()
{
    char fmtstr[100];
    sprintf(fmtstr, 
        "\nDebug:\n"
        "pincode:     %d\n"
        "effect:      %d\n"
        "brightness:  %d\n"
        "var0:        %d\n"
        "var1:        %d\n"
        "var2:        %d\n"
        "changed:     %d\n",
        stripcontrol.pincode,
        stripcontrol.effect,
        stripcontrol.brightness,
        stripcontrol.varZero,
        stripcontrol.varOne,
        stripcontrol.varTwo,
        stripcontrol.changed
        );
    Serial.println(fmtstr);
}
