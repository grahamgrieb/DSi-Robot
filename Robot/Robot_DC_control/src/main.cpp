#include <Arduino.h>

#define PWM_PIN_1 19          // PWM output pin RIGHT motor
#define DIRECTION_PIN_1 20    // Direction control pin
#define PWM_PIN_2 38          // PWM output pin LEFT motor
#define DIRECTION_PIN_2 44    // Direction control pin 
#define PWM_FREQUENCY 100000  // 100 kHz
#define PWM_RESOLUTION 8      // 8-bit resolution
#define PWM_CHANNEL_1 0       // PWM channel
#define PWM_CHANNEL_2 2       // PWM channel
#define SWITCH_INTERVAL 5000  // Interval to change direction in milliseconds

int direction = HIGH;         // Initial direction state
int currentMovement = 0;      // 0 = move forward, 1 = turn right, 2 = turn left
unsigned long previousMillis = 0;

void move_forward();
void turn_left();
void turn_right();
void stop();

void setup() {
  // Initialize the PWM pin and channel
  ledcSetup(PWM_CHANNEL_1, PWM_FREQUENCY, PWM_RESOLUTION);
  ledcSetup(PWM_CHANNEL_2, PWM_FREQUENCY, PWM_RESOLUTION);
  ledcAttachPin(PWM_PIN_1, PWM_CHANNEL_1);
  ledcAttachPin(PWM_PIN_2, PWM_CHANNEL_2);
  
  // Start the PWM with 50% duty cycle
  ledcWrite(PWM_CHANNEL_1, 128); // 50% of 255 (8-bit resolution)
  ledcWrite(PWM_CHANNEL_2, 128);

  // Initialize the direction pin
  pinMode(DIRECTION_PIN_1, OUTPUT);
  digitalWrite(DIRECTION_PIN_1, direction);
  pinMode(DIRECTION_PIN_2, OUTPUT);
  digitalWrite(DIRECTION_PIN_2, direction);
}

void loop() {
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= SWITCH_INTERVAL) {
    previousMillis = currentMillis;

    // Switch to the next movement function
    currentMovement = (currentMovement + 1) % 3;

    switch (currentMovement) {
      case 0:
        move_forward();
        break;
      case 1:
        turn_right();
        break;
      case 2:
        turn_left();
        break;
    }
  }
}

void turn_left() {
  direction = LOW; 
  ledcWrite(PWM_CHANNEL_1, 255);
  ledcWrite(PWM_CHANNEL_2, 200); // dir low
  // contract
  digitalWrite(DIRECTION_PIN_1, direction); // low makes right motor turn cw
  digitalWrite(DIRECTION_PIN_2, !direction); // high makes left motor turn ccw
  delay(1000);
  // expand
  direction = !direction;
  digitalWrite(DIRECTION_PIN_1, direction);
  digitalWrite(DIRECTION_PIN_2, !direction);
  delay(300);
}

void turn_right() {
  direction = LOW; 
  ledcWrite(PWM_CHANNEL_1, 200);
  ledcWrite(PWM_CHANNEL_2, 255); // dir low
  // contract
  digitalWrite(DIRECTION_PIN_1, direction); // low makes right motor turn cw
  digitalWrite(DIRECTION_PIN_2, !direction); // high makes left motor turn ccw
  delay(1000);
  // expand
  direction = !direction;
  digitalWrite(DIRECTION_PIN_1, direction);
  digitalWrite(DIRECTION_PIN_2, !direction);
  delay(300);
}

void move_forward() {
  direction = LOW; 
  ledcWrite(PWM_CHANNEL_1, 255);
  ledcWrite(PWM_CHANNEL_2, 255); // dir low
  // contract
  digitalWrite(DIRECTION_PIN_1, direction); // low makes right motor turn cw
  digitalWrite(DIRECTION_PIN_2, !direction); // high makes left motor turn ccw
  delay(1000);
  // expand
  direction = !direction;
  digitalWrite(DIRECTION_PIN_1, direction);
  digitalWrite(DIRECTION_PIN_2, !direction);
  delay(300);
}

void stop() {
  ledcWrite(PWM_CHANNEL_1, 0);
  ledcWrite(PWM_CHANNEL_2, 0);
}
