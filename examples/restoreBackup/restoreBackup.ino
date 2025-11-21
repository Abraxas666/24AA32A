#include <EE24AA32.h>
#include <SPI.h>
#include <SD.h>

String fileName = "";

EE24AA32 eeprom;

void setup() {

  Serial.begin(115200);
  eeprom.begin(0x50); 

  if (!SD.begin(0x0A)) {
      Serial.println("Card failed, or not present");
      while (1);
      }

  eeprom.dumpFilesList();

  Serial.println("Insert the name of the backup file to restore:");
  while (fileName.length() == 0) {
    if (Serial.available()) {
      fileName = Serial.readStringUntil('\n'); 
      fileName.trim(); 
    }
  }

  eeprom.restoreDump(fileName);

}

void loop() {
}



