void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Beep");

  tone(4, 3000, 1000);
  delay(1000);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("Waiting for Reset...");
  delay(1000);

}
