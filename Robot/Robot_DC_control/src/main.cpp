#include <Arduino.h>

#define PWM_PIN_1 1             // PWM output pin 
#define DIRECTION_PIN_1 3       // Direction control pin
#define PWM_PIN_2 22             // PWM output pin
#define DIRECTION_PIN_2 23       // Direction control pin
#define PWM_FREQUENCY 100000   // 100 kHz
#define PWM_RESOLUTION 8       // 8-bit resolution
#define PWM_CHANNEL_1 0          // PWM channel
#define PWM_CHANNEL_2 2          // PWM channel
#define SWITCH_INTERVAL 5000   // Interval to change direction in milliseconds

int direction = HIGH;        // Initial direction state

void move_forward();
void turn_left();

void setup() {
  // Initialize the PWM pin and channel
  ledcSetup(PWM_CHANNEL_1, PWM_FREQUENCY, PWM_RESOLUTION);
  ledcSetup(PWM_CHANNEL_2, PWM_FREQUENCY, PWM_RESOLUTION);
  ledcAttachPin(PWM_PIN_1, PWM_CHANNEL_1);
  ledcAttachPin(PWM_PIN_2, PWM_CHANNEL_2);
  
  // Start the PWM with 50% duty cycle
  ledcWrite(PWM_CHANNEL_1, 255); // 50% of 255 (8-bit resolution)
  ledcWrite(PWM_CHANNEL_2, 255);

  // Initialize the direction pin
  pinMode(DIRECTION_PIN_1, OUTPUT);
  digitalWrite(DIRECTION_PIN_1, direction);
  pinMode(DIRECTION_PIN_2, OUTPUT);
  digitalWrite(DIRECTION_PIN_2, direction);
}

void loop() {

  /*
  delay(500);
  direction = !direction;
  digitalWrite(DIRECTION_PIN_1, direction);
  */
 turn_left();
}

void turn_left() {
  ledcWrite(PWM_CHANNEL_1, 0);
  ledcWrite(PWM_CHANNEL_2, 255);
  direction = !direction;
  digitalWrite(DIRECTION_PIN_1, direction);
  digitalWrite(DIRECTION_PIN_2, !direction);
  delay(300);
  direction = !direction;
  digitalWrite(DIRECTION_PIN_1, direction);
  digitalWrite(DIRECTION_PIN_2, !direction);
  delay(800);
}

void move_forward() {
  ledcWrite(PWM_CHANNEL_1, 255);
  ledcWrite(PWM_CHANNEL_2, 255);
  direction = !direction;
  digitalWrite(DIRECTION_PIN_1, direction);
  digitalWrite(DIRECTION_PIN_2, !direction);
  delay(300);
  direction = !direction;
  digitalWrite(DIRECTION_PIN_1, direction);
  digitalWrite(DIRECTION_PIN_2, !direction);
  delay(800);
}