#include <EEPROM.h>


void setup() {
  EEPROM.write(0, 84);
  EEPROM.write(1, 83);
  EEPROM.write(2, 123);
  EEPROM.write(3, 51);
  EEPROM.write(4, 51);
  EEPROM.write(5, 80);
  EEPROM.write(6, 82);
  EEPROM.write(7, 48);
  EEPROM.write(8, 77);
  EEPROM.write(9, 95);
  EEPROM.write(10, 105);
  EEPROM.write(11, 53);
  EEPROM.write(12, 95);
  EEPROM.write(13, 102);
  EEPROM.write(14, 117);
  EEPROM.write(15, 110);
  EEPROM.write(16, 95);
  EEPROM.write(17, 33);
  EEPROM.write(18, 125);
}

void loop() {}
