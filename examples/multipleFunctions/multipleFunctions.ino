#include <EE24AA32.h>

EE24AA32 eeprom;
byte* data;

void setup() {

  Serial.begin(115200);
  eeprom.begin(0x50);      

  eeprom.writeAll();  // write all registers with random data

  Serial.println("Reading all 32 bytes blocks of memory. Please wait...");
  delay(2500);
  
  for (int x = 0; x <EEPROM_SIZE; x+= PAGE_SIZE){     // print all EEprom pages
    data = eeprom.readBlock(x); // Read a page of the EEprom 32 bytes 
  
    Serial.print("Address ");
    if ( x == 0x00) { Serial.print("00"); }
    if (( x < 0xFF) && ( x > 0)) { Serial.print("0"); }
    Serial.print(x,HEX);
    Serial.print(" ");

    for (int i = 0; i < PAGE_SIZE; i++) {
        if ( data[i] < 16) { Serial.print("0"); }
        Serial.print(data[i], HEX);
        Serial.print(" ");
        }
    Serial.println();
  }

  data = eeprom.readBlock(0x00); // Read the fist page of the EEprom 32 bytes

  for (int x = 0x20; x <EEPROM_SIZE; x+=PAGE_SIZE){ // Copy the first page data in all pages
      eeprom.writeBlock(x,data);  
      Serial.print("Page ");
      if ( x == 0x00) { Serial.print("00"); }
      if (( x < 0xFF) && ( x > 0)) { Serial.print("0"); }
      Serial.print(x,HEX);
      Serial.print(" wrote");
      Serial.println("");
      }
  Serial.println();
  Serial.println();

  for (int x = 0; x <EEPROM_SIZE; x+= PAGE_SIZE){   // print all EEprom pages
    data = eeprom.readBlock(x); // Read a page of the EEprom 32 bytes
    
    Serial.print("Address ");
    if ( x == 0x00) { Serial.print("00"); }
    if (( x < 0xFF) && ( x > 0)) { Serial.print("0"); }
    Serial.print(x,HEX);
    Serial.print(" ");

    for (int i = 0; i < PAGE_SIZE; i++) {
        if ( data[i] < 16) { Serial.print("0"); }
        Serial.print(data[i], HEX);
        Serial.print(" ");
        }
    Serial.println();

  }
}

void loop() {

}
