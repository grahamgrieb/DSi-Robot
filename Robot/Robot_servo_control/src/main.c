#define SERVO_PIN  2   // Pin connected to the servo motor

#include <Arduino.h>

void generatePWM(int pin, int pulseWidth);

void setup() {
  pinMode(SERVO_PIN, OUTPUT);  // Set servo pin as output
}

void loop() {
  // Move the servo from 0 to 270 degrees
  for (int angle = 0; angle <= 270; angle++) {
    int pulseWidth = map(angle, 0, 270, 500, 2500); // Map angle to pulse width
    generatePWM(SERVO_PIN, pulseWidth); // Generate PWM signal
    delay(15);  // Wait for servo to reach the position
  }
  
  // Move the servo from 270 to 0 degrees
  for (int angle = 270; angle >= 0; angle--) {
    int pulseWidth = map(angle, 0, 270, 500, 2500); // Map angle to pulse width
    generatePWM(SERVO_PIN, pulseWidth); // Generate PWM signal
    delay(15);  // Wait for servo to reach the position
  }
}

void generatePWM(int pin, int pulseWidth) {
  digitalWrite(pin, HIGH);
  delayMicroseconds(pulseWidth);
  digitalWrite(pin, LOW);
  delayMicroseconds(20000 - pulseWidth); // Total period of PWM is 20ms (50Hz), subtracting pulse width gives the delay for low signal
}
