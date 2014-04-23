#include "utility/debug.h"

void setup(){
  lcd_init();
  
  delay(1000);
  lcd_clear();
  lcd_print("Free RAM: "); lcd_print(getFreeRam());
  
  wifi_init();
}

void loop(){
  lcd_print("test ");
  delay(1000);
}
