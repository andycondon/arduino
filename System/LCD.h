#ifndef LCD_H
#define LCD_H

#include <SoftwareSerial.h>

#define rxPin 4  // rxPin is immaterial - not used - just make this an unused Arduino pin number
#define txPin 14 // pin 14 is analog pin 0, on a BBB just use a servo cable :), see Reference pinMode

class LCD{
  public:
  LCD();
  ~LCD();
  void clear();
  void print(char[] data);
  void cursor(uint8_t line, uint8_t character);
};

#endif
