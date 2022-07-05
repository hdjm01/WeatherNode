
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>
#include <BME280.h>
#include <BME280I2C.h>
#include <Wire.h>

#define sda D1
#define scl D2

String inputString = "";    
bool stringComplete = false;

BME280::TempUnit tempUnit(BME280::TempUnit_Celsius);
BME280::PresUnit presUnit(BME280::PresUnit_Pa);

BME280I2C::Settings settings(
   BME280::OSR_X1,
   BME280::OSR_X1,
   BME280::OSR_X1,
   BME280::Mode_Forced,
   BME280::StandbyTime_1000ms,
   BME280::Filter_Off,
   BME280::SpiEnable_False,
   BME280I2C::I2CAddr_0x77 // I2C address. I2C specific.
);

float temp(NAN), hum(NAN), pres(NAN);
int   maxTryBME        = 10;       // Maximale Versuche f�r die Verbindung zum BM[E|P]
long  timeSinceLastBM  = 0;
int   BM_DURATION      = 3000;     // Abstand zwischen Messungen am Sensor in ms

char* NAME = "WeatherNode";


ESP8266WebServer server(80);
BME280I2C bme(settings);

String getBME280(void) {
    String json = "{ ";
    json += "\"name\": \"WeatherNode\", ";
    
    json += " \"BME280\" : {";
        
    json += " \"Temperatur\":";
    
    json += " { ";
    
    json += "\"value\" : \"" + String(temp) + "\"";
    json += ", \"unit\" : ";
    json += "\"°C\"";
    
    json += " }";
    
    json += ", \"Luftfeuchte\":";
    
    json += " {";
    
    json += "\" value\" : ";
    json += "\"" + String(hum) + "\"";
    
    json += ", \"unit\" : ";
    json += "\"%\"";
    
    json += " }";
    
    json += ", \"Luftdruck\":";
    
    json += " {";
    
    json += " \"value\" : ";
    json += "\"" + String(pres / 100) + "\"";
    
    json += ", \"unit\" : ";
    json += "\"hPa\"";
    
    json += " }";    
    
    json += " }";    
    
    json += " }";
    return json;
}

void handleJson(){
    server.send(200, "application/json", getBME280());
}

void handleNotFound() {
  String message = NAME;
  message += "\nError: 404\nFile Not Found\n\n";
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


void setup() {
  WiFi.mode(WIFI_STA); 
  WiFiManager wm;
  bool res = wm.autoConnect("WeatherNode","setupkw39");

  if(!res) 
    Serial.println("Failed to connect");
  else 
    Serial.println("connected...yeey :)");
  
  inputString.reserve(200);
  Serial.begin(115200);
  Serial.println("\nWeatherNode");

  Wire.begin(sda,scl);
  int i = 0;
  while (!bme.begin() and ++i < maxTryBME)
  {
    delay(5);
    Serial.println("...");
    delay(50);
  }

  switch (bme.chipModel())
  {
    case BME280::ChipModel_BME280:
      Serial.println("Found BME280 sensor! Success.");
      break;
    case BME280::ChipModel_BMP280:
      Serial.println("Found BMP280 sensor! No Humidity available.");
      break;
    default:
      Serial.println("Found UNKNOWN sensor! Error!");
  }

  // Webserver

  server.on("/", []() {
    server.send(200, "text/plain", NAME);
  });
  server.on("/json", handleJson);
  server.onNotFound(handleNotFound);
  Serial.println("start Webserver");
  server.begin();
  
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
  
}


/*
  SerialEvent occurs whenever a new data comes in the hardware serial RX. This
  routine is run between each time loop() runs, so using delay inside loop can
  delay response. Multiple bytes of data may be available.
*/

void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    if (inChar == '\n') {
      // if the incoming character is a newline, set a flag
      stringComplete = true;
    }else if(inChar == '\r'){
      // remove
    }else{
      // add it to the inputString:
      inputString += inChar;
    }
  }
}
