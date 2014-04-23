#include <SoftwareSerial.h>

#define rxPin 4  // rxPin is immaterial - not used - just make this an unused Arduino pin number
#define txPin 14 // pin 14 is analog pin 0, on a BBB just use a servo cable :), see Reference pinMode

SoftwareSerial serial = SoftwareSerial(rxPin, txPin);

void lcd_init(){
  pinMode(txPin, OUTPUT);
  serial.begin(9600);            // 9600 baud is chip comm speed

  lcd_print("?G420");                // set display geometry,  4 x 20 characters in this case
  delay(500);                    // pause to allow LCD EEPROM to program

  lcd_print("?Bff");                 // set backlight to ff hex, maximum brightness
  delay(1000);                   // pause to allow LCD EEPROM to program

  lcd_print("?s6");                  // set tabs to six spaces
  delay(1000);                   // pause to allow LCD EEPROM to program
   
  lcd_print("?D00000000000000000");  // define special characters
  delay(300);                    // delay to allow write to EEPROM
                                 // see moderndevice.com for a handy custom char generator (software app)
  lcd_clear();
  delay(10);                                              
  lcd_print("..."); 

  //crashes LCD without delay
  lcd_print("?D11010101010101010");
  delay(300);

  lcd_print("?D21818181818181818");
  delay(300);

  lcd_print("?D31c1c1c1c1c1c1c1c");
  delay(300);

  lcd_print("?D41e1e1e1e1e1e1e1e");
  delay(300);

  lcd_print("?D51f1f1f1f1f1f1f1f");
  delay(300);

  lcd_print("?D60000000000040E1F");
  delay(300);

  lcd_print("?D70000000103070F1F");
  delay(300);

  lcd_print("?c0");                  // turn cursor off
  delay(300);
   
  lcd_clear();

  delay(1000);

  lcd_clear();
  delay(100);
  delay(3000);

  lcd_cursor(0,00);
}

void lcd_clear(){
  lcd_print("?f");
}

void lcd_print(String data){
  serial.print(data);
}

void lcd_print(int data){
  serial.print(data);
}

void lcd_cursor(String line, String character){
  lcd_print("?x");
  lcd_print(character);
  lcd_print("?y");
  lcd_print(line);
}

//TODO - Ideas for organizing LCD information:
//Task Title
//Status
//Error - possibly combine with Status to have two lines of info
//Global status such as IP, coordinates, temp, etc
