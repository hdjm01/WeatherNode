#pragma once

#include "Version.h"

String inputString = "";    
bool stringComplete = false;

void initSerial(){
  inputString.reserve(200);
  Serial.begin(115200);
  Serial.println("\nWeatherNode\n");
  Serial.printf("Version: %s \n", version);
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
