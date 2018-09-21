#include <Servo.h>
Servo servoLeft;
Servo servoRight;

float fullSpeed = 0.165;
float distance = 2;
float travelTime = (distance/fullSpeed)*1000;

float wheelBase = 0.101; // [m] distance between the wheels
 
void setup() {
  Serial.begin(9600);
  tone(4,3000,1000);
  delay(1000);

  servoLeft.attach(12);
  servoRight.attach(11);
  //FullSpeedAhead(travelTime);
  RightCircularTurn(0.5, 5000);
  
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

void RightCircularTurn(float radius,int delayTime) {
  int outerWheelSpeed = 1600;
  float innerWheelSpeed = 1500+(100*(1-(radius+wheelBase)/radius));
  Serial.println(innerWheelSpeed);
  servoLeft.writeMicroseconds(outerWheelSpeed);
  servoRight.writeMicroseconds(innerWheelSpeed);
  delay(delayTime);
}

void RightQuarterTurn(int delayTime) {
  servoLeft.writeMicroseconds(1450);
  servoRight.writeMicroseconds(1450);
  delay(delayTime);
}

void LeftQuarterTurn(int delayTime) {
  servoLeft.writeMicroseconds(1550);
  servoRight.writeMicroseconds(1550);
  delay(delayTime);
}

void FullSpeedAhead(float delayTime) {
  // ~0.18 m/s
  servoRight.writeMicroseconds(1345);
  servoLeft.writeMicroseconds(1700);
  delay(delayTime);
}
void FullSpeedBackwards(float delayTime) {
  // ~0.18 m/s
  servoLeft.writeMicroseconds(1365);
  servoRight.writeMicroseconds(1700);
  delay(delayTime);
}
