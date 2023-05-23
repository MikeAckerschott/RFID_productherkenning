#include <MFRC522.h>
#include <SPI.h>
#include <mcp2515.h>
#include <EEPROM.h>

void setup() {
  Serial.begin(9600);  // Initialize serial communication
  randomSeed(analogRead(0));
  RFID_setup();
  CAN_setup();
  ledSetup();
  setupStateMachine();
  softwareTimerSetup();
}

void loop() {


  doStateMachine();
  delay(10);
}