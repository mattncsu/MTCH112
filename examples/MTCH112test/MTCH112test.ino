#include <Mtch112.h>
  MTCH112 myProx=MTCH112();

void setup() {
   Serial.begin (115200); // Initialize the serial port
   delay (100);
   Serial.println ("");


  
  // Longest possible timeout (35s) before auto-recalibration.
   myProx.WriteReg(CONFIG_TIMEOUT_L, 0x03); //was 0xff
   myProx.WriteReg(CONFIG_TIMEOUT_H, 0xff); //was 0x00
  // Set up proximity detection mode (as opposed to touch).
  myProx.WriteReg(CONFIG_OUTCON, 0xC);
  myProx.WriteReg(CONFIG_LPCON, SLEEP_16ms | CLK_16MHZ);
  Serial.print("Prox Thresh=");Serial.println(myProx.ReadReg(CONFIG_PROX_THRESH));
  myProx.WriteReg(CONFIG_PROX_THRESH,8);
}

void loop() {
  Serial.print(myProx.ReadReg(OUTPUT_STATE),BIN);Serial.print(" ");
  Serial.print(myProx.ReadData(OUTPUT_BASELINE0L));Serial.print(" / ");
  Serial.println(myProx.ReadData(OUTPUT_READING0L));
  delay(200);
}
