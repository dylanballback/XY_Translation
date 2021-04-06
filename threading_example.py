import RPi.GPIO as GPIO
from time import sleep
from mpu6050 import mpu6050
from threading import Thread


# Sensor variables
global x
global y
global sensor
sensor = mpu6050(0x68)

# Direction pin from controller
DIR1 = 37
DIR2 = 29
# Step pin from controller
STEP1 = 35
STEP2 = 21
# 0/1 used to signify clockwise or counterclockwise
CW =1
CCW = 1

# Setup pin layout on PI
GPIO.setmode(GPIO.BCM)

# Establish Pins in software
GPIO.setup(DIR1, GPIO.OUT)
GPIO.setup(STEP1, GPIO.OUT)
GPIO.setup(DIR2, GPIO.OUT)
GPIO.setup(STEP2, GPIO.OUT)

# move function for the stepper motors
def move(step_pin, dir_pin, direction, speed, distance):
    global GPIO
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
# 
# def get_mpu_data():
#     
#     global x
#     global y
#     global sensor
#     
#     while True:
#         accelerometer_data = sensor.get_accel_data()
#         x = accelerometer_data['x']
#         y = accelerometer_data['y']
# 
# 
# data = Thread(target=get_mpu_data) 
# #Start Thread 
# data.start()

try:
    while True:
        print("Move x")
        move(STEP1, DIR1, CCW, 0.1, 2000)
        sleep(1)
    
    
    
#     # Run forever
#     while True:
#         if (x > 3):
#             move(STEP1, DIR1, CCW, 0.005, 500)
#         if (x < -3):
#             move(STEP1, DIR1, CW, 0.005, 500)
#         if (y > 3):
#             move(STEP2, DIR2, CCW, 0.005, 500)
#         if (y < -3):
#             move(STEP2, DIR2, CW, 0.005, 500)
# 
      

# Once finished clean everything up
except KeyboardInterrupt:
    print("cleanup")
finally:
    GPIO.cleanup()
