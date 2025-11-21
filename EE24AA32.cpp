/*
  Keywords - Arduino library support for 24AA32 EEPROM 
  Author: Abraxas666
  
  This library has been made to easily interface and use the 24AA32 with the Arduino
  This library makes use of the built-in hardware I2C and SPI ports of the microcontroller 
  Some functions required an external SD card to store and read the EEprom dump files
  See the read me file for the connections

*/


#include "EE24AA32.h"
#include <Wire.h>
#include <SPI.h>
#include <SD.h>

#define EEPROM_SIZE 4096  // 4 KB
#define PAGE_SIZE 32      // Block dimension

File EEpromDump;

EE24AA32::EE24AA32(){

}

void EE24AA32::begin(byte EEid){
  id = EEid;
  Wire.begin();
}

uint8_t EE24AA32::readAddr(unsigned int addr)
{
  Wire.beginTransmission(id);
  Wire.write((addr >> 8) & 0xFF);
  Wire.write(addr & 0xFF);
  byte error = Wire.endTransmission();
  if (error != 0) {
    Serial.print("Error reading I2C: ");
    Serial.println(error);
    return 0xFF;
  }

  Wire.requestFrom(id, 1);
  if (Wire.available()) {
    return Wire.read();
  }
  return 0xFF;

}

void EE24AA32::writeAddr(unsigned int addr, uint8_t data)
{
  Wire.beginTransmission(id);
  Wire.write((addr >> 8) & 0xFF);
  Wire.write(addr & 0xFF);
  Wire.write(data);
  byte error = Wire.endTransmission();
  if (error != 0) {
    Serial.print("Error writing I2C: ");
    Serial.println(error);
  }
  delay(10); // Wait till completition

}

byte* EE24AA32::readBlock(int startAddr)
{
 if (startAddr + PAGE_SIZE > EEPROM_SIZE) { // Avoid overflow
    Serial.println("Starting address too high! Buffer shifted automatically to the last eeprom page readable");
    startAddr = 0xFDF;
 }
  static byte buffer[PAGE_SIZE]; 

  Wire.beginTransmission(id);
  Wire.write((byte)(startAddr >> 8));   // High byte
  Wire.write((byte)(startAddr & 0xFF)); // Low byte
  Wire.endTransmission();

  // Data request
  Wire.requestFrom(id, PAGE_SIZE);

  uint8_t i = 0;
  while (Wire.available()) {
    buffer[i++] = Wire.read();
  }

  return buffer; 

}

void EE24AA32::eraseEEprom() {
  Serial.println("Erasing EEprom, set all addresses to 0xFF...Please wait");
  for (unsigned int i = 0; i < EEPROM_SIZE; i++) {
    writeAddr(i, 0xFF);
    Serial.print("Address ");
    Serial.print(i,HEX);
    Serial.println(" erased");
    }
  Serial.println("Operation complete!");
}

bool EE24AA32::EEdump(String filename) {
  
    filename += ".bin";

    // Delete file if existing
    SD.remove(filename);

    // Create new file
    File EEpromDump = SD.open(filename, FILE_WRITE);
    if (!EEpromDump) {
        Serial.println("File open error!");
        return false;
    }

    Serial.println("Start EEPROM dump...");
    uint16_t addr = 0;
    byte pageBuffer[PAGE_SIZE]; // 32 bytes

    while (addr < 4096) {
        Wire.beginTransmission(id);
        Wire.write((byte)(addr >> 8));
        Wire.write((byte)(addr & 0xFF));
        Wire.endTransmission();

        Wire.requestFrom(id, PAGE_SIZE);
        uint8_t i = 0;
        while (Wire.available() && i < PAGE_SIZE) {
            pageBuffer[i++] = Wire.read();
        }

        if (i != PAGE_SIZE) {
            Serial.println("I2C read error!");
            EEpromDump.close();
            return false;
        }

        EEpromDump.write(pageBuffer, PAGE_SIZE);
        addr += PAGE_SIZE;
    }

    EEpromDump.close();
    Serial.println("Dump file created!");
  
    return true;
}


