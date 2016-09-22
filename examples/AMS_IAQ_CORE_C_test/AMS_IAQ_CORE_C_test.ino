#include <Wire.h>
#include "AMS_IAQ_CORE_C.h"

AMS_IAQ_CORE_C iaqcore;

void setup(void){
      Serial.begin(115200);
      Serial.println("AMS_IAQ_CORE_C Test");
      Wire.begin();
      
      // initialize the slot select pins to "not selected"
      pinMode(7, OUTPUT);  digitalWrite(7, LOW);
      pinMode(9, OUTPUT);  digitalWrite(9, LOW);
      pinMode(10, OUTPUT); digitalWrite(10, LOW);      
      digitalWrite(7, HIGH); // select slot                   
}

void loop(void){
  if(!iaqcore.update()){
    Serial.println("Update Failed!");
  }
  
  for(uint8_t ii = 0; ii < 10; ii++){
    Serial.print("0x");
    if(iaqcore.data[ii] < 16){
      Serial.print("0");
    }
    Serial.print(iaqcore.data[ii], HEX);
    
    if(ii != 9){
      Serial.print(", ");
    }
  }
  Serial.println();
  
  Serial.print("Status: ");
  switch(iaqcore.getStatus()){
  case AMS_IAQ_CORE_C_STATUS_BUSY:
    Serial.println("Busy");
    break;
  case AMS_IAQ_CORE_C_STATUS_OK:
    Serial.println("OK");
    break;
  case AMS_IAQ_CORE_C_STATUS_ERROR:
    Serial.println("Error");
    break;
  case AMS_IAQ_CORE_C_STATUS_WARMING_UP:
    Serial.println("Warming Up");
    break;  
  default:
    Serial.print("Undefined Code: ");
    Serial.println(iaqcore.getStatus(), HEX);
    break;                
  }
  
  Serial.print("Resistance [ohms]: ");
  Serial.println(iaqcore.getResistanceOhms());
  
  Serial.print("CO2 Equivalent [ppm]: ");
  Serial.println(iaqcore.getCO2EquivalentPPM());

  Serial.print("TVOC Equivalent [ppb]: ");
  Serial.println(iaqcore.getTVOCEquivalentPPB());    

  delay(1000);  
}
