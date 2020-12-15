 #include <LowPower.h>

int sensorPin = A7;
int pastBrightnessPercentage = 0;
int currentBrightnessPercentage;
int PercentageBrightnessChangeThreshold = 5;

int brightnessPercentage();

void setup() {
  Serial.begin(9600);
}

/**********************
*Name: Tathagata Sikdar
*Date: Dec. 13, 2020
*Description: Checks for changes in brightness % based on LDR and prints to serial when change is detected
*Input: LDR brightness value (converted to % brightness based on the following formula: brightnessPercentage = -2.787050915+0.058492547*averageBrightness+0.000044146*averageBrightness*averageBrightness)
*from brightnessPercentage function below
*Output: Prints brightness % value to serial port
**********************/
void loop() {
  currentBrightnessPercentage = brightnessPercentage();
  //Checks for changes in % brightness greater than specified change threshold
  if(pastBrightnessPercentage+PercentageBrightnessChangeThreshold<=currentBrightnessPercentage || pastBrightnessPercentage-PercentageBrightnessChangeThreshold>=currentBrightnessPercentage){
    Serial.println(currentBrightnessPercentage);
    pastBrightnessPercentage = currentBrightnessPercentage;
  }
  //Makes sure % value goes all the way to 0% or 100% and doesnt get stuck at 2% or 99% because of the change threshold
  else if ((currentBrightnessPercentage ==0 && pastBrightnessPercentage != 0) || (currentBrightnessPercentage == 100 && pastBrightnessPercentage !=100)){ 
    Serial.println(currentBrightnessPercentage);
    pastBrightnessPercentage = currentBrightnessPercentage;
  }
  Serial.flush();
  LowPower.idle(SLEEP_8S, ADC_OFF, TIMER2_ON, TIMER1_OFF, TIMER0_OFF, SPI_OFF, USART0_OFF, TWI_OFF);
}

/**********************
*Name: Tathagata Sikdar
*Date: Dec. 12, 2020
*Description: Reads sensor pin analog value and converts it to a monitor brightness % based on the following formula: 
*brightnessPercentage = -2.787050915+0.058492547*averageBrightness+0.000044146*averageBrightness*averageBrightness (Differs from monitor to monitor and from resistor resistance combination. 
*Was found through the curve of best fit from plotted points (manually set monitor % brightness compared vs. LDR readings)
*Input: LDR reading
*Output: Monitor brightness %
**********************/
int brightnessPercentage(){
  int brightnessValuesList[100];
  int i;
  long averageBrightness=0;
  int brightnessPercentage;
  for(i=0; i<100; i++){
    brightnessValuesList[i] = analogRead(sensorPin);
  }
  for(i=0; i<100; i++){
    averageBrightness += brightnessValuesList[i];
  }
  averageBrightness = averageBrightness/100;
  brightnessPercentage = int(-2.787050915+0.058492547*averageBrightness+0.000044146*averageBrightness*averageBrightness); //<------LDR brightness value to monitor brightness % formula
  if(brightnessPercentage<0){
    brightnessPercentage=0;
  }
  else if (brightnessPercentage>100){
    brightnessPercentage=100;
  }
  return brightnessPercentage;
}
