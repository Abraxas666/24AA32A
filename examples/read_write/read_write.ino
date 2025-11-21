#include <EE24AA32.h>

EE24AA32 eeprom;
uint8_t data;

void setup() {

  Serial.begin(115200);
  eeprom.begin(0x50);      
  
  Serial.println("Writing value 111 in the address 0x0000...");
  eeprom.writeAddr(0x0000,111 );

  Serial.println("Reading first address ");
  data = eeprom.readAddr(0x0000);
  Serial.print("Address Data is in DEC: ");
  Serial.println(data);
  Serial.print("Address Data is in HEX: 0x");
  Serial.println(data, HEX);

  Serial.println("Reading last address ");
  data = eeprom.readAddr(0xFFF);
  Serial.print("Address Data is in DEC: ");
  Serial.println(data);
  Serial.print("Address Data is in HEX: 0x");
  Serial.println(data, HEX);
  }

void loop() {

}
