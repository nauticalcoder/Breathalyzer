#include <FourDigitLCD.h>

FourDigitLCD lcd; 
int sensorPin = A0;
int rawSensorValue = 0;
unsigned long previousLoggingTime;
unsigned long previousSampleTime;
unsigned const long loggingTimeInterval = 2000;
unsigned const long sampleTimeInterval = 5000;

int maxReading = 0;
int minReading = 1024;
int displayValue = 0;

bool lastShowedMax = false;
bool sampling = false;

void setup() {
  // put your setup code here, to run once:
  
  lcd.init();
  
  Serial.begin(9600);
  previousLoggingTime = millis();
  
  delay(1000);  // Wait 1 seconds before we start the data collection process
  lcd.display(3);
  delay(1000);  // Wait 1 seconds before we start the data collection process
  lcd.display(2);
  delay(1000);  // Wait 1 seconds before we start the data collection process
  lcd.display(1);
  delay(1000);  // Wait 1 seconds before we start the data collection process
  lcd.display(0);
  
  sampling = true;
  previousSampleTime = millis();
}

void loop() {
  
  // put your main code here, to run repeatedly:
  rawSensorValue = analogRead(sensorPin);

  if (rawSensorValue < minReading) {
    minReading = rawSensorValue;
  }
  if (rawSensorValue > maxReading) {
    maxReading = rawSensorValue;
  }

  unsigned long currentTime = millis();
  if ( (currentTime - previousLoggingTime) >= loggingTimeInterval) {
    Serial.print(currentTime);
    Serial.print(",");
    Serial.println(rawSensorValue);

    if (lastShowedMax) {
      displayValue = minReading;
      
      lastShowedMax = false;
    }
    else {
      displayValue = maxReading;
      lastShowedMax = true;
    }    
    previousLoggingTime = currentTime;
  }

  if (sampling && (currentTime - previousSampleTime) >= sampleTimeInterval) {
    sampling = false;
  }
  
  if (sampling)
    displayValue = 0;

  lcd.display(displayValue);
  
  //delay(100);  
}

void blinkLed(int numberOfBlinks, int duration) {
  for (int i=0; i < numberOfBlinks; i++) {
    delay(duration);              // wait for a second    
    digitalWrite(13, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(duration);              // wait for a second
    digitalWrite(13, LOW);    // turn the LED off by making the voltage LOW
  }
  
}

