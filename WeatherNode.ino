#include "WeatherNode.h"

MQTTManager mqtt_manager();

void setup() {
  delay(500);
  initSerial();  
  initFS();
  initWiFi();
  initBME();
  initUpdate();
  initWebserver();

  mqtt_manager.init();
  //initMQTT();  
  
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

  if( mqtt_manager.lastpub == 0 || ( mqtt_manager.lastpub + mqtt_manager.pubtime ) < millis() ){
    if(mqtt_manager.checkConnection()){
      mqtt_manager.publischBME280();
      mqtt_manager.lastpub = millis();
    }
  }
  
}
