
int IRSensor1 = A3;
int IRSensor2 = A4;
int IRSensor3 = A5;
int IRSensor4 = A6;
int IRSensor5 = A7;
int IRSensor6 = A8;
int IRSensor7 = A9;
//int LED = 13;
void setup() {
 Serial.begin(9600);
// set pin as input to receive info on sensor detection
 pinMode(IRSensor1, INPUT)
 pinMode(IRSensor2, INPUT)
 pinMode(IRSensor3, INPUT)
 pinMode(IRSensor4, INPUT)
 pinMode(IRSensor5, INPUT)
 pinMode(IRSensor6, INPUT)
 pinMode(IRSensor7, INPUT)
 //pinMode(LED, OUTPUT);// to light up LED if something is detected
}

void loop() {
  
  for(int i=A3;i<A10;i++){
    // read ball status and store it into "detect"
    int detect = analogRead(IRSensor);
    Serial.println(i);
    if(detect <200){ //ball detected
  // digitalWrite(LED, HIGH);//turn on led
      Serial.println("YES ball"); 
  }else{ //balll not detected
   //digitalWrite(LED, LOW);//turn off led
    Serial.println("NO ball");  

    }
  }

  //Serial.println(detect);
  
}
