// Two pin definition techniques
#define motorA 5
#define motorB 6

const int trigPin = 8;
const int echoPin = 9;
long duration;
int distance;

void setup() {
  pinMode(motorA,OUTPUT);
  pinMode(motorB,OUTPUT);
  
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT); 
  Serial.begin(9600); 
}

void loop() {
  digitalWrite(trigPin, LOW);		   
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);		   
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  duration = pulseIn(echoPin, HIGH);   
  
  distance = duration * 0.034 / 2;	 
  
  Serial.println(distance);
  
  if (distance > 50) {
    analogWrite(motorB,255);
    digitalWrite(motorA,LOW);
    delay(1000);
  } else if (distance < 30) {
     analogWrite(motorA,255);
  	 digitalWrite(motorB,LOW);
     delay(1000);
  }
}