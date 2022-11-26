#define A 12
#define B 10
#define C 8
#define D 7
#define E 6
#define F 11
#define G 9

#define D1 1
#define D2 2
#define D3 3
#define D4 4
#define DP 13 // decimal point
#define BUTTON 5

long n = 0; //start time
int x = 100; 
int del = 30; //delay value
int lastButtonState;
int currentButtonState;
bool on = true;
int prevNum1;
int prevNum2;
int prevNum3;
int prevNum4;
 
void setup()
{
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);
  pinMode(D4, OUTPUT);
  pinMode(DP, OUTPUT);
  pinMode(A, OUTPUT);
  pinMode(B, OUTPUT);
  pinMode(C, OUTPUT);
  pinMode(D, OUTPUT);
  pinMode(E, OUTPUT);
  pinMode(F, OUTPUT);
  pinMode(G, OUTPUT);
  pinMode(BUTTON, INPUT_PULLUP);

}
 
void loop()
{
  if(digitalRead(BUTTON)==LOW)          
  {   
    delay(10);                        
    if(digitalRead(BUTTON)==LOW)      
    {                      
      while(digitalRead(BUTTON)==LOW);
      on = !on;
      n = 0;                  
    }
  }

  if (on) {
    pickDigit(4);
    pickNumber(n/100%10);
    prevNum4 = n/100%10;
    clearLEDs();
    delayMicroseconds(del);

    pickDigit(3);
    pickNumber((n/1000)%10);
    prevNum3 = n/1000%10;
    clearLEDs();
    delayMicroseconds(del);

    pickDigit(2);
    pickNumber((n/10000)%10);
    prevNum2 = n/10000%10;
    clearLEDs();
    delayMicroseconds(del);

    pickDigit(1);
    pickNumber((n/100000)%10);
    prevNum1 = n/100000%10;
    clearLEDs();
    delayMicroseconds(del);

    n++;
  } else {

    clearLEDs();
    pickDigit(4);
    pickNumber(prevNum4);

    clearLEDs();
    pickDigit(3);
    pickNumber(prevNum3);

    clearLEDs();
    pickDigit(2);
    pickNumber(prevNum2);;

    clearLEDs();
    pickDigit(1);
    pickNumber(prevNum1);
    clearLEDs();

  }
}
 
void pickDigit(int x) //changes digit
{
  digitalWrite(D1, HIGH);
  digitalWrite(D2, HIGH);
  digitalWrite(D3, HIGH);
  digitalWrite(D4, HIGH);
  digitalWrite(DP, LOW);

  switch(x)
  {
  case 1: 
    digitalWrite(D1, LOW); 
    digitalWrite (DP, LOW);
    break;
  case 2: 
    digitalWrite(D2, LOW); 
    digitalWrite (DP, LOW);
    break;
  case 3: 
    digitalWrite(D3, LOW);
    digitalWrite(DP, HIGH);
    break;
  default: 
    digitalWrite(D4, LOW); 
    digitalWrite (DP, LOW);
    break;
  }
}

void clearDigit(int x) //changes digit
{
  digitalWrite(D1, HIGH);
  digitalWrite(D2, HIGH);
  digitalWrite(D3, HIGH);
  digitalWrite(D4, HIGH);
  digitalWrite(DP, LOW);

  switch(x)
  {
  case 1: 
    digitalWrite(D1, LOW); 
    digitalWrite (DP, LOW);
    break;
  case 2: 
    digitalWrite(D2, LOW); 
    digitalWrite (DP, LOW);
    break;
  case 3: 
    digitalWrite(D3, LOW);
    digitalWrite(DP, LOW);
    break;
  default: 
    digitalWrite(D4, LOW); 
    digitalWrite (DP, LOW);
    break;
  }
}
 
void pickNumber(int x) //changes value of number
{
  switch(x)
  {
  default: 
    zero(); 
    break;
  case 1: 
    one(); 
    break;
  case 2: 
    two(); 
    break;
  case 3: 
    three(); 
    break;
  case 4: 
    four(); 
    break;
  case 5: 
    five(); 
    break;
  case 6: 
    six(); 
    break;
  case 7: 
    seven(); 
    break;
  case 8: 
    eight(); 
    break;
  case 9: 
    nine(); 
    break;
  }
}
 
void clearLEDs()
{
  digitalWrite(A, LOW);
  digitalWrite(B, LOW);
  digitalWrite(C, LOW);
  digitalWrite(D, LOW);
  digitalWrite(E, LOW);
  digitalWrite(F, LOW);
  digitalWrite(G, LOW);
  digitalWrite(DP, LOW);
}
 
void zero()
{
  digitalWrite(A, HIGH);
  digitalWrite(B, HIGH);
  digitalWrite(C, HIGH);
  digitalWrite(D, HIGH);
  digitalWrite(E, HIGH);
  digitalWrite(F, HIGH);
  digitalWrite(G, LOW);
}
 
void one()
{
  digitalWrite(A, LOW);
  digitalWrite(B, HIGH);
  digitalWrite(C, HIGH);
  digitalWrite(D, LOW);
  digitalWrite(E, LOW);
  digitalWrite(F, LOW);
  digitalWrite(G, LOW);
}
 
void two()
{
  digitalWrite(A, HIGH);
  digitalWrite(B, HIGH);
  digitalWrite(C, LOW);
  digitalWrite(D, HIGH);
  digitalWrite(E, HIGH);
  digitalWrite(F, LOW);
  digitalWrite(G, HIGH);
}
 
void three()
{
  digitalWrite(A, HIGH);
  digitalWrite(B, HIGH);
  digitalWrite(C, HIGH);
  digitalWrite(D, HIGH);
  digitalWrite(E, LOW);
  digitalWrite(F, LOW);
  digitalWrite(G, HIGH);
}
 
void four()
{
  digitalWrite(A, LOW);
  digitalWrite(B, HIGH);
  digitalWrite(C, HIGH);
  digitalWrite(D, LOW);
  digitalWrite(E, LOW);
  digitalWrite(F, HIGH);
  digitalWrite(G, HIGH);
}
 
void five()
{
  digitalWrite(A, HIGH);
  digitalWrite(B, LOW);
  digitalWrite(C, HIGH);
  digitalWrite(D, HIGH);
  digitalWrite(E, LOW);
  digitalWrite(F, HIGH);
  digitalWrite(G, HIGH);
}
 
void six()
{
  digitalWrite(A, HIGH);
  digitalWrite(B, LOW);
  digitalWrite(C, HIGH);
  digitalWrite(D, HIGH);
  digitalWrite(E, HIGH);
  digitalWrite(F, HIGH);
  digitalWrite(G, HIGH);
}
 
void seven()
{
  digitalWrite(A, HIGH);
  digitalWrite(B, HIGH);
  digitalWrite(C, HIGH);
  digitalWrite(D, LOW);
  digitalWrite(E, LOW);
  digitalWrite(F, LOW);
  digitalWrite(G, LOW);
}
 
void eight()
{
  digitalWrite(A, HIGH);
  digitalWrite(B, HIGH);
  digitalWrite(C, HIGH);
  digitalWrite(D, HIGH);
  digitalWrite(E, HIGH);
  digitalWrite(F, HIGH);
  digitalWrite(G, HIGH);
}
 
void nine()
{
  digitalWrite(A, HIGH);
  digitalWrite(B, HIGH);
  digitalWrite(C, HIGH);
  digitalWrite(D, HIGH);
  digitalWrite(E, LOW);
  digitalWrite(F, HIGH);
  digitalWrite(G, HIGH);
}
