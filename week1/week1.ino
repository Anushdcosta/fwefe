#include <Servo.h>

// servo initializers
Servo myservo;  // create servo object to control a servo

const int trigPin = 7;
const int echoPin = 6;
long duration;
int distance;

int leds[3] = {9,10,11};
void setup()
{
  for (int led : leds) {
  	pinMode(led, OUTPUT);
  }
  myservo.attach(3);  
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT); 
  Serial.begin(9600); 
}

void loop()
{
  digitalWrite(trigPin, LOW);		   
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);		   
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  duration = pulseIn(echoPin, HIGH);   
  
  distance = duration * 0.034 / 2;	   
  
  (distance > 100)? digitalWrite(leds[2], HIGH):digitalWrite(leds[2],LOW);
  (distance > 50)? digitalWrite(leds[1], HIGH):digitalWrite(leds[1],LOW);
  (distance > 25 )? digitalWrite(leds[0], HIGH):digitalWrite(leds[0],LOW);
  
  if (distance > 100){
    myservo.write(180);
  } else if (distance < 25) {
    myservo.write(0);
  } else {
    int val = map(distance, 25, 100, 1, 179);
    myservo.write(val);
  }
}