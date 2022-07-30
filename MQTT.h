#pragma once

#include "MyWifi.h"
#include "MyESP.h"
#include "BME280.h"

#include <PubSubClient.h>

const char* MQTTClientName   = "ESp-"+ESP.getChipId();
IPAddress     mqtt_server(192, 168, 178, 24);
PubSubClient  mqtt_client(wclient);
int           mqtt_port                 = 1883;
bool          mqtt_connected            = false;
int           mqtt_pubtime              = 60 * 1000 * 5;
int           reconnectMQTT_TRY         = 3;
unsigned long lastReconnectMQTT         = 0;
int           reconnectMQTTTime         = 10000;
int           reconnectMQTT_MAX_TRY     = 100;

long          mqtt_lastpub = 0;
char          clientid[25];

String getBME280(void);

void initMQTT(){
  
  snprintf(clientid,25,"ESP-%08X",chipid);
  Serial.print("Set mqtt server: ");
  Serial.print(mqtt_server);
  Serial.print(" on port ");
  Serial.println(mqtt_port);
  mqtt_client.setServer(mqtt_server, mqtt_port);
  Serial.println("start mqtt client");
  mqtt_client.connect(clientid);  
}

void  publischBME280(void) {
  
    Serial.println("MQTT Publish");
    
    static char outstr[15];
    char topic[80];
    
    sprintf(topic,"/WeaterNode/ESP-%06X/temp",chipid);
    dtostrf(temp,7, 1, outstr);
    mqtt_client.publish(topic, outstr);

    sprintf(topic,"/WeaterNode/ESP-%06X/hum",chipid);
    dtostrf(hum,7, 0, outstr);
    mqtt_client.publish(topic, outstr);
    
    sprintf(topic,"/WeaterNode/ESP-%06X/pres",chipid);
    dtostrf(pres / 100,7, 1, outstr);
    mqtt_client.publish(topic, outstr);    

    sprintf(topic,"/WeaterNode/ESP-%06X/data",chipid);
    mqtt_client.publish(topic, getBME280().c_str());    
}



void reconnectMQTT(){
  
  if(mqtt_client.connected()) {
    return;
  }else{
        
    // Wartezeit einhalten
    if (millis() - lastReconnectMQTT >= reconnectMQTTTime){
      
      /*
      Serial.print("(re)connect MQTT " + String(mqtt_server.toString()) + ":" + String(mqtt_port));        
      Serial.print(", Client ID");
      Serial.print(clientid); 
      Serial.print(" "); 
      */
      
      if(mqtt_client.connect(clientid)){
        //Serial.println("connected");
        reconnectMQTT_TRY = 0; // Anzahl der Versuche zürück setzen
        return;
      }else{
        delay(100);
        //Serial.print("not connected : ");
        //Serial.println(mqtt_client.state());

        // Loop until we're reconnected or reach max
        int con = 0;
        while (!mqtt_client.connected() and con <= (reconnectMQTT_TRY - 1) ) {
          Serial.print("."); 
          // Attempt to connect
          if (mqtt_client.connect(clientid)) {
            //Serial.println(" connected");
            delay(100);
            return;
          } else {
      
            /*
             Serial.print("failed, rc=");
            Serial.print(mqtt_client.state());     
            
            Serial.print(" try again in ");
            Serial.print(reconnectMQTTTime / 1000);
            Serial.println(" seconds");*/
            
            // Wait reconnectMQTTTime ms before retrying
            delay(100);
            con++;
          }
        }
        Serial.print("failed, rc=");
        Serial.println(mqtt_client.state()); 
      }
        
      lastReconnectMQTT = millis();
    }  
    
  }     
} 
