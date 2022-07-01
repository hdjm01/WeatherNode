#include <BME280.h>
#include <BME280I2C.h>
#include <Wire.h>

#define sda D2
#define scl D1

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
int   BM_DURATION      = 5000;     // Abstand zwischen Messungen am Sensor in ms

void  printBME280(void) {
    String json = "{ ";
    json += "\"name\": \"WeatherNode\", ";
    
    json += " {";
    json += " \"name\": \"BME280\"";
    
    json += ", \"Temperatur\":";
    
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
  if (timeSinceLastBM == 0 || (millis() - timeSinceLastBM > BM_DURATION)) {
    timeSinceLastBM = millis();
    bme.read(pres, temp, hum, tempUnit, presUnit);
    printBME280();
  }
}
