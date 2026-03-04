/*
 * Group Information: Section G2, Group 8
 * Team Members: Abhiram Reddy Kandadi, Brendan Wujek, Joao Vitor Ferreira
 * Stevens Honor Pledge: "I pledge my honor that I have abided by the Stevens Honor System."
 * Task 1: Straight Move Performance (@ maximum speed)
 */

#include <Servo.h> 
#include <Ultrasonic.h>

//Initialize 
Ultrasonic ultrasonic_left(D4, D7);   //left
Ultrasonic ultrasonic_center(D5, D8); //center
Ultrasonic ultrasonic_right(D1, D2);  //right

#define motor1pin D3 
#define motor2pin D6 

Servo motor1; 
Servo motor2;  

void driveForwardMax() {
  // Calibrated max speed: Saturation occurs at 140
  motor1.write(140); 
  motor2.write(138);   
}

void setup() {
  Serial.begin(115200);
  motor1.attach(motor1pin);  
  motor2.attach(motor2pin);  
  
  delay(2000); 
}

void loop() {
  int center_distance = ultrasonic_center.read(CM) * 10;
  
  // Print data to the Serial Monitor
  Serial.print("Task 1 | Center Sensor (mm): ");
  Serial.println(center_distance);
  
  driveForwardMax();
  
  delay(150); 
}