void setup() {
  pinMode(13, OUTPUT);
  pinMode(8, OUTPUT);
}

void loop() {

  for (int i = 0; i < 50 ; i++) {
    digitalWrite(13, HIGH);
    digitalWrite(8, LOW);
    delay(100);
    digitalWrite(13, LOW);
    digitalWrite(8, HIGH);
    delay(100);
  }
  digitalWrite(13, HIGH);
  digitalWrite(8, HIGH);
  while (true);
}
