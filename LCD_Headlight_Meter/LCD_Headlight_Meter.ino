#include <stdarg.h>

int lightPin = 0;  //define a pin for Photo resistor
int ledPin=9;     //define a pin for LED
int backlightPin=6;     //define a pin for LED

// include the library code:
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

char* p(char *fmt, ... ){
        char tmp[128]; // resulting string limited to 128 chars
        va_list args;
        va_start (args, fmt );
        vsnprintf(tmp, 128, fmt, args);
        va_end (args);
        Serial.print(tmp);
        return tmp;
}

void setup()
{
  // set up the LCD's number of columns and rows: 
  lcd.begin(20, 4);
    Serial.begin(9600);  //Begin serial communcation
    pinMode( ledPin, OUTPUT );
    pinMode( backlightPin, OUTPUT );
    
    lcd.setCursor(0, 0);
    lcd.print("Headlight: ");
}

void loop()
{
  int inputValue = analogRead(lightPin) / 4;
  int inputPercentage = ((inputValue * 100) / 255);
  int outputValue = (255 -inputValue);
  int outputPercent = ((outputValue * 100) / 255);
  p("Ambient Light: %d%% Headlight: %d%%\n", inputPercentage, outputPercent);
  lcd.setCursor(11, 0);
  lcd.print("    ");
  lcd.setCursor(11, 0);
  
  analogWrite(backlightPin, inputValue);
  
  
  if (inputPercentage < 85)
  {
    lcd.print(outputPercent);
    analogWrite(ledPin, outputValue);
  }
  else
  {
    lcd.print(0);
    analogWrite(ledPin, 0);
  }
  lcd.print("%");
  
//    Serial.println(analogRead(lightPin)); //Write the value of the photoresistor to the serial monitor.
//    analogWrite(ledPin, analogRead(lightPin)/2);  //send the value to the ledPin. Depending on value of resistor 
                                                //you have  to divide the value. for example, 
                                                //with a 10k resistor divide the value by 2, for 100k resistor divide by 4.
   delay(100); //short delay for faster response to light.
}

