#pragma once

#include <LittleFS.h>

const char cfgFileName[] = "WeatherNode.cfg";

bool readCFGFile();

void FileSystemInfo();
void showFiles();

void initFS(){

  Serial.println(F("Inizializing FS..."));
  
  if (LittleFS.begin()){
    Serial.println(F("done."));
  }else{
    Serial.println(F("fail."));
    return;
  }

  FileSystemInfo();
  showFiles();
  
  if(LittleFS.exists(cfgFileName)){
    Serial.println("Found configuration file");
    readCFGFile();
  }else{
    Serial.println("Missing configuration file");
    return;
  }
  
}

void FileSystemInfo(){
    Serial.println("File System Information");
    FSInfo fs_info;
    LittleFS.info(fs_info);
 
    Serial.println("File sistem info.");
 
    Serial.printf("Total space:      %d byte\n", fs_info.totalBytes);
    Serial.printf("Total space used: %d byte\n", fs_info.usedBytes); 
    Serial.printf("Block size:       %d byte\n", fs_info.blockSize);
    Serial.printf("Page size:        %d byte\n", fs_info.totalBytes);
 
    Serial.printf("Max open files:   %d\n", fs_info.maxOpenFiles);
    Serial.printf("Max path length:  %d\n", fs_info.maxPathLength);
 
    Serial.println();
}

void showFiles(){
  Serial.println("Files");
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
}

bool readCFGFile(){
  Serial.println("Read config file");
  File file = LittleFS.open(cfgFileName, "r");
  if (!file) {
    Serial.println("Failed to open data file");
    return false;
  }

  size_t size = file.size();
  
  if (size > 1024) {
    Serial.println("Data file size is too large");
    return false;
  }
  while(file.available()){
    Serial.write(file.read());
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

  /*
  size_t size = file.size();
  if (size > 1024) {
    Serial.println("Data file size is too large");
    return "";
  }*/

  while(file.available()){
    s += file.readString();
  }
  file.close();  
  return s;
}
