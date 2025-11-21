# 24AA32 EEPROM library for Arduino family v1.0.0 
Author: Abraxas666

The library includes the main functionalities to read and write data in the EEprom 24AA32. 
Additionally some functions have been added to create,read and restore dump files from the EEprom to the SD card and vice versa.
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

| Qty | Component                                | Description                                                                                                      |
|-----|------------------------------------------|------------------------------------------------------------------------------------------------------------------|
| 1   | EEPROM 24AA32 (5-pin version)           | EEPROM I²C, default address `0x50`.                                                                             |
| 1   | SOT23 to DIP10 Adapter                  | Adapter to mount EEPROM on a board for easy MCU connection (prototype use only).                                |
| 2   | 1/4 Watt Resistors                      | Pull-up resistors for SCL and SDA pins.                                                                         |
| 1   | Micro SD TF Card Storage Expansion Board| Storage expansion board for Arduino (SPI interface).                                                            |


- **SCL and SDA pins must be pulled up to 5V with resistors.**  
  Tested values: `10 kΩ` and `3.3 kΩ`.

- **The IC used is a SOT-23 5-pin version.**  
  For versions with more pins (A0, A1, A2) to select different EEPROM IDs, refer to the datasheet.

---

### ✅ Examples without SD card
The following examples can be used independently **without the SD card attached to the Arduino**:
- `read_write`
- `readBlocks`
- `writeBlocks`
- `readEEprom`
- `writeEEprom`
- `eraseEEprom`

---

### ✅ Examples requiring SD card
The SD card is required for these examples:
- `CreateDumpFile`
- `readBackup`
- `restoreBackup`


