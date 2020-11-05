#include<Wire.h>
//-------------------------
const int MPU_addr = 0x68;
int16_t AcX, AcY, AcZ, Tmp, GyX, GyY;
//-------------------------
int minVal = 9;
int maxVal = 351;
//-------------------------
double x;
double y;
//-------------------------
// X direction <>
const int x_step_pin = 8; // define pin for step
const int x_dir_pin = 10;  // define pin for direction
float Gyro_angleX[2]; // define array for gyro angle
float Total_angleX[2]; // define array for total angle
float Acceleration_angleX[2]; // define array for acceleration angle
//-------------------------
// Y direction ^^
const int y_step_pin = 4; // define pin for step
const int y_dir_pin = 6;  // define pin for direction
float Gyro_angleY[2]; // define array for gyro angle
float Total_angleY[2]; // define array for total angle
float Acceleration_angleY[2]; // define array for acceleration angle
//-------------------------
// Defult directions
int CC = LOW;
int CCW = HIGH;
//-------------------------
float elapsedTime, time, timePrev;
int i;
float rad_to_deg = 180 / 3.141592654;
//-------------------------
float desired_angle = 0; /*This is the angle in which we whant the
                          balance to stay steady*/
//-------------------------
void setup() {
  // Code for sensing angle
  Wire.begin();
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);
  Serial.begin(250000);
//-------------------------
  // Stepup all pins to the board
  pinMode(x_step_pin,OUTPUT);
  pinMode(x_dir_pin,OUTPUT);
  pinMode(y_step_pin,OUTPUT);
  pinMode(y_dir_pin,OUTPUT);
//-------------------------
  time = millis(); //Start counting time in milliseconds
  delay(1000);
}// end setup void
//-------------------------
void loop() {

  timePrev = time;  // the previous time is stored before the actual time read
  time = millis();  // actual time read
  elapsedTime = (time - timePrev) / 1000;
//-------------------------
  // Read the MPU 6050
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr,14,true);
//-------------------------
  AcX = Wire.read()<<8|Wire.read();
  AcY = Wire.read()<<8|Wire.read();
  AcZ = Wire.read()<<8|Wire.read();
//-------------------------
  /*---X---*/
  Acceleration_angleX[1] = atan(-1 * (AcX / 16384.0) / sqrt(pow((AcY / 16384.0), 2) + pow((AcZ / 16384.0), 2))) * rad_to_deg;
  /*---Y---*/
  Acceleration_angleY[0] = atan((AcY / 16384.0) / sqrt(pow((AcX / 16384.0), 2) + pow((AcZ / 16384.0), 2))) * rad_to_deg;
//-------------------------
  int xAng = map(AcX,minVal,maxVal,-90,90);
  int yAng = map(AcY,minVal,maxVal,-90,90);
  int zAng = map(AcZ,minVal,maxVal,-90,90);
//-------------------------
  y = RAD_TO_DEG * (atan2(-yAng, -zAng)+PI);
  x = RAD_TO_DEG * (atan2(-xAng, -zAng)+PI);
//-------------------------
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x43); //Gyro data first adress
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr, 4, true); //Just 4 registers
//-------------------------
  GyX = Wire.read() << 8 | Wire.read(); //Once again we shif and sum
  GyY = Wire.read() << 8 | Wire.read();
//-------------------------
  /*---X---*/
  Gyro_angleX[0] = GyX / 131.0; // dividing by the value the datasheet gave, 131
  /*---Y---*/
  Gyro_angleY[1] = GyY / 131.0;
//-------------------------
  // implement for the acceleration due to gravity, .98, that affects the angles
  /*---X axis angle---*/
  Total_angleX[0] = 0.98 * (Total_angleX[0] + Gyro_angleX[0] * elapsedTime) + 0.02 * Acceleration_angleX[0];
  /*---Y axis angle---*/
  Total_angleY[1] = 0.98 * (Total_angleY[1] + Gyro_angleY[1] * elapsedTime) + 0.02 * Acceleration_angleY[1];
//-------------------------
// CHANGE THE VALUES IN THE IF STATEMENTS........
  if (Total_angleX[0] > 1 ){
    Serial.println(Total_angleY[1]);
    move(x_step_pin,x_dir_pin,CCW,500,100);
   }
//-------------------------
  if (Total_angleX[0] < 1 ){
    Serial.println(Total_angleY[1]);
    move(x_step_pin,x_dir_pin,CC,500,100);
   }
//-------------------------
  if (Total_angleY[1] > 1 ){
    Serial.println(Total_angleX[0]);
    move(y_step_pin,y_dir_pin,CCW,25,300);
   }
//-------------------------
  if (Total_angleY[1] < 1 ){
    Serial.println(Total_angleX[0]);
    move(y_step_pin,y_dir_pin,CC,25,300);
   }
// End Loop
}
//-------------------------
// Move the servo function
void move(int step_pin, int dir_pin, int direction, int speed, int distance){
//-------------------------
  // Set the direction
  digitalWrite(dir_pin, direction);
//-------------------------
  // Run
  for(int x = 0; x < distance; x++) {
   digitalWrite(step_pin,HIGH);
   delayMicroseconds(speed);
   digitalWrite(step_pin,LOW);
   delayMicroseconds(speed);
  }
// End of FOR loop
}
