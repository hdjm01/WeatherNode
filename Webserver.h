#pragma once

#include <ESP8266WebServer.h>
#include "Index.h"
#include "configForm.h"
#include "User.h"
#include "CSS.h"
#include "JavaScript.h"
#include "Version.h"

ESP8266WebServer server(80);

String getBME280(void);
void getConfig();
void handleConfig();
void handleXML();
void handleNotFound();
void setConfig();

void initWebserver(){
  // Webserver

  server.on("/", []() { server.send(200, "text/html", INDEX); });  
  
  //server.on("/test", []() { server.send(200, "text/html", "test"); });  
  
  server.on("/BME280.json", []() { server.send(200, "application/json", getBME280()); });
  server.on("/json", []() { server.send(200, "application/json", getBME280()); });
  
  server.on("/main.js", []() { server.send(200, "text/javascript", JS); });  
  server.on("/main.css", []() { server.send(200, "text/css", CSS); });  
  
  server.on("/config", handleConfig);  
  
  server.on("/getcfg", getConfig); // returns xml
  server.on("/setcfg", setConfig); // returns 200?
  
  server.on("/xml", handleXML);
  
  server.onNotFound(handleNotFound);
  
  Serial.println("start Webserver");
  
  server.begin();
}

void setConfig(){
  if (!server.authenticate(username, password))
      return server.requestAuthentication();

  if(server.hasArg("mqtt_server")){
    mqtt_server.fromString(server.arg("mqtt_server"));
  }

 if(server.hasArg("mqtt_port"))
    mqtt_port = server.arg("mqtt_port").toInt();

 /*if(server.hasArg("username"))
    username = server.arg("username").c_str();
      
  if(server.hasArg("password") && server.arg("password") != "")
    password = server.arg("password").c_str();
*/

  if(server.hasArg("i2c_scl"))
    scl = server.arg("i2c_scl").toInt();

  if(server.hasArg("i2c_sda"))
    sda = server.arg("i2c_sda").toInt();
    
  server.send(200, "text/plain", "ok");
}

void getConfig(){
  if (!server.authenticate(username, password))
      return server.requestAuthentication();

  String message = "<?xml version=\"1.0\"?>"
    "<cfg>";

  message += "<param id='mqtt_server'>";
  message += mqtt_server.toString();
  message += "</param>";

  message += "<param id='mqtt_port'>";
  message += mqtt_port;
  message += "</param>";

  message += "<param id='username'>";
  message += username;
  message += "</param>";

  message += "<param id='scl_pin'>";
  message += scl;
  message += "</param>";

  message += "<param id='sda_pin'>";
  message += sda;
  message += "</param>";
 
  message += "</cfg>";
  server.send(200, "text/xml", message);
}

void handleConfig(){
  if (!server.authenticate(username, password))
      return server.requestAuthentication();     
  server.send(200, "text/html", configForm);
}

void handleNotFound() {
  String message = "WeatherNode\nError: 404\nFile Not Found\n\n";
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


String getBME280(void) {
    String json = "{ "
    "\"name\" : \"WeatherNode\", "
    
    "\"id\" : \"";
    json += ESP.getChipId();
    json += "\", "

    "\"version\" : \"";
    json += version;
    json += "\", "

    " \"BME280\" : {"

    " \"Temperatur\": { ";
    json += "\"value\" : \"" + String(temp) + "\"";
    json += ", \"unit\" : "
    "\"°C\""
    " }";
    
    json += ", \"Luftfeuchte\" : { "
    "\" value\" : ";
    json += "\"" + String(hum) + "\"";    
    json += ", \"unit\" : "
    "\"%\""
    " }"
    
    ", \"Luftdruck\" : { "
    " \"value\" : ";
    json += "\"" + String(pres / 100) + "\"";    
    json += ", \"unit\" : "
    "\"hPa\""
    " }"
    " }"    
    " }";
    return json;
}

/*
void handleSaveConfig(){
  if (!server.authenticate(username, password))
      return server.requestAuthentication();

  String content = "<html>";
  content += head;
  content += "<body>";
  content += html_title;
  content += "<p>Ihre Angaben wurden gespeichert</p>";
  content += "</body>"
  "</html>";

  server.send(200, "text/html", content);
}*/

void handleXML(){
  String xml = R"(<?xml version="1.0"?>
  <device name="WeatherNode">
   <name>BME280</name>
   <temp>)";
   xml  += String(temp) + "</temp>"
   "<hum>" + String(hum) + "</hum>"
   "<pres>" + String(pres / 100) + "</pres>"
  "</device>\n";
  
  server.send(200, "text/xml", xml);
}
