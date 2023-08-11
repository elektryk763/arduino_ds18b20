#include <OneWire.h>

OneWire  ds(4); //pin to sensor

void setup(void)
{
  Serial.begin(9600);
}

void loop(void)
{
  byte i;
  byte present = 0;
  byte data[9];
  byte addr[8];
  float celsius;

  if ( !ds.search(addr))
  {
    ds.reset_search();
    delay(250);
    return;
  }

  ds.reset();
  ds.select(addr);
  ds.write(0x44, 1);

  delay(100);

  present = ds.reset();
  ds.select(addr);
  ds.write(0xBE);

  for ( i = 0; i < 9; i++)
  {
    data[i] = ds.read();
  }

  int16_t raw = (data[1] << 8) | data[0];

  byte cfg = (data[4] & 0x60);
  if (cfg == 0x00) raw = raw & ~7;  
  else if (cfg == 0x20) raw = raw & ~3; 
  else if (cfg == 0x40) raw = raw & ~1; 


  celsius = (float)raw / 16.0;
  Serial.print("  Temperature = ");
  Serial.print(celsius);
  Serial.println(" Celsius, ");
}
