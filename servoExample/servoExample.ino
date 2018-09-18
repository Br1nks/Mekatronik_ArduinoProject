
#include <Servo.h>
Servo servoLeft;
Servo servoRight;
int pinServoLeft = 12;
int pinServoRight = 13;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  servoLeft.attach(pinServoLeft);
  servoRight.attach(pinServoRight);

}

void loop() {
  servoLeft.writeMicroseconds(1550);
  servoRight.writeMicroseconds(1300);
  delay(4000);
  servoLeft.writeMicroseconds(1500);
  servoRight.writeMicroseconds(1500);
  delay(10000);

}
