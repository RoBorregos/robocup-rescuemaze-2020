#include "Multiplexor.h"

Multiplexor::Multiplexor(){}

void Multiplexor::tcaselect(int number)
{
  if (number > 7)
    return;

  Wire.beginTransmission(TCAADDR);
  Wire.write(1 << number);
  Wire.endTransmission();
  delay(kWaitToSend);
}

void Multiplexor::setup()
{
    while (!Serial);
    delay(1000);
 
    Wire.begin();
    
    Serial.begin(115200);
    Serial.println("\nTCAScanner ready!");
    
    for (uint8_t t=0; t<8; t++) {
      tcaselect(t);
      Serial.print("TCA Port #"); Serial.println(t);
 
      for (uint8_t addr = 0; addr<=127; addr++) {
        if (addr == TCAADDR) continue;
      
        uint8_t data;
        if (! twi_writeTo(addr, &data, 0, 1, 1)) {
           Serial.print("Found I2C 0x");  Serial.println(addr,HEX);
        }
      }
    }
    Serial.println("\ndone");
}