import serial
import screen_brightness_control as sbc
import time

port = 'COM7'

with serial.Serial(port, baudrate = 9600, timeout = 1) as ser:

    while 1:
        time.sleep(7)
        brightnessPercentage = ser.readline()
        if len(brightnessPercentage)>0:
            print(int(brightnessPercentage))
            sbc.fade_brightness(int(brightnessPercentage))
