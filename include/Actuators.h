#pragma once
#include "Config.h"

// Expose state variables for the main loop to evaluate
extern bool isWaterOutOpen;
extern unsigned long waterOutOpenedTime;
extern unsigned long lastWaterOutTriggerTime;

// Function Prototypes
void initActuators();
void shakeFeederServo(ShakeIntensity intensity);
void openWaterOutServo();
void closeWaterOutServo();

