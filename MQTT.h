#pragma once

#include "MyWifi.h"
#include "BME280.h"

#include <PubSubClient.h>

extern const char * chip_id;

class MQTTManager {
  private:
   const char* ClientName   = strcat("WeatherNode ",chip_id);  
   IPAddress     server;
   PubSubClient  client;
   int           port       = 1883;
   bool          connected  = false;
   bool          enabled    = true;
   char          id[25];
   int           reconnectTime      = 10000;
   int           reconnect_MAX_TRY  = 100;
   int           pubtime            = 60 * 1000 * 5;
   unsigned long lastReconnect      = 0;
   int           reconnect_TRY  = 3;
   long          lastpub       = 0;
  public:
   void init();
   void reconnect();
   void publish();
   bool checkConnection();
   void publish(char topic, char value);
   void publischBME280(void);
};

void MQTTManager::init(){
  this->server = IPAddress(192, 168, 178, 24); 
  client = wclient;
  if(!enabled)
   return;
   
  
  Serial.print("Set mqtt server: ");
  Serial.print(server);
  Serial.print(" on port ");
  Serial.println(port);
  
  this->client.setServer(this->server, this->port);
  
  Serial.println("start mqtt client");
  
  this->client.connect(this->ClientName);  
  
}

bool MQTTManager::checkConnection(){
  // MQTT ++++++++++++
  if(!this->client.connected()) {
    this->connected == false;
    this->reconnect();
  }else{
    this->connected == true;
    return true;
  }
}

void  MQTTManager::publish(char topic, char value) {
  this->client.publish(topic, value);
}

// ToDO refact.
void  MQTTManager::publischBME280(void) {
  
    Serial.println("MQTT Publish");
    
    char outstr[15];
    char topic[80];
    
    sprintf(topic,"/WeaterNode/ESP-%06X/temp",chip_id);
    dtostrf(temp,7, 1, outstr);
    this->client.publish(topic, outstr);

    sprintf(topic,"/WeaterNode/ESP-%06X/hum",chip_id);
    dtostrf(hum,7, 0, outstr);
    this->client.publish(topic, outstr);
    
    sprintf(topic,"/WeaterNode/ESP-%06X/pres",chip_id);
    dtostrf(pres / 100,7, 1, outstr);
    this->client.publish(topic, outstr);    

    sprintf(topic,"/WeaterNode/ESP-%06X/data",chip_id);
    //this->client.publish(topic, getBME280().c_str());    
}



bool MQTTManager::reconnect(){
  
  if(this.client.connected()) {
    this->connected == true;
    return true;
  }else{
     this->connected == false;   
     
    // Wartezeit einhalten
    if (millis() - this->lastReconnect >= this->reconnectTime){
      
      /*
      Serial.print("(re)connect MQTT " + String(this.server.toString()) + ":" + String(this.port));        
      Serial.print(", Client ID");
      Serial.print(clientid); 
      Serial.print(" "); 
      */
      
      if(this->client.connect(clientid)){
        //Serial.println("connected");
        this.reconnect_TRY = 0; // Anzahl der Versuche zürück setzen
        
        return;
      }else{
        delay(100);
        //Serial.print("not connected : ");
        //Serial.println(this.client.state());

        // Loop until we're reconnected or reach max
        int con = 0;
        while (!this->client.connected() and con <= (this->reconnect_TRY - 1) ) {
          Serial.print("."); 
          // Attempt to connect
          if (this->client.connect(clientid)) {
            //Serial.println(" connected");
            delay(100);
            return;
          } else {
      
            /*
             Serial.print("failed, rc=");
            Serial.print(this.client.state());     
            
            Serial.print(" try again in ");
            Serial.print(reconnectMQTTTime / 1000);
            Serial.println(" seconds");*/
            
            // Wait reconnectMQTTTime ms before retrying
            delay(100);
            con++;
          }
        }
        Serial.print("failed, rc=");
        Serial.println(this.client.state()); 
        return false;
      }
       
      lastReconnectMQTT = millis();
    }  
    
  }     
} 
