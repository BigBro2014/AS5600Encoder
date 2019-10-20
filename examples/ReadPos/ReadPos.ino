

#include <Arduino.h>

#include "AS5600Encoder.h"


AS5600Encoder enc(PA0, false);


void setup()
{
  Serial.begin(115200);  
}


void loop()
{
  static uint32_t i = 0;

//  Serial.println(i);

  delay(1);

  enc.update();

  if (++i >= 1024)
  {
    i = 0;

    Serial.print(F("encoder: "));
    Serial.print(enc.getEncoderVal());
    
    Serial.print(F(", absolute pos: "));
    Serial.println(enc.getAbslutePos());
  }
}
