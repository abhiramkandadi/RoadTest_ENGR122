/*
 * Group Information: Section G2, Group 8
 * Team Members: Abhiram Reddy Kandadi, Brendan Wujek, Joao Vitor Ferreira
 * Stevens Honor Pledge: "I pledge my honor that I have abided by the Stevens Honor System."
 * Task 2: Detect an Obstacle and make a stop
 */

#include <Servo.h> 
#include <Ultrasonic.h>

Ultrasonic ultrasonic_left(D4, D7);   
Ultrasonic ultrasonic_center(D5, D8); 
Ultrasonic ultrasonic_right(D1, D2);  

#define motor1pin D3 
#define motor2pin D6 

const int STOP_DIST = 100; // 100 mm 

Servo motor1; 
Servo motor2;  


//Fucntion to Drive forward
void driveForward() {
  motor1.write(113); 
  motor2.write(113);
}

//Stop the motors
void stopMotors() {
  motor1.write(90);
  motor2.write(90);
}

void setup() {
  Serial.begin(115200);
  motor1.attach(motor1pin);  
  motor2.attach(motor2pin);  
  
  delay(2000); 
}

void loop() {
  int center_distance = ultrasonic_center.read(CM) * 10;
  
  // Print data 
  Serial.print("Task 2 | Center Sensor (mm): ");
  Serial.println(center_distance);
  
  delay(100); 

  if (center_distance > STOP_DIST || center_distance == 0) {
    driveForward();
  } 
  else {
    stopMotors();
  }
}