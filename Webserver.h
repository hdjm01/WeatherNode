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

void initWebserver(){
  // Webserver

  server.on("/", []() { server.send(200, "text/html", INDEX); });  
  server.on("/test", []() { server.send(200, "text/html", "test"); });  
  server.on("/json", []() { server.send(200, "application/json", getBME280()); });
  server.on("/main.js", []() { server.send(200, "text/javascript", JS); });  
  server.on("/main.css", []() { server.send(200, "text/css", CSS); });  
  server.on("/config", handleConfig);  
  server.on("/getcfg", getConfig);
  server.on("/xml", handleXML);
  server.onNotFound(handleNotFound);
  
  Serial.println("start Webserver");
  
  server.begin();
}

void getConfig(){
  if (!server.authenticate(username, password))
      return server.requestAuthentication();

  String message = "<?xml version=\"1.0\"?>"
    "<cfg>";

  message += "<param id='mqtt_host' value='";
  message += mqtt_server.toString();
  message += "'/>";

  message += "<param id='mqtt_port' value='";
  message += mqtt_port;
  message += "'/>";

  message += "<param id='username' value='";
  message += username;
  message += "'/>";

  message += "<param id='scl_pin' value='";
  message += scl;
  message += "'/>";

  message += "<param id='sda_pin' value='";
  message += sda;
  message += "'/>";
 
  message += "</cfg>";
  server.send(200, "text/xml", message);
}

void handleConfig(){
  if (!server.authenticate(username, password))
      return server.requestAuthentication();

  String content = "<html>";
  //content += head;
  content += "<body>";
  //content += html_title;

  if(server.hasArg("action")){
    content += server.arg("action");
  }

  /*content += navi;
  content += configForm;
  content += projectLink;  */
  content += "</body>"
  "</html>";
      
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
  <device>
   <name>WeatherNode</name>
   <temp></temp>
   <hum></hum>
   <pres></pres>
  </device>
  )";
  
  server.send(200, "text/xml", xml);
}
