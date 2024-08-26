#include <Servo.h>

const int trigPin = 9;
const int echoPin = 10;
const int servoPin = 11;

// Motor driver pins
const int motor1Pin1 = 3;
const int motor1Pin2 = 4;
const int motor2Pin1 = 5;
const int motor2Pin2 = 6;
const int motor3Pin1 = 7;
const int motor3Pin2 = 8;
const int motor4Pin1 = 12;
const int motor4Pin2 = 13;

Servo gripper;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(14, OUTPUT); // A0 as digital pin 14
  pinMode(15, OUTPUT); // A1 as digital pin 15
  pinMode(2, OUTPUT);
  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(motor2Pin1, OUTPUT);
  pinMode(motor2Pin2, OUTPUT);
  pinMode(motor3Pin1, OUTPUT);
  pinMode(motor3Pin2, OUTPUT);
  pinMode(motor4Pin1, OUTPUT);
  pinMode(motor4Pin2, OUTPUT);

  gripper.attach(servoPin);

  Serial.begin(9600);
  digitalWrite(14, HIGH); // Turn on A0
  digitalWrite(15, LOW);  // Turn off A1
  digitalWrite(2, HIGH);
}

void loop() {
  long duration, distance;

  // Send pulse
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Measure pulse width
  duration = pulseIn(echoPin, HIGH);
  distance = (duration / 2) / 29.1;

  Serial.print("Distance: ");
  Serial.println(distance);

  if (distance >= 15 && distance <= 25) {
    // Stop and activate gripper
    digitalWrite(14, LOW); // Turn off A0
    digitalWrite(15, HIGH); // Turn on A1
    digitalWrite(2, LOW);
    stopMotors();
    gripper.write(180); // Open gripper
    delay(1000); // Hold for a second

    turnAround();
    delay(1000); // Turn for a second

    moveForward();
    delay(3000); // Move forward for 3 seconds

    stopMotors();
    gripper.write(0); // Close gripper
    delay(1000);
    
    turnAround();
    
    delay(1000);
    digitalWrite(14, HIGH); // Turn off A0
    digitalWrite(15, LOW); // Turn on A1
    digitalWrite(2, HIGH);
    delay(3000);
    shutdownRobot();
  } else {
    // Move forward
    digitalWrite(14, HIGH); // Turn on A0
    digitalWrite(15, LOW);  // Turn off A1
    digitalWrite(2, HIGH);
    moveForward();
    delay(1000); // Move forward for 1 second

    stopMotors();
  }
}

void moveForward() {
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, HIGH);
  digitalWrite(motor2Pin2, LOW);
  digitalWrite(motor3Pin1, HIGH);
  digitalWrite(motor3Pin2, LOW);
  digitalWrite(motor4Pin1, HIGH);
  digitalWrite(motor4Pin2, LOW);
}

void turnAround() {
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, HIGH);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, HIGH);
  digitalWrite(motor3Pin1, LOW);
  digitalWrite(motor3Pin2, HIGH);
  digitalWrite(motor4Pin1, LOW);
  digitalWrite(motor4Pin2, HIGH);
}

void stopMotors() {
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, LOW);
  digitalWrite(motor3Pin1, LOW);
  digitalWrite(motor3Pin2, LOW);
  digitalWrite(motor4Pin1, LOW);
  digitalWrite(motor4Pin2, LOW);
}
void shutdownRobot() {
  // Turn off all motor driver pins
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, LOW);
  digitalWrite(motor3Pin1, LOW);
  digitalWrite(motor3Pin2, LOW);
  digitalWrite(motor4Pin1, LOW);
  digitalWrite(motor4Pin2, LOW);

  // Turn off any LEDs
  digitalWrite(14, LOW);
  digitalWrite(15, LOW);
  digitalWrite(2, LOW);

  // Optionally, add code to put Arduino in low power mode or simply do nothing
  while (true) {
    // Loop forever to simulate shutdown
  }
}
