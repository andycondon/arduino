void setup(void) 
{
  // Initialize the digital pin 13 as an output.
  pinMode(13, OUTPUT);
}


void loop(void) 
{
  digitalWrite(13, HIGH);
  delay(50);
  digitalWrite(13, LOW);
  delay(50);
  digitalWrite(13, HIGH);
  delay(50);
  digitalWrite(13, LOW);
  delay(05);
  digitalWrite(13, HIGH);
  delay(50);
  digitalWrite(13, LOW);
  delay(1000);
}
