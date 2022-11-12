#include <SD.h>

#pragma once

#include "MyWifi.h"
#include "BME280.h"

#include "MQTT.h"
#include "I2C.h"
#include "MySerial.h"
#include "Update.h"
#include "Webserver.h"

char chip_id[32] = ""; // 4294967296 is the maximum for Uint32, so 10 characters it is
sprintf(chip_id, "ESP-%d", (long) ESP.getChipId());
