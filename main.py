from machine import Pin, I2C
from ssd1306 import SSD1306_I2C
from time import sleep

i2c=I2C(0,sda=Pin(0), scl=Pin(1), freq=200000)
oled = SSD1306_I2C(128, 64, i2c)


x = 0

left_button  = Pin(15, Pin.IN, Pin.PULL_DOWN)
right_button = Pin(14, Pin.IN, Pin.PULL_DOWN)



oled.fill(0)
oled.text("x: 0",0,0)
oled.show()


def move(step_pin, dir_pin, direction, speed, distance):
    # Esablish the direction you want to go
        if direction == 1:
            dir_pin.high()
        else:
            dir_pin.low()

        # Run for 440 steps. This will change based on how you set you controller
        for i in range(distance):
            # Set one coil winding to high
            step_pin.high()
            # Allow it to get there.
            sleep(speed) # Dictates how fast stepper motor will run
            # Set coil winding to low
            step_pin.low()
            sleep(speed) # Dictates how fast stepper motor will run


STEP1 = Pin(13, Pin.OUT)
DIR1  = Pin(12, Pin.OUT)

while True:

    if left_button.value():
        oled.fill(0)
        x = x - 1
        move(STEP1, DIR1, 1, 0.001, 1000)
        oled.text("x: " + str(x),0,0)
        oled.show()
        sleep(0.2)

    if right_button.value():
        oled.fill(0)
        x = x + 1

        move(STEP1, DIR1, 0, 0.001, 1000)

        oled.text("x: " + str(x),0,0)
        oled.show()
        sleep(0.2)
