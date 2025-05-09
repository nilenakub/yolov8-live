// Arduino Uno
// Receives A ,Switches on LED on Pin13 for 2 seconds
// Rahul.S

// (c) www.xanthium.in 2021
// Tutorial - https://www.xanthium.in/Cross-Platform-serial-communication-using-Python-and-PySerial

#include "AccelStepper.h"
#include "math.h"

// Motor pin definitions:
#define motorPin1  11      // IN1 on the ULN2003 driver
#define motorPin2  10      // IN2 on the ULN2003 driver
#define motorPin3  9     // IN3 on the ULN2003 driver
#define motorPin4  8     // IN4 on the ULN2003 driver

// Define the AccelStepper interface type; 4 wire motor in half step mode:
#define MotorInterfaceType 8

// Initialize with pin sequence IN1-IN3-IN2-IN4
AccelStepper stepper = AccelStepper(MotorInterfaceType, motorPin1, motorPin3, motorPin2, motorPin4);

void setup()
{
  // Set the maximum steps per second:
  stepper.setMaxSpeed(1000);
  // Set the maximum acceleration in steps per second^2:
  stepper.setAcceleration(200);
  //An LED is Connected Pin12 
  Serial.begin(9600); // opens serial port, sets data rate to 9600 bps 8N1
  
}

void loop()
{
 while (Serial.available()==0){}
      float height = Serial.parseFloat();    
      Serial.println(height);
      motorcal(height);
}

      
int motorcal(float h){

  long distance = ((round(h))*200);
    // Set target position:
  stepper.moveTo(distance);
  // Run to position with set speed and acceleration:
  stepper.runToPosition();
  
  delay(1000);
  
  // Move back to original position:
  stepper.moveTo(0);
  // Run to position with set speed and acceleration:
  stepper.runToPosition();
  
  delay(1000);

}
  