//link to simulator https://wokwi.com/projects/349179354927858259

int IRSensor = 2;
int LED = 13;
void setup() {
 
 pinMode(IRSensor, INPUT);// set pin as input to receive info on sensor detection
 pinMode(LED, OUTPUT);// to light up LED if something is detected
}

void loop() {

  int detect = analogRead(IRSensor);// read ball status and store it into "detect"
  if(detect == LOW){ //ball detected
   digitalWrite(LED, HIGH);//turn on led
   Serial.println("Yes ball"); 

  }else{ //balll not detected
   digitalWrite(LED, LOW);//turn off led
   Serial.println("No ball");  

  }
}



//notes
//IR module outputs LOW when detecting object
//digitalWrite() sets mode
//digitalRead() reads mode

