/*
  MTCH112.h - Test library for Microchip MTCH112
  Dual-Channel Proximity/Touch Controller
*/

// include this library's description file
#include "Arduino.h"
#include "Mtch112.h"

// include description files for other libraries used (if any)
#include "Wire.h"

// Constructor /////////////////////////////////////////////////////////////////
// Function that handles the creation and setup of instances

MTCH112::MTCH112()
{
Wire.begin();
}

// Public Methods //////////////////////////////////////////////////////////////
// Functions available in Wiring sketches, this library, and other libraries

void MTCH112::Recalibrate() {
  // Clear bit 2 of the CONFIG_CALCON0 register to force recalibration.
  WriteReg(CONFIG_CALCON0,((0x2)));
}

unsigned char MTCH112::ReadReg(unsigned char register_address)
{
   Wire.beginTransmission (MTCH112_I2C_DEFUALT_ADDR); // turn on sending
   Wire.write (register_address); // Write to ADXL345 register map address
   Wire.endTransmission (); // End to send
   Wire.requestFrom (MTCH112_I2C_DEFUALT_ADDR, 1); // Request two bytes for ADXL345
   unsigned char val;
   if (Wire.available () <= 1) // Get <= 2 data
   {
     val = Wire.read ();
   }
}

void MTCH112::WriteReg(unsigned char register_address, unsigned char value)
{
  unsigned char currVal=ReadReg(register_address);
  Serial.print("WAS: ");
  Serial.print(register_address,HEX);Serial.print("=");Serial.print(currVal);
  Serial.print(" changing to ");Serial.println(value);
  if (value != currVal){
     Wire.beginTransmission(MTCH112_I2C_DEFUALT_ADDR);
  Wire.write(WP_BYTE_H);
  Wire.write(WP_BYTE_L);
  Wire.write(register_address); 
  Wire.write(value);     
  Wire.write((WP_BYTE_H ^ WP_BYTE_L ^ value ^ register_address));
  Wire.endTransmission();      // stop transmitting
  }
  else{
    Serial.println("Register already set...skipping EEPROM write.");
  }
 
  delay(EPROM_WRITE_DELAY);
   Serial.print("NOW: ");
   Serial.print(register_address,HEX);Serial.print("=");Serial.println(ReadReg(register_address));
}

void MTCH112::Setup(unsigned int timeout_value, unsigned char outcon_value, unsigned char lpcon_value) 
{
  unsigned char timeout_L_value = (unsigned char) (timeout_value & 0x00ff);
  unsigned char timeout_H_value = (unsigned char) (timeout_value & 0xff00 >> 8);
  WriteReg(CONFIG_TIMEOUT_L,timeout_L_value);  //default = 0xff
  WriteReg(CONFIG_TIMEOUT_H, timeout_H_value);   //default = 0xff
  WriteReg(CONFIG_OUTCON, outcon_value);         //default = 0x0C
  WriteReg(CONFIG_LPCON, lpcon_value);           //default = 0x0C
}
unsigned int MTCH112::ReadData(unsigned char register_address)
{
   Wire.beginTransmission (MTCH112_I2C_DEFUALT_ADDR); // turn on sending
   Wire.write (register_address); // Write to ADXL345 register map address
   Wire.endTransmission (); // End to send
   Wire.requestFrom (MTCH112_I2C_DEFUALT_ADDR, 2); // Request two bytes for ADXL345
   if (Wire.available () <= 2) // Get <= 2 data
   {
  unsigned char bytel = Wire.read();  //check byte order
  unsigned char byteh = Wire.read();
  unsigned int val = (byteh << 8);
  val = val | bytel;
//  Serial.print(bytel);Serial.print(" ");Serial.println(byteh);
  return val;
}
}