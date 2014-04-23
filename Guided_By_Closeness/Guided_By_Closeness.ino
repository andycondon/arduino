#include "types.h"

int E1 = 5;    //M1 Speed Control
int E2 = 6;    //M2 Speed Control
int M1 = 4;    //M1 Direction Control
int M2 = 7;    //M1 Direction Control

int FULL_POWER = 100;
int HALF_POWER = 60;
int QUARTER_POWER = 40;
int NO_POWER = 0;

char* p(char *fmt, ... ){
  char tmp[128]; // resulting string limited to 128 chars
  va_list args;
  va_start (args, fmt );
  vsnprintf(tmp, 128, fmt, args);
  va_end (args);
  Serial.print(tmp);
  return tmp;
}
void stop(void)
{
  digitalWrite(E1,LOW);   
  digitalWrite(E2,LOW);      
}   
void advance(char leftPower,char rightPower)
{
  analogWrite (E1,leftPower);
  digitalWrite(M1,LOW);   
  analogWrite (E2,rightPower);    
  digitalWrite(M2,LOW);
}  
void back_off (char leftPower,char rightPower)
{
  analogWrite (E1,leftPower);
  digitalWrite(M1,HIGH);    
  analogWrite (E2,rightPower);    
  digitalWrite(M2,HIGH);
}
void turn_L (char leftPower,char rightPower)
{
  analogWrite (E1,leftPower);
  digitalWrite(M1,HIGH);    
  analogWrite (E2,rightPower);    
  digitalWrite(M2,LOW);
}
void turn_R (char leftPower,char rightPower)
{
  analogWrite (E1,leftPower);
  digitalWrite(M1,LOW);    
  analogWrite (E2,rightPower);    
  digitalWrite(M2,HIGH);
}
void bank (char leftPower,char rightPower)
{
  analogWrite (E1,leftPower);
  digitalWrite(M1,LOW);    
  analogWrite (E2,rightPower);    
  digitalWrite(M2,LOW);
}
boolean atLeast (int input, int floor)
{
  return (input >= floor);
}
boolean below (int input, int ceiling)
{
  return (input < ceiling);
}
boolean between (int input, int floor, int ceiling)
{
  return (atLeast(input, floor) && below(input,ceiling));
}
Closeness decideCloseness(int input)
{
  if(below(input, VERY_FAR))
  {
    return VERY_FAR;
  }
  if (between(input, VERY_FAR, FAR))
  {
    return FAR;
  }
  if (between(input, FAR, CLOSE))
  {
    return CLOSE;
  }
  return VERY_CLOSE;
}

char* closenessString(Closeness closeness)
{
  switch(closeness)
  {
    case VERY_FAR:
      return "Very Far";
    case FAR:
      return "Far";
    case CLOSE:
      return "Close";
    case VERY_CLOSE:
      return "Very Close";
    default:
      return "Unknown";
  }
}

void setup(void) 
{ 
  int i;
  for(i=6;i<=9;i++)
    pinMode(i, OUTPUT);  
  Serial.begin(9600);      //Set Baud Rate

} 
void loop(void) 
{
  int rightSensor = analogRead(A0);
  int frontSensor = analogRead(A1);
  int leftSensor = analogRead(A2);
  
  Closeness rightCloseness = decideCloseness(rightSensor);
  Closeness frontCloseness = decideCloseness(frontSensor);
  Closeness leftCloseness = decideCloseness(leftSensor);
  
  p("Right: %s   Front: %s   Left: %s \n", closenessString(rightCloseness), closenessString(frontCloseness), closenessString(leftCloseness));
  
  if(atLeast(frontCloseness, VERY_CLOSE) && below(rightCloseness, CLOSE))
  {
    back_off (QUARTER_POWER, FULL_POWER);
  }
  else if (atLeast(frontCloseness, VERY_CLOSE))
  {
    back_off (FULL_POWER, FULL_POWER);
  }
  else if(atLeast(frontCloseness, CLOSE) && below(rightCloseness, CLOSE))
  {
    bank (FULL_POWER,QUARTER_POWER);
  }
  else if(atLeast(frontCloseness, CLOSE) && below(leftCloseness, CLOSE))
  {
    bank (QUARTER_POWER,FULL_POWER);
  }
  else if(atLeast(rightCloseness, VERY_CLOSE))
  {
    turn_L (FULL_POWER,FULL_POWER);
  }
  else if(atLeast(leftCloseness, VERY_CLOSE))
  {
    turn_R (FULL_POWER,FULL_POWER);
  }
  else
  {
    advance (FULL_POWER,FULL_POWER);
  }
  
  delay(100);
}



