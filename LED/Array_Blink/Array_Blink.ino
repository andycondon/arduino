const unsigned long BLINK_MILLIS = 100;
const int NUM_LEDS = 6;
const int LEDS[NUM_LEDS] = {13, 12, 11, 10, 9, 8};

int led(int ledNumber)
{
  return LEDS[ledNumber];
}

void blink(int ledNumber, int millisOn)
{
  int pin = led(ledNumber);
  digitalWrite(pin, HIGH);
  delay(millisOn);
  digitalWrite(pin, LOW);
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
    blink(i, BLINK_MILLIS);
    delay(BLINK_MILLIS);
    blink(i, BLINK_MILLIS);
    delay(BLINK_MILLIS);
    blink(i, BLINK_MILLIS);
    
    delay(1000);
  }
}
