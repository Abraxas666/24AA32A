#include <EE24AA32.h>
#include <SPI.h>
#include <SD.h>

EE24AA32 eeprom;
String fileName = "";

void setup() {
  Serial.begin(115200);
  eeprom.begin(0x50);     


  if (!SD.begin(0x0A)) {
      Serial.println("Card failed, or not present");
      while (1);
      }
  
  Serial.println("Insert the backup file name ( max 8 characters without extension! ):");
  while (fileName.length() == 0) {
    if (Serial.available()) {
      fileName = Serial.readStringUntil('\n'); 
      fileName.trim(); 
    }
  }

  eeprom.EEdump(fileName); // create dump file
  eeprom.readDump(fileName); // read the dump file created

}

void loop() {

}
