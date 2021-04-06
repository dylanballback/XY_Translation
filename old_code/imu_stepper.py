import RPi.GPIO as GPIO
from time import sleep

#Variables X and Y
x = 0
y = 0
# Direction pin from controller
DIR1 = 37
DIR2 = 29
# Step pin from controller
STEP1 = 35
STEP2 = 21
# 0/1 used to signify clockwise or counterclockwise
CW = 0
CCW = 0

# Setup pin layout on PI
GPIO.setmode(GPIO.BCM)

# Establish Pins in software
GPIO.setup(DIR1, GPIO.OUT)
GPIO.setup(STEP1, GPIO.OUT)
GPIO.setup(DIR2, GPIO.OUT)
GPIO.setup(STEP2, GPIO.OUT)

# move function for the stepper motors
def move(step_pin, dir_pin, direction, speed, distance):
    # Esablish the direction you want to go
        GPIO.output(dir_pin,direction)
        # Run for 440 steps. This will change based on how you set you controller
        for i in range(distance):
            # Set one coil winding to high
            GPIO.output(step_pin,GPIO.HIGH)
            # Allow it to get there.
            sleep(speed) # Dictates how fast stepper motor will run
            # Set coil winding to low
            GPIO.output(step_pin,GPIO.LOW)
            sleep(speed) # Dictates how fast stepper motor will run
    # set the duration
    
try:
    # Run forever
    while True:
        if (x > 3):
            move(STEP1, DIR1, CCW, 0.005, 500)
        if (x < -3):
            move(STEP1, DIR1, CW, 0.005, 500)
        if (y > 3):
            move(STEP2, DIR2, CCW, 0.005, 500)
        if (y < -3):
            move(STEP2, DIR2, CW, 0.005, 500)

        """Change Direction: Changing direction requires time to switch. The
        time is dictated by the stepper motor and controller. 
        sleep(1.0)
        # Esablish the direction you want to go
        GPIO.output(DIR,CW)

        # Run for 440 steps. This will change based on how you set you controller
        for x in range(440):

            # Set one coil winding to high
            GPIO.output(STEP,GPIO.HIGH)
            # Allow it to get there.
            sleep(.0010) # Dictates how fast stepper motor will run
            # Set coil winding to low
            GPIO.output(STEP,GPIO.LOW)
            sleep(.0010) # Dictates how fast stepper motor will run

        Change Direction: Changing direction requires time to switch. The
        time is dictated by the stepper motor and controller. 
        sleep(1.0)
        GPIO.output(DIR,CCW)
        for x in range(440):
            GPIO.output(STEP,GPIO.HIGH)
            sleep(.0010)
            GPIO.output(STEP,GPIO.LOW)
            sleep(.0010)
            
            """

# Once finished clean everything up
except KeyboardInterrupt:
    print("cleanup")
    GPIO.cleanup()
