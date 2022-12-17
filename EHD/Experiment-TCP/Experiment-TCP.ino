/*
  Modbus RTU Server for the static EHD thrust experiments

*/

#include <ArduinoRS485.h> // ArduinoModbus depends on the ArduinoRS485 library
#include <ArduinoModbus.h>
#include "HX711.h"
#include <WiFi.h>
#include <ESPmDNS.h>

#define LOADCELL_DOUT_PIN  22
#define LOADCELL_SCK_PIN  23

#define VHV_PIN 35
#define IHV_PIN 36

#define MONITOR_PIN 18
#define WARNING_PIN 19

const char* ssid = "ABRACADABRA-2G";
const char* password = "OPENSESAME";

const long LOADCELL_OFFSET = -139433;
const long LOADCELL_DIVIDER = 192; // 1kg cell
long loadcell_reading;

HX711 force_sensor;
ModbusTCPServer ModbusServer;

void setup() {
  Serial.begin(9600);
  pinMode(MONITOR_PIN, OUTPUT);
  pinMode(WARNING_PIN, OUTPUT);
  digitalWrite(MONITOR_PIN,1);
  digitalWrite(WARNING_PIN,1);
  delay(100);
  
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("Connecting ");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (MDNS.begin("EHD_RTU")) {
    Serial.println("MDNS responder started");
  }
  
  force_sensor.begin( LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN );
  //force_sensor.set_offset(LOADCELL_OFFSET);
  force_sensor.set_scale();

  flash();
  flash();

  // Serial.println("Modbus Server");
  // start the Modbus server
  if (!ModbusServer.begin()) {
    Serial.println("Failed to start Modbus RTU Server");
    warn();
    while (1) {
    }
  }
  
  // configure 3 holding registers starting at 0x00
  ModbusServer.configureHoldingRegisters(0x00, 3);
  
}

void loop() {
  // flash();  
  // poll for Modbus RTU requests and update the holding registers
  ModbusServer.poll();
  loadcell_reading = force_sensor.get_units(1);
  loadcell_reading = loadcell_reading + LOADCELL_OFFSET;
  if (loadcell_reading < 0) loadcell_reading = 0;
  // linear scaling of the "units" output, should apply the offset and scale to the driver directly
  ModbusServer.holdingRegisterWrite( 2, (unsigned int)( loadcell_reading / LOADCELL_DIVIDER ) ); // 0.1g
  ModbusServer.holdingRegisterWrite( 0, analogRead(VHV_PIN) );
  ModbusServer.holdingRegisterWrite( 1, analogRead(IHV_PIN) );
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
