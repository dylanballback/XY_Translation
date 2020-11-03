#include<Wire.h>

const int MPU_addr=0x68;
int16_t AcX, AcY, AcZ, Tmp, GyX, GyY, GyZ;

int minVal = 9;
int maxVal = 351;

double x;
double y;

// X direction
const int x_step_pin = 8; // define pin for step
const int x_dir_pin = 10;  // define pin for direction

// Y direction
const int y_step_pin = 4; // define pin for step
const int y_dir_pin = 6;  // define pin for direction

// Defult directions
int CC = LOW;
int CCW = HIGH;

void setup() {
  // Code for sensing angle
  Wire.begin();
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);
  Serial.begin(9600);

  // Stepup all pins to the board
  pinMode(x_step_pin,OUTPUT);
  pinMode(x_dir_pin,OUTPUT);
  pinMode(y_step_pin,OUTPUT);
  pinMode(y_dir_pin,OUTPUT);
  
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

  y = RAD_TO_DEG * (atan2(-yAng, -zAng)+PI);
  x = RAD_TO_DEG * (atan2(-xAng, -zAng)+PI);


  if (x > 10 && x < 180){
    Serial.println("move forward in the X // ");
    move(x_step_pin,x_dir_pin,CCW,500,600);
   }

  if (x < 350 && x > 181){
    Serial.println("move backward in the X // ");
    move(x_step_pin,x_dir_pin,CC,500,600);
   }

  if (y > 7 && y < 180){
    Serial.println("move to the right in the Y ");
    move(y_step_pin,y_dir_pin,CCW,25,2000);
   }

  if (y < 353 && y > 181){
    Serial.println("move to the left in the Y ");
    move(y_step_pin,y_dir_pin,CC,25,2000);
   }
// End Loop
}

void move(int step_pin, int dir_pin, int direction, int speed, int distance){
// Move the servo function

  // Set the direction
  digitalWrite(dir_pin, direction);

  // Run
  for(int x = 0; x<distance; x++) {
   digitalWrite(step_pin,HIGH);
   delayMicroseconds(speed);
   digitalWrite(step_pin,LOW);
   delayMicroseconds(speed);
  }

// End of loop
}
