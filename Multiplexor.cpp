/* ROBORREGOS MAZE 2020.
 * This multiplexor class is to give an ID number
 * to each I2C sensor.
 * To get more information, go to Multiplexor.h file.
 * Marlon Romo (MarlonB500).
*/
#include "Multiplexor.h"

Multiplexor::Multiplexor() {
  while (!Serial);
  delay(1000);

  Wire.begin();
  Serial.println("\nTCAScanner ready!");

  for (uint8_t t = 0; t < 8; ++t) {
    tcaselect(t);
    Serial.print("TCA Port #");
    Serial.println(t);

    for (uint8_t addr = 0; addr <= 127; ++addr) {
      if (addr == TCAADDR)
        continue;

      uint8_t data;
      if (!twi_writeTo(addr, &data, 0, 1, 1)) {
        Serial.print("Found I2C 0x");
        Serial.println(addr, HEX);
      }
    }
  }
  Serial.println("\ndone");
}

void Multiplexor::tcaselect(const uint8_t number) {
  if (number > 7)
    return;

  if (number <= 7) {
  Wire.beginTransmission(TCAADDR);
  Wire.write(number << 7);
  Wire.endTransmission();
  delay(kWaitToSend);
  }
}
