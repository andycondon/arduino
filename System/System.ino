#include "utility/debug.h"

void setup()
{
  lcd_init();
  
  delay(1000);
  lcd_clear();
  lcd_print("Free RAM: "); lcd_print(getFreeRam());
  
  wifi_init();
}

void loop()
{
  wifi_print_data_to_LCD();
}
