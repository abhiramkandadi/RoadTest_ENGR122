/*
 * Group Information: Section G2, Group 8
 * Team Members: Abhiram Reddy Kandadi, Brendan Wujek, Joao Vitor Ferreira
 * Stevens Honor Pledge: "I pledge my honor that I have abided by the Stevens Honor System."
 * Task 3: Move Straight to a wall and return to the start location and stop
 */

#include <Servo.h> 
#include <Ultrasonic.h>

Ultrasonic ultrasonic_left(D4, D7);   
Ultrasonic ultrasonic_center(D5, D8); 
Ultrasonic ultrasonic_right(D1, D2); 

#define motor1pin D3 // LEFT MOTOR
#define motor2pin D6 // RIGHT MOTOR

const int STOP_DIST = 100; 



// 1. FORWARD TRIM 
int leftMotorForward = 114;  
int rightMotorForward = 114; 

// 2. TURN TRIM 
int leftMotorTurn = 122;   
int rightMotorTurn = 62;   

// 3. TURN ANGLE CALIBRATION 
int turnDuration = 650;    

Servo motor1; 
Servo motor2;  

int state = 0; 
unsigned long startTime = 0;
unsigned long forwardDuration = 0;
unsigned long returnStartTime = 0;

void driveForward() {
  motor1.write(leftMotorForward); 
  motor2.write(rightMotorForward);
}

void stopMotors() {
  motor1.write(90);
  motor2.write(90);
}

void turnAround() {
  motor1.write(leftMotorTurn);
  motor2.write(rightMotorTurn);  
  delay(turnDuration); 
  stopMotors();
}

void setup() {
  Serial.begin(115200);
  motor1.attach(motor1pin);  
  motor2.attach(motor2pin);  
  
  delay(2000); 
}

void loop() {
  int center_distance = ultrasonic_center.read(CM) * 10;
  
  Serial.print("Task 3 | State: ");
  Serial.print(state);
  Serial.print(" | Center Dist (mm): ");
  Serial.println(center_distance);
  
  delay(100); 
  
  if (state == 0) {
    startTime = millis();
    state = 1;
  } 
  else if (state == 1) {
    if (center_distance > 0 && center_distance <= STOP_DIST) {
      stopMotors();
      forwardDuration = millis() - startTime; 
      delay(300); 
      state = 2;
    } else {
      driveForward();
    }
  }
  else if (state == 2) {
    turnAround();
    delay(300);
    returnStartTime = millis();
    state = 3;
  }
  else if (state == 3) {
    if (millis() - returnStartTime < forwardDuration) {
      driveForward();
    } else {
      stopMotors();
      state = 4;
    }
  }
  else if (state == 4) {
    // Idle state
  }
}