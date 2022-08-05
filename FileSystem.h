#pragma once

#include <LittleFS.h>
#include <ArduinoJson.h>
const char cfgFileName[] = "WeatherNode.cfg";
StaticJsonDocument<500> doc;

bool readCFGFile();
bool getCFG();


void initFS(){

  Serial.println(F("Inizializing FS..."));
    if (LittleFS.begin()){
        Serial.println(F("done."));
    }else{
        Serial.println(F("fail."));
        /*LittleFS.format();
        initFS();*/
    }
  
    // Get all information of your LittleFS
    FSInfo fs_info;
    LittleFS.info(fs_info);
 
    Serial.println("File sistem info.");
 
    Serial.print("Total space:      ");
    Serial.print(fs_info.totalBytes);
    Serial.println("byte");
 
    Serial.print("Total space used: ");
    Serial.print(fs_info.usedBytes);
    Serial.println("byte");
 
    Serial.print("Block size:       ");
    Serial.print(fs_info.blockSize);
    Serial.println("byte");
 
    Serial.print("Page size:        ");
    Serial.print(fs_info.totalBytes);
    Serial.println("byte");
 
    Serial.print("Max open files:   ");
    Serial.println(fs_info.maxOpenFiles);
 
    Serial.print("Max path length:  ");
    Serial.println(fs_info.maxPathLength);
 
    Serial.println();
 
    // Open dir folder
    Dir dir = LittleFS.openDir("/");
    // Cycle all the content
    while (dir.next()) {
        // get filename
        Serial.print(dir.fileName());
        Serial.print(" - ");
        // If element have a size display It else write 0
        if(dir.fileSize()) {
            File f = dir.openFile("r");
            Serial.println(f.size());
            f.close();
        }else{
            Serial.println("0");
        }
    }
  if(LittleFS.exists(cfgFileName)){
    Serial.println("Found configuration file");   
  }
  readCFGFile();
}

bool readCFGFile(){
  File file = LittleFS.open(cfgFileName, "r");
  if (!file) {
    Serial.println("Failed to open data file");    
    return false;
  }
  
  DeserializationError error = deserializeJson(doc, file);
  if (error){
    Serial.println(F("Failed to read file, using default configuration"));
    return false;
  }
  file.close();  
  return true;
}

String readFile(String filename){
  String s;
  File file = LittleFS.open(filename, "r");
  if (!file) {
    Serial.println("Failed to open data file");
    return "";
  }

  size_t size = file.size();
  /*if (size > 1024) {
    Serial.println("Data file size is too large");
    return "";
  }*/
  while(file.available()){
    s += file.readString();
  }
  file.close();  
  return s;
}

String getCFG(String var){
  return doc[var];
}
