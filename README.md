# 24AA32 EEPROM library for Arduino family v1.0.0 
Author: Abraxas666

The library includes the main functionalities to read and write data in the EEprom 24AA32
Additionally some functions have been added to store,read and restore dump file from/into the EEprom and an externa SD card
All the example included have been tested only on arduino Uno, but should easily work with other types of Arduino boards and ESP32 as well ( to be tested! )

CONNECTIONS:

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

BOM: 

- EEPROM 24AA32 5 pins version ( see the datasheet in the documentation ). The 5 pins version has a default address 0x50, if more than 1 eeprom is required in your projects, choose a different version.
  By means of the additional PINs A0,A1,A2 is possible to modify the EEprom address and connect up to 8 different EEproms to the I2C bus.

  https://uk.rs-online.com/web/p/eeprom/8234539?searchId=3268a2c8-6259-465f-82ed-c313d3e2e8e3

- SOT23 TO DIP10 ADAPTER ( used to install the EEProm on a board and easily connect it to the MCU, only for prototype scope ) 

  https://www.amazon.it/-/en/Aihasd-Pieces-Plate-Adapter-SOT23/dp/B016K1J22E/ref=sr_1_5?crid=18PHMLMUPH6UC&dib=eyJ2IjoiMSJ9.uDpveZq6-M6_8NNbncgvpEQkkogOIsfVNjTGd5SL0WWvRxGHNfYPH7SKUYqSDkxP6XvkzA8-TYinopI1Yi4SCw1NPMxjXtS-_l07mCv0YV_S9VOtMZZmodJPi6Nld6o1P0MTDwrqTICVA-OUauy-n2NQamudsKWPf94xs_SU69A.JeVJFZDFNZd17DPvVuXGOUUAhb7_ParCRsjNDsHP-64&dib_tag=se&keywords=sot23+to+dip10&qid=1763711577&sprefix=sot23+to+dip10%2Caps%2C82&sr=8-5

-  1/4 watt resistor, used to pullup the SCL and SDA pins

   https://it.aliexpress.com/item/32659058582.html?spm=a2g0o.productlist.main.7.6fc14146bFxcOI&algo_pvid=ac830a57-4669-4375-9d6d-c96487f6cdca&algo_exp_id=ac830a57-4669-4375-9d6d-c96487f6cdca-6&pdp_ext_f=%7B%22order%22%3A%2294%22%2C%22eval%22%3A%221%22%2C%22fromPage%22%3A%22search%22%7D&pdp_npi=6%40dis%21EUR%211.69%210.88%21%21%211.90%210.99%21%40211b655217637123858013162e4f8d%2165446466021%21sea%21IT%210%21ABX%211%210%21n_tag%3A-29910%3Bd%3A11bd30dd%3Bm03_new_user%3A-29895%3BpisId%3A5000000190964043&curPageLogUid=qVvoBmv0zZKc&utparam-url=scene%3Asearch%7Cquery_from%3A%7Cx_object_id%3A32659058582%7C_p_origin_prod%3A


- Micro SD TF Card Storage Expansion Board Memory Shield Module SPI For Arduino

  https://it.aliexpress.com/item/1005005942931651.html?spm=a2g0o.productlist.main.29.78e82907Vy58g3&algo_pvid=17a8d506-1c17-4e71-8685-23a9bbddc5d2&algo_exp_id=17a8d506-1c17-4e71-8685-23a9bbddc5d2-28&pdp_ext_f=%7B%22order%22%3A%2213%22%2C%22eval%22%3A%221%22%2C%22fromPage%22%3A%22search%22%7D&pdp_npi=6%40dis%21EUR%211.24%211.18%21%21%219.97%219.51%21%40211b61ae17637121157654030e383a%2112000034959556654%21sea%21IT%210%21ABX%211%210%21n_tag%3A-29910%3Bd%3A11bd30dd%3Bm03_new_user%3A-29895&curPageLogUid=aU2y6tlgRb0V&utparam-url=scene%3Asearch%7Cquery_from%3A%7Cx_object_id%3A1005005942931651%7C_p_origin_prod%3A



#NOTE!! 
#SCL and SDA pins must be pulled up to 5V with resistors. 10kohm and 3.3kohm resistors have been tested 
The IC used is a SOT-23 5 pins version! for the version with more pins, with A0,A1,A2 to select diffente EEprom IDs, refer to the datasheet

The examples read_write, readBlocks, writeBlocks, readEEprom, writeEEprom, eraseEEprom, can be used indpendenty without the SD card attached to the Arduino.

The SD card is required for the examples, CreateDumpFile, readBackup, restoreBackup.


