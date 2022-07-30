#pragma once

#include "MyWifi.h"
#include "BME280.h"

#include "MQTT.h"
#include "I2C.h"
#include "MyESP.h"
#include "MySerial.h"
#include <ESP8266HTTPUpdateServer.h>

#include "Webserver.h"



// Update
ESP8266HTTPUpdateServer httpUpdater;
const char* update_path = "/firmware";
