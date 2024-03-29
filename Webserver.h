#pragma once

#include <ESP8266WebServer.h>
#include "User.h"
#include "Version.h"
#include "MQTT.h"
#include "FileSystem.h"

ESP8266WebServer server(80);

String getBME280(void);
void getConfig();
void handleConfig();
void handleXML();
void handleMQTT();
void handleNotFound();
void setConfig();

extern const char * chip_id;

void initWebserver(){
  
  server.on("/", []() { server.send(200, "text/html", readFile("WeatherNode.html")); });  
  
  server.on("/main.js", []() { server.send(200, "text/javascript", readFile("main.js")); });  
  server.on("/main.css", []() { server.send(200, "text/css", readFile("main.css")); });  
    
  server.on("/BME280.json", []() { server.send(200, "application/json", getBME280()); });
  server.on("/json", []() { server.send(200, "application/json", getBME280()); });
    
  server.on("/config", handleConfig);  
  server.on("/mqtt", handleMQTT);  
  
  server.on("/config.xml", getConfig); // returns xml
  server.on("/setcfg", setConfig); // returns 200?
  
  server.on("/xml", handleXML);

  server.on("/test", []() { server.send(200, "text/html", "ok"); });  
  
  server.onNotFound(handleNotFound);
  
  Serial.println("start Webserver");
  
  server.begin();
}

void setConfig(){
  Serial.println("/setcfg");
  
  if (!server.authenticate(username, password))
      return server.requestAuthentication();

  /*if(server.hasArg("mqtt_client")){
    const String value = server.arg("mqtt_client");
    doc["mqtt_client"] = value;
  }

  if(server.hasArg("mqtt_server")){
    doc["mqtt_server"] = server.arg("mqtt_server");
  }

  if(server.hasArg("mqtt_enable")){
    doc["mqtt_enable"] = server.arg("mqtt_enable");
  }

 if(server.hasArg("mqtt_port")){
    const String port = server.arg("mqtt_port");
    mqtt_port = port.toInt();
    doc["mqtt_port"] = port;
 }

 if(server.hasArg("mqtt_topic")){
    doc["mqtt_topic"] = server.arg("mqtt_topic");
  }

 if(server.hasArg("username")){
    doc["username"] = server.arg("username");
 }
      
  if(server.hasArg("password") && server.arg("password") != ""){
    //password = server.arg("password").c_str();
    doc["password"] = server.arg("password");
  }

  if(server.hasArg("i2c_scl")){
    //scl = server.arg("i2c_scl").toInt();
    doc["i2c_scl"] = server.arg("i2c_scl");
  }

  if(server.hasArg("i2c_sda")){
    //sda = server.arg("i2c_sda").toInt();
    doc["i2c_sda"] = server.arg("i2c_sda");
  }*/

  saveCfgJson();
    
  server.send(200, "text/plain", "ok");
}

void getConfig(){
  
  if (!server.authenticate(username, password))
      return server.requestAuthentication();

  String message = "<?xml version=\"1.0\"?>"
    "<cfg>";

  message += "<param id='mqtt_client'>";
  message += doc["mqtt_client"];
  message += "</param>";

  message += "<param id='mqtt_server'>";
  message += String(doc["mqtt_server"]);
  message += "</param>";

  message += "<param id='mqtt_port'>";
  message += String(doc["mqtt_port"]);
  message += "</param>";

  message += "<param id='username'>";
  message += String(doc["username"]);
  message += "</param>";

  message += "<param id='i2c_scl'>";
  message += String(doc["i2c_scl"]);
  message += "</param>";

  message += "<param id='i2c_sda'>";
  message += String(doc["i2c_sda"]);
  message += "</param>";
 
  message += "</cfg>";
  server.send(200, "text/xml", message);
}


void handleConfig(){
  
  if (!server.authenticate(username, password))
      return server.requestAuthentication();     
      
  server.send(200, "text/html", readFile("ConfigForm.html"));
  
}

void handleMQTT(){
  if(!mqtt_connected){
    server.send(503, "text/html", "error");  
  }else{
    server.send(200, "text/html", "ok");  
  }
  
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
    String json = "{\n"
    " \"name\" : \"WeatherNode\",\n"
    
    " \"id\" : \"";
    json += chip_id;
    json += "\",\n"

    " \"version\" : \"";
    json += version;
    json += "\",\n"

    " \"BME280\" : {\n"

    "  \"Temperatur\":   {";
    json += " \"value\" : \"" + String(temp) + "\"";
    json += ",  \"unit\" : "
    "\"°C\""
    " },\n";
    
    json += "  \"Luftfeuchte\" : {"
    " \"value\" : ";
    json += "\"" + String(hum) + "\"";    
    json += ",  \"unit\" : "
    "\"%\""
    " },\n"
    
    "  \"Luftdruck\" :   {"
    " \"value\" : ";
    json += "\"" + String(pres / 100) + "\"";    
    json += ", \"unit\" : "
    "\"hPa\""
    " }\n"
    "  }\n"
    "}";
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
