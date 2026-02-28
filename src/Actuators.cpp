#include <Arduino.h>
#include <ESP32Servo.h>
#include "Actuators.h"

Servo feederServo;
Servo waterOutServo;

bool isWaterOutOpen = false;
unsigned long waterOutOpenedTime = 0;
unsigned long lastWaterOutTriggerTime = 0;

void initActuators() {
  feederServo.setPeriodHertz(50);    
  waterOutServo.setPeriodHertz(50);
  
  feederServo.attach(feederServoPinOut, 500, 2400);
  waterOutServo.attach(waterOutServoPinOut, 500, 2400);
  
  feederServo.write(0);
  waterOutServo.write(0);
}

void shakeFeederServo(ShakeIntensity intensity) {
  int targetAngle;
  int delayBetweenMovesMs;
  int totalShakes;

  switch (intensity) {
    case WEAK:
      targetAngle = 45;         
      delayBetweenMovesMs = 400; 
      totalShakes = 2;          
      Serial.println("Action: Shaking feeder servo [WEAK]");
      break;
    case MEDIUM:
      targetAngle = 90;         
      delayBetweenMovesMs = 250; 
      totalShakes = 4;          
      Serial.println("Action: Shaking feeder servo [MEDIUM]");
      break;
    case STRONG:
      targetAngle = 135;        
      delayBetweenMovesMs = 120; 
      totalShakes = 6;          
      Serial.println("Action: Shaking feeder servo [STRONG]");
      break;
    default:
      Serial.println("Error: Invalid shake intensity.");
      return;
  }

  for (int i = 0; i < totalShakes; i++) {
    feederServo.write(targetAngle);
    delay(delayBetweenMovesMs); 
    feederServo.write(0); 
    delay(delayBetweenMovesMs);
  }
}

void openWaterOutServo() {
  Serial.println("Action: Opening the water out");
  waterOutServo.write(90); 
  isWaterOutOpen = true;
  waterOutOpenedTime = millis(); 
}

void closeWaterOutServo() {
  Serial.println("Action: Closing the water out");
  waterOutServo.write(0); 
  isWaterOutOpen = false;
  lastWaterOutTriggerTime = millis(); 
}
