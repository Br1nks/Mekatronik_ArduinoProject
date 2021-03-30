#include <Servo.h>

Servo servoLeft;
Servo servoRight;

const int setPoint = 1;
const int kpl = -25;
const int kpr = -25;
const int respTime = 20;

void setup() {
  pinMode(10,INPUT);
  pinMode(9,OUTPUT);
  pinMode(3,INPUT);
  pinMode(2,OUTPUT);

  tone(4,3000,1000);
  delay(1000);
  servoLeft.attach(12);
  servoRight.attach(11);
}

void loop() {
  int irLeft = irDistance(9,10);
  int irRight = irDistance(2,3);

  int driveLeft = (setPoint - irLeft) * kpl;
  int driveRight = (setPoint - irRight) * kpr;

  maneuver(driveLeft, driveRight, respTime);
}

int irDistance(int irLedPin, int irReceivePin) {
  int distance = 0;
  for(long f = 38000; f <= 42000; f+=1000) { 
    distance+=irDetect(irLedPin,irReceivePin,f);
  }
  return distance;
}

int irDetect(int irLedPin, int irReceiverPin, long frequency) {
  tone(irLedPin,frequency,8);
  delay(1);
  int ir = digitalRead(irReceiverPin);
  delay(1);
  return ir;
}

void maneuver(int speedLeft, int speedRight, int msTime) {
  servoLeft.writeMicroseconds(1500+speedLeft);
  servoRight.writeMicroseconds(1500-speedRight);

  if(msTime == -1) {
    servoLeft.detach();
    servoRight.detach();
  }
  delay(msTime);
}

