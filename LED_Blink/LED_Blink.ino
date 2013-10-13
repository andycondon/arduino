void setup(void) 
{
  // Initialize the digital pin 13 as an output.
  pinMode(13, OUTPUT);
}


void loop(void) 
{
  digitalWrite(13, HIGH);   // set the LED on
  delay(1000);              // wait for a second
  digitalWrite(13, LOW);    // set the LED off
  delay(1000);              // wait for a second
}
