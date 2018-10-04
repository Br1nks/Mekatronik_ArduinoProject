#include <Servo.h>
Servo servoLeft;
Servo servoRight;

float fullSpeed = 0.165;
float wheelBase = 0.11; // [m] distance between the wheels
 
void setup() {
  Serial.begin(9600);
  tone(4,3000,1000);
  delay(1000);

  servoLeft.attach(12);
  servoRight.attach(11);
  
  //RightCircularTurn(0.25);
  LeftCircularTurn(0.25);
  
  servoLeft.detach();
  servoRight.detach();
}
void loop() {
}

void STOP(int delayTime) {
  servoLeft.writeMicroseconds(1500);
  servoRight.writeMicroseconds(1500);
  delay(delayTime);
}

void RightCircularTurn(float radius) {
  float pulseVariance;
  int outerWheelSpeed = 1700;
  
  // correction of speedvariance of the servos
  if (radius < 0.15) {
    pulseVariance = 7;
  } else {
    pulseVariance = 16*radius + 7.6;
  }
  
  float innerWheelSpeed = 1500+pulseVariance-(100*(radius/(radius+wheelBase)));
  float delayTime = ((2*(radius+wheelBase)*3.1415)/ fullSpeed)*1000;
  servoLeft.writeMicroseconds(outerWheelSpeed);
  servoRight.writeMicroseconds(innerWheelSpeed);
  delay(delayTime);
}

void LeftCircularTurn(float radius) {
  float pulseVariance;
  int outerWheelSpeed = 1345;
  // correction of speedvariance of the servos
  if (radius < 0.15) {
    pulseVariance = 7;
  } else {
    pulseVariance = 16*radius + 7.6;
  }
  
  float innerWheelSpeed = 1500-pulseVariance+(100*(radius/(radius+wheelBase)));
  float delayTime = ((2*(radius+wheelBase)*3.1415)/ fullSpeed)*1000;
  servoLeft.writeMicroseconds(innerWheelSpeed);
  servoRight.writeMicroseconds(outerWheelSpeed);
  delay(delayTime);
}
