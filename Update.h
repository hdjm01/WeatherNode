#pragma once
#include <ESP8266HTTPUpdateServer.h>
#include "Webserver.h"
ESP8266HTTPUpdateServer httpUpdater;
const char* update_path = "/firmware";
void initUpdate(){
  // Updateserver
  httpUpdater.setup(&server, update_path, username, password);
  Serial.println("HTTPUpdateServer ready!");
}
