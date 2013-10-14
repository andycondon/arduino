const int BLINK_MILLIS = 50;
const int NUM_LEDS = 6;
const int LEDS[NUM_LEDS] = {13, 12, 11, 10, 9, 8};

int led(int ledNumber)
{
  return LEDS[ledNumber];
}

void blink(int ledNumber, int millisOn)
{
  digitalWrite(led(ledNumber), HIGH);
  delay(millisOn);
  digitalWrite(led(ledNumber), LOW);
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
    blink(led(i), BLINK_MILLIS);
    delay(BLINK_MILLIS);
    blink(led(i), BLINK_MILLIS);
    delay(BLINK_MILLIS);
    blink(led(i), BLINK_MILLIS);
    
    delay(1000);
  }
}
