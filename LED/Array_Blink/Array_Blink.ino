const unsigned long BLINK_MILLIS = 50;
const int NUM_LEDS = 6;
const int LEDS[NUM_LEDS] = {13, 12, 8, 7, 4, 2};
//                          0   1   2  3  4  5

int led(int ledNumber)
{
  return LEDS[ledNumber];
}

void blink(int ledNumber, int millisOn, int times)
{
  for(int i = 0; i < times; i++)
  {
    int pin = led(ledNumber);
    digitalWrite(pin, HIGH);
    delay(millisOn);
    digitalWrite(pin, LOW);
  }
}

void setup(void) 
{
  for(int i = 0; i < NUM_LEDS; i++)
  {
    pinMode(led(i), OUTPUT);
  }
}

void loop(void) 
{
  for(int i = 0; i < NUM_LEDS; i++)
  {
    blink(i, BLINK_MILLIS, 2);
    delay(BLINK_MILLIS);
  }
  
  for(int i = NUM_LEDS - 1; i >= 0; i--)
  {
    blink(i, BLINK_MILLIS, 2);
    delay(BLINK_MILLIS);
  }
}
