#include<Wire.h>
 
const int MPU_addr=0x68;
int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;
 
int minVal=265;
int maxVal=402;
 
double x;
double y;
double z;
 
#define SCK_PIN 8
#define SDI_PIN 9
#define CS_PIN 10
#define POT_PIN A0
#define DAC_MAX 4095

#include "MCP_DAC.h"

int writeval;
MCP4921 myDAC(SDI_PIN, SCK_PIN);

  
void setup(){
myDAC.begin(CS_PIN);
Wire.begin();

Wire.beginTransmission(MPU_addr);
Wire.write(0x6B);
Wire.write(0);
Wire.endTransmission(true);
Serial.begin(9600);
}
void loop(){
Wire.beginTransmission(MPU_addr);
Wire.write(0x3B);
Wire.endTransmission(false);
Wire.requestFrom(MPU_addr,14,true);
AcX=Wire.read()<<8|Wire.read();
AcY=Wire.read()<<8|Wire.read();
AcZ=Wire.read()<<8|Wire.read();
int xAng = map(AcX,minVal,maxVal,-90,90);
int yAng = map(AcY,minVal,maxVal,-90,90);
int zAng = map(AcZ,minVal,maxVal,-90,90);
 
x= RAD_TO_DEG * (atan2(-yAng, -zAng)+PI);
y= RAD_TO_DEG * (atan2(-xAng, -zAng)+PI);
z= RAD_TO_DEG * (atan2(-yAng, -xAng)+PI);
 
Serial.print("AngleX= ");
Serial.println(x);
 
Serial.print("AngleY= ");
Serial.println(y);
 
Serial.print("AngleZ= ");
Serial.println(z);
Serial.println("-----------------------------------------");
if (y >=0 && y <=90){
  //DAC_MAX/5=819 = 1volt=60deg
  myDAC.analogWrite(map(y, 90, 0, 1638,2047));
}else if (y >=270 && y <=360){
myDAC.analogWrite(map(y, 360, 270,  2048,2457));
}delay(400);
}
