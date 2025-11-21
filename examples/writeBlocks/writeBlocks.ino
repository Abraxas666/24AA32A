#include <EE24AA32.h>

EE24AA32 eeprom;
byte data[32] = {0xFF,0xFE,0xFD,0xFC,0xFB,0xFA,0xF9,0xF8,
                 0xF7,0xF6,0xF5,0xF4,0xF3,0xF2,0xF1,0xF0,
                 0xE0,0xD0,0xC0,0xB0,0xA0,0x90,0x80,0x70,
                 0x60,0x50,0x40,0x30,0x20,0x10,0x00,0xAA};
byte* page;
int addr = 0xFE0;

void setup() {

  Serial.begin(115200);
  eeprom.begin(0x50);      

 eeprom.writeBlock(addr,data);  // write the array data values into the eeprom page

 page = eeprom.readBlock(addr); // Read the page of the EEprom 32 bytes

 Serial.print("Address ");      // print the page values to verify if the same of array data
 if ( addr == 0x00) { Serial.print("00"); }
 if (( addr < 0xFF) && ( addr > 0)) { Serial.print("0"); }
 Serial.print(addr,HEX);
 Serial.print(" ");
 for (int x = 0; x <PAGE_SIZE; x++){
    if ( page[x] < 16) { Serial.print("0"); }
    Serial.print(page[x], HEX);
    Serial.print(" ");
    }
 Serial.println();
}

void loop() {

}
