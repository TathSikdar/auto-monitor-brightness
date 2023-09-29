import serial
import screen_brightness_control as sbc
import time


for portNumber in range(50):
    port = "COM"+str(portNumber)
    try:
        with serial.Serial(port, baudrate = 9600, timeout = 1) as ser:
            while 1:
                time.sleep(7)
                brightnessPercentage = ser.readline()
                if len(brightnessPercentage)>0:
                    print(int(brightnessPercentage.strip()))
                    sbc.set_brightness(int(brightnessPercentage.strip()))
    except Exception as e:
        print(e)
