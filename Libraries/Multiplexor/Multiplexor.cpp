/* ROBORREGOS MAZE 2020.
 * Marlon Romo, Emérico Pedraza, Diego Prado, Grecia Flores.
 * This multiplexor class is to give an ID number
 * to each I2C sensor.
 * To get more information, go to Multiplexor.h file.
*/

#include "Multiplexor.h"

Multiplexor::Multiplexor() {
}

void Multiplexor::tcaselect(const uint8_t number) {
  if (number <= 7){
 
  Wire.beginTransmission(TCAADDR);
  Wire.write(1 << number);
  Wire.endTransmission();  
  }
}