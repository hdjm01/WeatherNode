#include "WeatherNode.h"


void setup() {
  
  chipid=ESP.getChipId();
  
  initSerial();  
  initWiFi();

  initBME();

  // Updateserver
  httpUpdater.setup(&server, update_path, username, password);
  Serial.println("HTTPUpdateServer ready!");

  initWebserver();
  initMQTT();
  
  Serial.println("Setup Done");
}


void loop() { 
  server.handleClient();

  // Serial Input/Response
  if (stringComplete) {
    
    if(inputString == "BME280"){
        Serial.println(getBME280());
    }else if(inputString == "SENSORS"){
        Serial.println(getBME280());
    }else{
        Serial.println("\n# WeatherNode");
        Serial.println("## Commands");
        Serial.println("   BME280");
        Serial.println("   SENSORS");
        Serial.println("   https://github.com/hdjm01/WeatherNode/wiki ");
    }    
    
    inputString = "";
    stringComplete = false;
  }  

  // Read Sensor
  if (timeSinceLastBM == 0 || (millis() - timeSinceLastBM > BM_DURATION)) {
    timeSinceLastBM = millis();
    bme.read(pres, temp, hum, tempUnit, presUnit);
  }

  if(!mqtt_client.connected()) {
    reconnectMQTT();
  }
  
  if( mqtt_lastpub == 0 || ( mqtt_lastpub + mqtt_pubtime ) < millis() ){
     publischBME280();
     mqtt_lastpub = millis();
  }
  
}
