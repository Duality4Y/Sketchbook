#ifndef HTML_H
#define HTML_H

#include <Arduino.h>
#include <WiFiClient.h>
#include <WiFiServer.h>
#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>

#include "stripcontrol.h"

// declared in main sketch.
extern String sta_ssid;
extern String sta_pass;
extern String board_name;

extern int accessPin;

extern ESP8266WebServer server;

extern stripcontrol_t stripcontrol;
extern int stripselect;
extern int striplen;

extern void settingsStore();

void handleStripControl();
void handleWiFiSettings();
void handleLedSettings();
void handleRoot();

#endif
