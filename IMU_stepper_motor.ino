#include<Wire.h>

const int MPU_addr=0x68;
int16_t AcX, AcY, AcZ, Tmp, GyX, GyY, GyZ;

int minVal = 9;
int maxVal = 351;

double x;
double y;

void setup() {
  Wire.begin();
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);
  Serial.begin(9600);
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


  if (x > 5 && x < 180){
    Serial.print("move forward in the X // ");
   }

  if (x < 355 && x > 181){
    Serial.print("move backward in the X // ");
   }

  if (y > 5 && y < 180){
    Serial.print("move to the right in the Y ");
   }

  if (y < 355 && y > 181){
    Serial.print("move to the left in the Y ");
   }
// End Loop
}
