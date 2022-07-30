#pragma once

#include <ESP8266WiFi.h>
#include <WiFiManager.h>

WiFiClient wclient;

void initWiFi(){
  WiFi.mode(WIFI_STA); 
  WiFiManager wm;
  bool res = wm.autoConnect("WeatherNode","setupkw39");

  if(!res) 
    Serial.println("Failed to connect");
  else
    Serial.println("connected...yeey :)");
}
