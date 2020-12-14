 #include <LowPower.h>

int sensorPin = A7;
int pastBrightnessPercentage = 0;
int currentBrightnessPercentage;
int PercentageBrightnessChangeThreshold = 5;

int brightnessPercentage();

void setup() {
  Serial.begin(9600);
}

void loop() {
  currentBrightnessPercentage = brightnessPercentage();
  if(pastBrightnessPercentage+PercentageBrightnessChangeThreshold<=currentBrightnessPercentage || pastBrightnessPercentage-PercentageBrightnessChangeThreshold>=currentBrightnessPercentage){
    Serial.println(currentBrightnessPercentage);
    pastBrightnessPercentage = currentBrightnessPercentage;
  }
  Serial.flush();
  int i;
  LowPower.idle(SLEEP_8S, ADC_OFF, TIMER2_ON, TIMER1_OFF, TIMER0_OFF, SPI_OFF, USART0_OFF, TWI_OFF);
}


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
  brightnessPercentage = int(-2.787050915+0.058492547*averageBrightness+0.000044146*averageBrightness*averageBrightness);
  if(brightnessPercentage<0){
    brightnessPercentage=0;
  }
  else if (brightnessPercentage>100){
    brightnessPercentage=100;
  }
  return brightnessPercentage;
}
