//#include <strings_en.h>
#include <ESP8266WiFi.h>
#include <WiFiManager.h>

void setup() {
  WiFi.mode(WIFI_STA); 
  Serial.begin(115200);
  WiFiManager wm;
  wm.resetSettings();
  
  bool res = wm.autoConnect("WeatherNode","setupkw39");

  if(!res) 
    Serial.println("Failed to connect");
  else 
    Serial.println("connected...yeey :)");
}

void loop() {}