bool EE24AA32::restoreDump(String filename) {

    filename += ".bin";
    uint8_t error = 0;  

    File dumpFile = SD.open(filename, FILE_READ);
    if (!dumpFile) {
        Serial.println("Error file not found!");
        return false;
    }

    Serial.println("Start EEPROM restore...");
    uint16_t addr = 0;
    byte pageBuffer[PAGE_SIZE];

    while (addr < EEPROM_SIZE && dumpFile.available()) {
        uint8_t i = 0;
        
        // read one page of the dump file
        while (i < PAGE_SIZE && dumpFile.available()) {
            pageBuffer[i++] = dumpFile.read();
        }

        // Write one page in the eeprom
        Wire.beginTransmission(0x50);
        Wire.write((byte)(addr >> 8));    // High byte
        Wire.write((byte)(addr & 0xFF));  // Low byte
        Wire.write(pageBuffer, i);
        Wire.endTransmission();

        delay(10); //Waiting for eeprom write

        Serial.print("Written Addr 0x");
        Serial.print(addr, HEX);
        Serial.print(" - ");
        Serial.print(i);
        Serial.println(" bytes");

        addr += PAGE_SIZE;
    }

    dumpFile.close();
    Serial.println("Restore completed!");

    Serial.println("Starting progam verify, please wait....");

    dumpFile = SD.open(filename, FILE_READ);

    while (dumpFile.available()) {
      for (int i = 0; i < EEPROM_SIZE && dumpFile.available(); i++) {
            byte b = dumpFile.read();
            data = readAddr(i);
            if ( data != b) { error += 1;}
      }
    }

    dumpFile.close();
    if (error) { Serial.println( "Error found,verify failed!!"); }
    else { Serial.println( "Program verify complete without errors!!"); }

    return error;
}

void EE24AA32::readAll() {

      Serial.println("Reading EEPROM 24AA32A...");
      delay(2000);
      for (int x = 0; x <EEPROM_SIZE; x+= PAGE_SIZE){
            dataArr = readBlock(x); // Read a page of the EEprom 32 bytes
            Serial.print("Address ");
            if ( x == 0x00) { Serial.print("00"); }
            if (( x < 0xFF) && ( x > 0)) { Serial.print("0"); }
            Serial.print(x,HEX);
            Serial.print(" ");
      for (int i = 0; i < PAGE_SIZE; i++) {
            if ( dataArr[i] < 16) { Serial.print("0"); }
            Serial.print(dataArr[i], HEX);
            Serial.print(" ");
            }
          Serial.println();
          }
      Serial.println("Reading complete!");
}

void EE24AA32::writeAll() {
  Serial.println("Writing EEPROM 24AA32A with random values...");
  delay(2000);

  for (unsigned int i = 0; i < EEPROM_SIZE; i++) {
      byte value = random (0,256);
      writeAddr(i, value);
      Serial.print("Address ");
      Serial.print(i,HEX);
      Serial.print(" written with data ");
      Serial.println(value,HEX);
    }

  Serial.println("Writing complete! All bytes set!");
  }

  void EE24AA32::dumpFilesList() {
      int numTabs = 0;

      File root = SD.open("/");

      Serial.println("List of backup files");
      Serial.println();

      while (true) {
          File entry = root.openNextFile();
          if (!entry) {
            break;
          }
          for (int i = 0; i < numTabs; i++) {
            Serial.print('\t');
          }
          Serial.print(entry.name());
          Serial.print("\t");
          Serial.println(entry.size());
          entry.close();
        }
      
      numTabs = 0;
      Serial.println();
  
  }

  bool EE24AA32::readDump(String filename){
      Serial.println("Reading file, please wait..");
      Serial.println("");
      delay(2500);

      filename += ".bin";

      File dataFile = SD.open(filename);
      if (!dataFile) {
        Serial.println("File error!");
        return;
      }

      while (dataFile.available()) {
          Serial.print("Addr 0x");
          if (addr < 0x10) Serial.print("0"); 
          if (addr < 0x100) Serial.print("0"); 
          Serial.print(addr, HEX);
          Serial.print(": ");

          for (uint8_t i = 0; i < PAGE_SIZE && dataFile.available(); i++) {
            byte b = dataFile.read();
            if (b < 0x10) Serial.print("0"); 
            Serial.print(b, HEX);
            Serial.print(" ");
          }

          Serial.println();
          addr += PAGE_SIZE;
          }

      dataFile.close();
      Serial.println("Operation complete! ");
  }       
  
  byte* EE24AA32::writeBlock(int startAddr,byte* dataArray)  {

      if (startAddr + PAGE_SIZE > EEPROM_SIZE) { // Avoid overflow
        Serial.println("Starting address too high! Buffer shifted automatically to the last eeprom page writable");
        startAddr = 0xFDF;
        }

      for (int x = 0; x <PAGE_SIZE; x++){
         writeAddr(startAddr,dataArray[x]);
         startAddr += 1;
         }  

   }     
  