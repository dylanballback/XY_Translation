#include<Wire.h>

const int MPU_addr=0x68; 
int16_t AcX, AcY, AcZ, Tmp, GyX, GyY, GyZ;

int minVal = 9; 
int maxVal = 351;

double x; 
double y;

const int stepPin = 8; // define pin for step
const int dirPin = 10;  // define pin for direction

const int stepPin2 = 4; // define pin for step
const int dirPin2 = 6;  // define pin for direction

int CC = LOW;
int CCW = HIGH;

int current_direction = LOW;

void setup() {
Wire.begin(); 
Wire.beginTransmission(MPU_addr); 
Wire.write(0x6B);
Wire.write(0); 
Wire.endTransmission(true); 
Serial.begin(9600);

pinMode(stepPin,OUTPUT); 
pinMode(dirPin,OUTPUT);
  
pinMode(stepPin2,OUTPUT); 
pinMode(dirPin2,OUTPUT);
}

void loop() {
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

x = RAD_TO_DEG * (atan2(-yAng, -zAng)+PI); 
y = RAD_TO_DEG * (atan2(-xAng, -zAng)+PI);

if(current_direction == LOW){
  digitalWrite(dirPin, HIGH); // set direction, HIGH for clockwise, LOW for anticlockwise
  digitalWrite(dirPin2, HIGH); // set direction, HIGH for clockwise, LOW for anticlockwise
  current_direction = HIGH;
 } else {
  digitalWrite(dirPin, LOW); // set direction, HIGH for clockwise, LOW for anticlockwise
  digitalWrite(dirPin2, LOW); // set direction, HIGH for clockwise, LOW for anticlockwise
  current_direction = LOW;
 }
if (x > 10 && x < 180){
  Serial.print("move forward in the X // ");
 }
  if (x < 350 && x > 181){
  Serial.print("move backward in the X // ");
 }

if (y > 10 && y < 180){
  Serial.print("move to the right in the Y ");
 }
  if (y < 350 && y > 181){
  Serial.print("move to the left in the Y ");
 }

 for(x; x<500; x++) { // loop for 200 steps
  digitalWrite(stepPin,HIGH);
  delayMicroseconds(500);
  digitalWrite(stepPin,LOW);
  delayMicroseconds(500);
 }

 for(y; y<4000; y++) { // loop for 200 steps
  digitalWrite(stepPin2,HIGH);
  delayMicroseconds(100);
  digitalWrite(stepPin2,LOW); 
  delayMicroseconds(100);
 }
Serial.println("\n-----------------------------------------"); 
//delay(100); // delay for 1 second
 
}
