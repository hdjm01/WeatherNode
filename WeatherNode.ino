#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>

char* NAME = "WeatherNode";

ESP8266WebServer server(80);

void handleJson(){
    String json = "{\n"; 
    json += " \"name\" : \"WeatherNode\" ";     
    json += "\n}";    
    server.send(200, "application/json", json);
}

void handleNotFound() {
  String message = NAME;
  message += "\nError: 404\nFile Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";

  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }

  server.send(404, "text/plain", message);
}


void setup() {

  // WiFi Connection
  
  WiFi.mode(WIFI_STA); 
  Serial.begin(115200);
  WiFiManager wm;
  //wm.resetSettings();
  
  bool res = wm.autoConnect(NAME,"setupkw39");

  if(!res) 
    Serial.println("Failed to connect");
  else 
    Serial.println("connected...yeey :)");

  // Webserver

  server.on("/", []() {
    server.send(200, "text/plain", NAME);
  });
  server.on("/json", handleJson);
  server.onNotFound(handleNotFound);
  Serial.println("start Webserver");
  server.begin();
  
  Serial.println("Setup Done");
}

void loop() {
  server.handleClient();
}
