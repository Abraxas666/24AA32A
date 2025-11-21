# 24AA32 EEPROM library for Arduino family v1.0.0 
Author: Abraxas666

The library includes the main functionalities to read and write data in the EEprom 24AA32
Additionally some functions have been added to store,read and restore dump file from/into the EEprom and an externa SD card
All the example included have been tested only on arduino Uno, but should easily work with other types of Arduino boards and ESP32 as well ( to be tested! )

## CONNECTIONS

| Component   | Pin       | Arduino UNO |
|-------------|-----------|-------------|
| EE24AA32    | SCL       | A4          |
| EE24AA32    | SDA       | A5          |
| EE24AA32    | VCC       | 5V          |
| EE24AA32    | GND       | GND         |
| EE24AA32    | WP        | GND         |
| SD CARD     | SCK       | 13          |
| SD CARD     | MISO      | 12          |
| SD CARD     | MOSI      | 11          |
| SD CARD     | CS        | 10          |
| SD CARD     | GND       | GND         |
| SD CARD     | VCC       | 5V          |


## Bill of Materials (BOM)

| Qty | Component                                | Description                                                                                                      | Supplier   | Link                                                                 |
|-----|------------------------------------------|------------------------------------------------------------------------------------------------------------------|------------|----------------------------------------------------------------------|
| 1   | EEPROM 24AA32 (5-pin version)           | EEPROM I²C, default address `0x50`. For multiple EEPROMs, use versions with A0, A1, A2 pins (up to 8 devices).  | RS Online  | Buy Here |
| 1   | SOT23 to DIP10 Adapter                  | Adapter to mount EEPROM on a board for easy MCU connection (prototype use only).                                | Amazon     | Buy Here |
| 2   | 1/4 Watt Resistors                      | Pull-up resistors for SCL and SDA pins.                                                                         | AliExpress | Buy Here |
| 1   | Micro SD TF Card Storage Expansion Board| Storage expansion board for Arduino (SPI interface).                                                            | AliExpress | Buy Here |

#NOTE!! 
#SCL and SDA pins must be pulled up to 5V with resistors. 10kohm and 3.3kohm resistors have been tested 
The IC used is a SOT-23 5 pins version! for the version with more pins, with A0,A1,A2 to select diffente EEprom IDs, refer to the datasheet

The examples read_write, readBlocks, writeBlocks, readEEprom, writeEEprom, eraseEEprom, can be used indpendenty without the SD card attached to the Arduino.

The SD card is required for the examples, CreateDumpFile, readBackup, restoreBackup.


