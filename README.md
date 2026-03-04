# ENGR 122: Week 5 Road Test - Group 8

## Project Overview
[cite_start]This repository contains the Arduino sketches for the Week 5 Road Test of the ENGR 122 Design of Systems course at Stevens Institute of Technology[cite: 388, 389, 390]. [cite_start]The code evaluates the basic driving performance of a custom-built, differential-drive robot utilizing continuous rotation servos and an array of ultrasonic sensors for autonomous navigation[cite: 423, 424]. 

Because the project strictly prohibits continuous time-based control (e.g., single long `delay()` functions), all tasks are programmed using rapid iterative loops and finite state machines driven by `millis()`.

## Team Information
* **Section:** G2
* **Group:** 8
* **Team Members:** Abhiram Reddy Kandadi, Brendan Wujek, Joao Vitor Ferreira
* **Stevens Honor Pledge:** *"I pledge my honor that I have abided by the Stevens Honor System."*

## Hardware & Wiring
* **Microcontroller:** WeMos D1 R2 (ESP8266)
* **Actuators:** 2x Continuous Rotation Servos
* **Sensors:** 3x HC-SR04 Ultrasonic Sensors (Mounted via custom 3D-printed chassis: Center facing forward, Left/Right angled outward at 35 degrees)

### Pin Mapping
| Component | WeMos Pin | Notes |
| :--- | :--- | :--- |
| **Left Motor** | `D3` | Controlled via `Servo.h` |
| **Right Motor** | `D6` | Controlled via `Servo.h` |
| **Left Ultrasonic** | Trig: `D4`, Echo: `D7` | Angled 35° left |
| **Center Ultrasonic**| Trig: `D5`, Echo: `D8` | Forward-facing |
| **Right Ultrasonic** | Trig: `D1`, Echo: `D2` | Angled 35° right |

*(Note: Pins D1 and D2 are the default I2C pins for the SSD1306 OLED display. The OLED display code has been stripped from this Week 5 submission to free up the pins for the right-side ultrasonic sensor).*

## Software Dependencies
The following libraries are required to compile these sketches:
* `<Servo.h>`: Built-in Arduino library for motor PWM control.
* `<Ultrasonic.h>`: Library used to abstract pulse-timing logic for the HC-SR04 sensors.

## Task Breakdown
[cite_start]Per the assignment requirements, each task is programmed as a separate runnable Arduino Sketch[cite: 429, 430].

1. **Task 1: Straight Driving Performance (`Task1.ino`)**
   * [cite_start]**Goal:** Make your robot go straight at least 6 feet at a maximum speed[cite: 435].
   * **Logic:** Utilizes empirically calibrated saturation values to achieve maximum RPM without signal flatlining. 

2. **Task 2: Detect Wall and Stop (`Task2.ino`)**
   * [cite_start]**Goal:** Detect an obstacle (wall) using Ultrasonic sensors and make it stop within 4 inches of the obstacle[cite: 447].
   * **Logic:** Continuously polls the center ultrasonic sensor. When the distance drops below `100 mm` (~3.93 inches), it commands the motors to enter their "dead band" (`90` PWM) to halt.

3. **Task 3: Move to Wall, Return, and Stop (`Task3.ino`)**
   * [cite_start]**Goal:** Make your robot go straight and detect an obstacle (wall) using Ultrasonic sensors and return to the start zone and stop[cite: 462].
   * **Logic:** Utilizes a finite state machine. It records the exact forward travel time using `millis()`, executes a high-torque zero-radius turn, and drives back for that exact recorded duration before cutting the motors.

## Calibration & Trimming
Due to manufacturing tolerances, the right motor spins naturally faster than the left. Software trimming was applied to correct the chassis drift and optimize the zero-radius turn:
* **Forward Trim:** Left Motor = `115`, Right Motor = `111` (Slows the fast right motor, boosts the slow left motor).
* **Turn Trim (High Power):** Left Motor = `132`, Right Motor = `52`.
* **Turn Duration:** `650 ms` (Calibrated specifically to achieve a true 180-degree sweep at the trimmed power levels).
* **Dead Band (Stop):** Both motors stop completely at `90` PWM.