#include <Servo.h>

Servo servoLeft;
Servo servoRight;

byte wLeftOld;
byte wRightOld;
byte counter;

void setup() {
  tone(4,3000,1000);
  delay(1000);
  
  // Whiskers
  pinMode(7,INPUT);
  pinMode(5,INPUT);
  
  // LEDS
  pinMode(10,OUTPUT);
  pinMode(13,OUTPUT);

  // Servos
  servoLeft.attach(12);
  servoRight.attach(11);

  wLeftOld = 0;
  wRightOld = 1;
  counter = 0;
}

void loop() {
  byte wLeft = digitalRead(5);
  byte wRight = digitalRead(7);

  if (wLeft != wRight) {
    if ((wLeft != wLeftOld) &&  (wRight != wRightOld)) {
      counter++;
      wLeftOld = wLeft;
      wRightOld = wRight;
      
      if(counter == 4) {
        wLeft = 0;
        wRight = 0;
        counter = 0;
      }
    } else {
      counter = 0;
    }
  }

  long randomTurnDegree = random(20,180)*20/3;

  if ((wLeft == 0) && (wRight == 0)) {
    digitalWrite(13,HIGH);
    digitalWrite(10,HIGH);
    backward(1000);
    turnLeft(800);
  } else if (wLeft ==0) {
    digitalWrite(13,HIGH);
    digitalWrite(10,LOW);
    backward(1000);
    turnRight(randomTurnDegree);
    //turnRight(400);

  } else if (wRight == 0) {
    digitalWrite(13,LOW);
    digitalWrite(10,HIGH);
    backward(1000);
    turnLeft(randomTurnDegree);
    //turnLeft(400);

  } else {
    digitalWrite(13,LOW);
    digitalWrite(10,LOW);
    forward(20);
  }
}

void forward(int time) {
  servoLeft.writeMicroseconds(1700);
  servoRight.writeMicroseconds(1345);
  delay(time);
}
void backward(int time) {
  servoLeft.writeMicroseconds(1345);
  servoRight.writeMicroseconds(1700);
  delay(time);
}
void turnLeft(int time) {
  servoLeft.writeMicroseconds(1345);
  servoRight.writeMicroseconds(1345);
  delay(time);
}
void turnRight(int time) {
  servoLeft.writeMicroseconds(1700);
  servoRight.writeMicroseconds(1700);
  delay(time);
}

