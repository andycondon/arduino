#include <LCD.h>

SoftwareSerial serial = SoftwareSerial(rxPin, txPin);

LCD::LCD(){
  pinMode(txPin, OUTPUT);
  serial.begin(9600);            // 9600 baud is chip comm speed

  print("?G420");                // set display geometry,  4 x 20 characters in this case
  delay(500);                    // pause to allow LCD EEPROM to program

  print("?Bff");                 // set backlight to ff hex, maximum brightness
  delay(1000);                   // pause to allow LCD EEPROM to program

  print("?s6");                  // set tabs to six spaces
  delay(1000);                   // pause to allow LCD EEPROM to program
   
  print("?D00000000000000000");  // define special characters
  delay(300);                    // delay to allow write to EEPROM
                                 // see moderndevice.com for a handy custom char generator (software app)
  clear();
  delay(10);                                              
  print("..."); 

  //crashes LCD without delay
  print("?D11010101010101010");
  delay(300);

  print("?D21818181818181818");
  delay(300);

  print("?D31c1c1c1c1c1c1c1c");
  delay(300);

  print("?D41e1e1e1e1e1e1e1e");
  delay(300);

  print("?D51f1f1f1f1f1f1f1f");
  delay(300);

  print("?D60000000000040E1F");
  delay(300);

  print("?D70000000103070F1F");
  delay(300);

  print("?c0");                  // turn cursor off
  delay(300);
   
  clear();

  delay(1000);

  clear();
  delay(100);
  delay(3000);

  cursor(0,0);
  print("?x00?y0");              // cursor to first character of line 0
}

LCD::~LCD(){
  // Nothing to destruct. //TODO What about the serial?
}

void LCD::clear(){
  print("?f");
}

void LCD::print(char[] data){
  serial.print(data);
}

void LCD::cursor(uint8_t line, uint8_t character){
  print("?x");
  print(character);
  print("?y");
  print(line);
}
