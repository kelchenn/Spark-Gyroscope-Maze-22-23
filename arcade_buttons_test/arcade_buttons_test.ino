const int arcadebutton1Pin =  22; 
const int arcadebutton2Pin =  52;

void setup() {
  Serial.begin(9600);
  // Set up the arcadebutton pins to be an input:
  pinMode(arcadebutton1Pin, INPUT);
  pinMode(arcadebutton2Pin, INPUT);
}

void loop() 
{
  int arcadebutton1State;  // variables to hold the arcadebutton states
  int arcadebutton2State;
  
  // Here we'll read the current arcadebutton states into
  // two variables:
  arcadebutton1State = digitalRead(arcadebutton1Pin);
  arcadebutton2State = digitalRead(arcadebutton2Pin);

  // If button1 is being pressed, print to serial panel
  if (arcadebutton1State == HIGH)
    {
       Serial.print("button 1 = " );
       Serial.println(arcadebutton1State);
     }
  else if (arcadebutton2State == HIGH)
    {
      Serial.print("button 2= ");
      Serial.println(arcadebutton2State);
    }
}
