//IR module outputs LOW when detecting object


int IRSensor = 2;
int LED = 13;
void setup() {
 
 pinMode(IRSensor, INPUT);// set pin as input to receive info on sensor detection
 pinMode(LED, OUTPUT);// to light up LED if something is detected
}

void loop() {

  int detect = digitalRead(IRSensor);// read ball status and store it into "detect"
  if(detect == LOW){ //ball detected
   digitalWrite(LED, HIGH);//turn on led
   Serial.println("Obastacle on the way"); 

  }else{ //balll not detected
   digitalWrite(LED, LOW);//turn off led
   Serial.println("All clear");  

  }
  delay(200);
}

//digitalWrite() sets mode
//digitalRead() reads mode
