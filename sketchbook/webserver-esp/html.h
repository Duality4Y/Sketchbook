#ifndef HTML_H
#define HTML_H

#include <Arduino.h>
#include <WiFiClient.h>
#include <WiFiServer.h>
#include <ESP8266WebServer.h>
#include "stripcontrol.h"

// declared in main sketch.
extern String sta_ssid;
extern String sta_pass;
extern String board_name;

extern int accesPin;

extern ESP8266WebServer server;

extern stripcontrol_t stripcontrol;

extern void settingsStore();

void handleStripControl();
void handleWiFiSettings();
void handleLedSettings();
void handleRoot();

#endif
