
#include <Servo.h>

Servo servoLeft;
Servo servoRight;
int pinServoLeft = 12;
int pinServoRight = 13;


void setup() {
  // put your setup code here, to run once:
  tone(4,3000,1000);
  delay(1000);
  
  Serial.begin(9600);
  servoLeft.attach(pinServoLeft);
  servoRight.attach(pinServoRight);

}

void loop() {
  // put your main code here, to run repeatedly:

  for (int pulseWidth = 1380; pulseWidth <=1700; pulseWidth+=10) {
  Serial.print("pulseWidth = ");
  Serial.println(pulseWidth);
  Serial.println("press a key and click");
  Serial.println("Send to start servo...");

  while(Serial.available()==0);
   
  Serial.read();
  Serial.println("Running...");
  servoLeft.writeMicroseconds(pulseWidth);
  servoRight.writeMicroseconds(pulseWidth);
  delay(6000);
  servoLeft.writeMicroseconds(1500);
  servoRight.writeMicroseconds(1500);

  }
}
