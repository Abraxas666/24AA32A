#include <EE24AA32.h>

EE24AA32 eeprom;
byte* data;

void setup() {

  Serial.begin(115200);
  eeprom.begin(0x50);      
  
  Serial.println("Reading all 32 bytes blocks of memory. Please wait...");
  delay(2500);
  
  for (int x = 0; x <EEPROM_SIZE; x+= PAGE_SIZE){
    data = eeprom.readBlock(x); // Read the fist page of the EEprom 32 bytes
   // printData(data);
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
