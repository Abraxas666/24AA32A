/*
  Keywords - Arduino library support for 24AA32 EEPROM 
  Author: Abraxas666
  
  This library has been made to easily interface and use the 24AA32 with the Arduino
  This library makes use of the built-in hardware I2C and SPI ports of the microcontroller 
  Some functions required an external SD card to store and read the EEprom dump files
  See the read me file for the connections

*/

#ifndef EE24AA32_H
#define EE24AA32_H
#endif

#define EEPROM_SIZE 4096  // 4 KB
#define PAGE_SIZE     32  // Block

#include "Arduino.h"
#include <Wire.h>

class EE24AA32
{
   public:

      unsigned int  addr;
      uint8_t data;
      uint8_t EEid;
      int id;
      int startAddr;
      String filename;
      byte* dataArr;

      EE24AA32();

      void  begin(byte EEid);

      uint8_t readAddr(unsigned int addr);
      void  writeAddr( unsigned int addr, uint8_t data);
      byte* readBlock(int startAddr);
      byte* writeBlock(int startAddr,byte* dataArray);

      void eraseEEprom();
      void readAll();
      void writeAll();

      bool EEdump(String filename); 
      bool restoreDump(String filename);
      bool readDump(String filename);
   
   private:

      void dumpFilesList();

};

