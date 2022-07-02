#include <BME280.h>
#include <BME280I2C.h>
#include <Wire.h>

#define sda D2
#define scl D1

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

BME280I2C bme(settings);

float temp(NAN), hum(NAN), pres(NAN);
int   maxTryBME        = 10;       // Maximale Versuche für die Verbindung zum BM[E|P]
long  timeSinceLastBM  = 0;
int   BM_DURATION      = 3000;     // Abstand zwischen Messungen am Sensor in ms

void  printBME280(void) {
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
    Serial.println(json);
}

void setup() {
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
  
}

void loop() {

  if (stringComplete) {
    Serial.print("#");
    Serial.print(inputString);
    Serial.println("#");
    
    if(inputString == "BME280"){
        printBME280();
    }else if(inputString == "SENSORS"){
        printBME280();     
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
