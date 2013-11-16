void setup(void) 
{
  pinMode(13, OUTPUT);
  pinMode(12,OUTPUT);
  pinMode(11,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(9,OUTPUT);
  pinMode(8,OUTPUT);
}

void blink(int pin)
{
  digitalWrite(pin, HIGH);
  delay(100);
  digitalWrite(pin, LOW);
}

void loop(void) 
{
  blink(13);
  
  blink(13);
  blink(12);
  
  blink(13);
  blink(12);
  blink(11);
  
  blink(13); 
  blink(12);
  blink(11);
  blink(10);
 
  blink(13);
  blink(12);
  blink(11);
  blink(10);
  blink(9);
  
  blink(13);
  blink(12);
  blink(11);
  blink(10);
  blink(9);
  blink(8);
}

