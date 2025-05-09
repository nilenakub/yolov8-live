// Variable to store the received float
float receivedValue = 0.0;

// Flag to indicate if an action has been performed
bool actionPerformed = false;

#include "AccelStepper.h"
#include "math.h"

// Motor pin definitions:
#define motorPin1  11      // IN1 on the ULN2003 driver
#define motorPin2  10      // IN2 on the ULN2003 driver
#define motorPin3  9     // IN3 on the ULN2003 driver
#define motorPin4  8     // IN4 on the ULN2003 driver
#define cutPin    53     // Simulate blade
// Define the AccelStepper interface type; 4 wire motor in half step mode:
#define MotorInterfaceType 8

// Initialize with pin sequence IN1-IN3-IN2-IN4
AccelStepper stepper = AccelStepper(MotorInterfaceType, motorPin1, motorPin3, motorPin2, motorPin4);



void setup() {
  pinMode(53, OUTPUT);

  Serial.begin(9600); // Initialize serial communication at 9600 baud rate
  Serial.println("Arduino ready to receive float...");
  // Set the maximum steps per second:
  stepper.setMaxSpeed(1000);
  // Set the maximum acceleration in steps per second^2:
  stepper.setAcceleration(200);
  //An LED is Connected Pin12 


}

void loop() {
  // Check if serial data is available
  if (Serial.available() > 0) {
    // Read the incoming data as a string
    String dataString = Serial.readStringUntil('\n');
    dataString.trim(); // Remove any leading/trailing whitespace

    // Attempt to convert the string to a float
    receivedValue = dataString.toFloat();

    // Check if the conversion was successful (you might want more robust error handling)
    if (receivedValue != 0.0 || dataString.equals("0.00")) {
      Serial.print("Received: ");
      Serial.println(receivedValue, 2); // Print the received value with 2 decimal places

      // Perform the action only if it hasn't been done yet
      if (!actionPerformed) {
        Serial.println("Performing action based on received value...");
              motorcal(receivedValue);
        // }

        actionPerformed = true; // Set the flag so the action isn't repeated
      } else {
        Serial.println("Action already performed for this value. Waiting for the next.");
      }

      // Reset the flag to allow for a new action upon the next data reception
      actionPerformed = false;
      receivedValue = 0.0; // Reset the received value
    } else {
      Serial.println("Error: Could not convert received data to float.");
    }
  }
  // No delay needed here as we want to be responsive to incoming serial data
}



int motorcal(float h){

  long distance = ((round(h))*200); //edit Algorithm for distance 
  
  // Set target position:
  stepper.moveTo(distance);
  // Run to position with set speed and acceleration:
  stepper.runToPosition();
  
  digitalWrite(53, HIGH);
  delay(2000);
  
  digitalWrite(53, LOW);

  // Move back to original position:
  stepper.moveTo(0);
  // Run to position with set speed and acceleration:
  stepper.runToPosition();
  
  delay(1000);

}