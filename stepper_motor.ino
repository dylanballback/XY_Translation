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
  // Stepup all pins to the board
  pinMode(x_step_pin,OUTPUT);
  pinMode(x_dir_pin,OUTPUT);
  pinMode(y_step_pin,OUTPUT);
  pinMode(y_dir_pin,OUTPUT);
}

void loop() {
  // Run the code to balance the system
  move(x_step_pin,x_dir_pin,CC,500,600);

  delay(1000); // delay for 1 second

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
