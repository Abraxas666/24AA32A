#include <EE24AA32.h>

EE24AA32 eeprom;

void setup() {
  
  Serial.begin(115200);
  eeprom.begin(0x50);  

  eeprom.writeAll(); // write all addesses with random values

  }

void loop() {

}
