# Auto-monitor-brightness (HDMI & Display Port only~)

## Materials:
1. **Arduino nano**/Arduino uno/ESP8266/ESP32 (Anything better than an arduino nano is overkill and is bigger in size and therefore more visually obtrusive)
2. LDR (Used a **2k-5k** (GL5506))(Anything higher is overkill unless your using a lower ohm resistor)
3. resistor (Used a **5.1K ohm**)(Higher resistors offer greater precision)
4. (Schematics should also be posted)

## Arduino code:
Takes analog input from LDR (**Remember to set pin to whichever pin the LDR is connected to** (Ex. int sensorPin = A7), converts it to a monitor brighntess % value based on the following **formula:**
**y = -2.787050915+0.058492547x+0.000044146x^2** where x is the average brightness captured by the LDR and y is the monitor % brightness. 
This formula was found by using plotted points (Manually set monitor % brightness vs. LDR readings) and finding the curve of best fit using https://elsenaju.eu/Calculator/online-curve-fit.htm. 
This formula will need to be changed from monitor to monitor (I use a Dell P2419H) or when using resistors of different resistances than the ones mentioned above. 
This monitor brightness % is then monitored for changes and written to serial bus when changes are detected based on **PercentageBrightnessChangeThreshold** (The difference in monitor brightness at which the program will write new brightness % value to serial bus). 

## Python code:
Changes monitor brightness based on % brightness sent by Arduino using PySerial and PyScreen_Brightness_Control library. **Make sure to change com port to the same one used by the Arduino** (Ex. port = COM7  <---All caps). The program also prints monitor brightness % to the terminal everytime it makes a change (Incase you want to check the brightenss values the program has changed to), but that can be removed.
