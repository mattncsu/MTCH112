/*
  MTCH112.h - Test library for Microchip MTCH112
  Dual-Channel Proximity/Touch Controller
*/

// ensure this library description is only included once
#ifndef Mtch112
#define Mtch112

// include types & constants of Wiring core API
//general infomation
#define EPROM_WRITE_DELAY    0xC8 //200ms

//i2c configuration information 
#define MTCH112_I2C_DEFUALT_ADDR  0x73
#define WRITE_PROTECT_BYTE_H  (unsigned char 0x55)
#define WRITE_PROTECT_BYTE_L  (unsigned char 0xAA)

//Configuration Registers
#define CONFIG_RESET_CALIB  0x00
#define CONFIG_OUTCON   0x01
#define CONFIG_CALCON0    0x02
#define CONFIG_CALCON1    0x03
#define CONFIG_ADACQ0   0x04
#define CONFIG_ADACQ1   0x05
#define CONFIG_LPCON    0x06
#define CONFIG_PRESS_THRESH 0x07
#define CONFIG_PROX_THRESH  0x08
#define CONFIG_TIMEOUT_L  0x09
#define CONFIG_TIMEOUT_H  0x0A
#define CONFIG_I2CADDR    0x0B

//Read/Output Registers, readonly
#define OUTPUT_STATE    0x80
#define OUTPUT_READING0L  0X81
#define OUTPUT_READING0H  0X82
#define OUTPUT_READING1L  0X83
#define OUTPUT_READING1H  0X84
#define OUTPUT_BASELINE0L 0x85
#define OUTPUT_BASELINE0H 0x86
#define OUTPUT_BASELINE1L 0X87
#define OUTPUT_BASELINE1H 0x88

#define SLEEP_1ms   0x00
#define SLEEP_2ms   0x02
#define SLEEP_4ms   0x04
#define SLEEP_8ms   0x06
#define SLEEP_16ms  0x08
#define SLEEP_32ms  0x0A
#define SLEEP_64ms  0x0C
#define SLEEP_128ms 0x0E
#define SLEEP_256ms 0x10
#define SLEEP_512ms 0x12
#define SLEEP_1s    0x14
#define SLEEP_2s    0x16
#define SLEEP_4s    0x18
#define SLEEP_8s    0x1A
#define SLEEP_16S   0x1C
#define SLEEP_32s   0x1E
#define SLEEP_64s   0x20
#define SLEEP_128s  0x22
#define SLEEP_256s  0x24
#define CLK_32MHZ   0x01
#define CLK_16MHZ   0x00

#define WP_BYTE_H 0x55 //unlock sequence (see Fig2-10 in datasheet)
#define WP_BYTE_L 0xAA

#define I2C_TIMEOUT 1000

// library interface description
class MTCH112
{
  // user-accessible "public" interface
  public:
	MTCH112();
	void Recalibrate();
	unsigned char ReadReg(unsigned char register_address);
	void WriteReg(unsigned char register_address, unsigned char value);
	void Setup(unsigned int timeout_value, unsigned char outcon_value, unsigned char lpcon_value);
	unsigned int ReadData(unsigned char register_address);
	
  // library-accessible "private" interface
  private:

};

#endif
