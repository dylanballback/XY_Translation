const int stepPin = 8; // define pin for step
const int dirPin = 10;  // define pin for direction

const int stepPin2 = 4; // define pin for step
const int dirPin2 = 6;  // define pin for direction


int CC = LOW;
int CCW = HIGH;

//Set direction
int current_direction = LOW;

void setup() {
  pinMode(stepPin,OUTPUT);
  pinMode(dirPin,OUTPUT);

  pinMode(stepPin2,OUTPUT);
  pinMode(dirPin2,OUTPUT);
}


// Loop
void loop() {

if(current_direction == LOW){
  digitalWrite(dirPin, HIGH); // set direction, HIGH for clockwise, LOW for anticlockwise
  digitalWrite(dirPin2, HIGH); // set direction, HIGH for clockwise, LOW for anticlockwise
  current_direction = HIGH;
 } else {
  digitalWrite(dirPin, LOW); // set direction, HIGH for clockwise, LOW for anticlockwise
  digitalWrite(dirPin2, LOW); // set direction, HIGH for clockwise, LOW for anticlockwise
  current_direction = LOW;
 }

 for(int x = 0; x<500; x++) { // loop for 200 steps
  digitalWrite(stepPin,HIGH);
  delayMicroseconds(500);
  digitalWrite(stepPin,LOW);
  delayMicroseconds(500);
 }

 for(int x = 0; x<4000; x++) { // loop for 200 steps
  digitalWrite(stepPin2,HIGH);
  delayMicroseconds(100);
  digitalWrite(stepPin2,LOW);
  delayMicroseconds(100);
 }
delay(1000); // delay for 1 second

}
