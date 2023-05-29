int IRSensor = A5; // connect ir sensor to arduino pin A5
int sensorValue = 0;

void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(9600);

  pinMode(IRSensor, INPUT); // ir sensor pin as INPUT
  digitalWrite(IRSensor, HIGH); // turn on the pullup resistor
}


void loop() {
  // read the analog in value:
  sensorValue = analogRead(IRSensor);

  Serial.print("sensor = " );
  Serial.println(sensorValue);

}
