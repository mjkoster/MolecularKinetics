/*
  Modbus RTU Server for the static EHD thrust experiments

*/

#include <ArduinoRS485.h> // ArduinoModbus depends on the ArduinoRS485 library
#include <ArduinoModbus.h>
#include "HX711.h"

#define LOADCELL_DOUT_PIN  6
#define LOADCELL_SCK_PIN  5

#define VHV_PIN A1
#define IHV_PIN A0

#define MONITOR_PIN 10
#define WARNING_PIN 16


const long LOADCELL_OFFSET = 105000;
const long LOADCELL_DIVIDER = 363;
long loadcell_reading;
int vhv_reading, ihv_reading;

const int ilookup[12] = {0.00, 0.00, 0.01, 0.03, 0.06, 0.10, 0.15, 0.22, 0.29, 0.38, 0.48, 0.66};
const int flookup[12] = {0.00, 0.00, 0.01, 0.10, 0.25, 0.42, 0.56, 0.67, 0.71, 0.70, 0.63, 0.00};

HX711 force_sensor;

void setup() {
  //  Serial.begin(9600);
  pinMode(MONITOR_PIN, OUTPUT);
  pinMode(WARNING_PIN, OUTPUT);
  digitalWrite(MONITOR_PIN,1);
  digitalWrite(WARNING_PIN,1);
  delay(100);

  force_sensor.begin( LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN );
  //force_sensor.set_offset(LOADCELL_OFFSET);
  force_sensor.set_scale();

  flash();
  flash();

  // Serial.println("Modbus RTU Server");
  // start the Modbus RTU server
  if (!ModbusRTUServer.begin(2, 9600)) {
    // Serial.println("Failed to start Modbus RTU Server");
    warn();
    while (1) {
    }
  }
  
  // configure 3 holding registers starting at 0x00
  ModbusRTUServer.configureHoldingRegisters(0x00, 3);
  
}

void loop() {
  // flash();  
  // poll for Modbus RTU requests and update the holding registers
  ModbusRTUServer.poll();
  loadcell_reading = force_sensor.get_units(1);
  loadcell_reading = loadcell_reading + LOADCELL_OFFSET;
  if (loadcell_reading < 0) loadcell_reading = 0;
  // linear scaling of the "units" output, should apply the offset and scale to the driver directly
  // ModbusRTUServer.holdingRegisterWrite( 2, (unsigned int)( loadcell_reading / LOADCELL_DIVIDER ) ); // 0.1g
  ModbusRTUServer.holdingRegisterWrite( 0, analogRead(VHV_PIN) );
  // ModbusRTUServer.holdingRegisterWrite( 1, analogRead(IHV_PIN) );
  ModbusRTUServer.holdingRegisterWrite( 1, analogRead(IHV_PIN) );
  ModbusRTUServer.holdingRegisterWrite( 2, (unsigned int)( loadcell_reading / LOADCELL_DIVIDER ) ); // 0.1g
}

void flash() {
  digitalWrite(MONITOR_PIN,0);
  delay(50);
  digitalWrite(MONITOR_PIN,1);
  delay(50);
}

void warn() {
    digitalWrite(WARNING_PIN,0);
}
