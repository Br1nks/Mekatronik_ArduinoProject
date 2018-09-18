#include <Servo.h>
Servo servoLeft;
Servo servoRight;

float fullSpeed = 0.178;
float distance = 0.1;
float travelTime = (distance/fullSpeed)*1000;

void setup() {
  tone(4,3000,1000);
  delay(1000);

  servoLeft.attach(11);
  servoRight.attach(12);

  FullSpeedAhead(travelTime);;
  
  servoLeft.detach();
  servoRight.detach();
  
}

void loop() {
}

void measureDistance() {
  
}
void STOP(int delayTime) {
  servoLeft.writeMicroseconds(1500);
  servoRight.writeMicroseconds(1500);
  delay(delayTime);
}

void LeftQuarterTurn(int delayTime) {
  servoLeft.writeMicroseconds(1450);
  servoRight.writeMicroseconds(1450);
  delay(delayTime);
}

void RightQuarterTurn(int delayTime) {
  servoLeft.writeMicroseconds(1550);
  servoRight.writeMicroseconds(1550);
  delay(delayTime);
}

void FullSpeedAhead(float delayTime) {
  // ~0.18 m/s
  servoLeft.writeMicroseconds(1345);
  servoRight.writeMicroseconds(1700);
  delay(delayTime);
}

