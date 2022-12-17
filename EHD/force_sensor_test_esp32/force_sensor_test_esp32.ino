#include "HX711.h"

// HX711 circuit wiring
const int LOADCELL_DOUT_PIN = 22;
const int LOADCELL_SCK_PIN = 23;

HX711 scale;

void setup() {
  Serial.begin(9600);
  
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  
  if (scale.is_ready()) {
    //scale.tare();
    scale.set_scale();  
  } 
  else {
    Serial.println("HX711 not found.");
  }
}

void loop() {

  if (scale.is_ready()) {
    long reading = scale.get_units(1);
    Serial.print("HX711 reading: ");
    Serial.println(reading);
  } 
  else {
    Serial.println("HX711 not found.");
  }
  delay(1000);
}