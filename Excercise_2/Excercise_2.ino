// Write the word you want the LED:s to blink out in morse code.
String Word = "SOS";
// change sound to any number =! 0 to activate sound
int sound = 1;


int morseTic = 150;
int morseLongTic = 2*morseTic;
int morseAlphabet[][5] = {
     {1,2},
     {2,1,1,1,0},
     {2,1,2,1,0},
     {2,1,1,0},
     {1,0},
     {1,1,2,1,0},
     {2,2,1,0},
     {1,1,1,1,0},
     {1,1,0},
     {1,2,2,2,0},
     {2,1,2,0},
     {1,2,1,1,0},
     {2,2,0},
     {2,1,0},
     {2,2,2,0},
     {1,2,2,1,0},
     {2,2,1,2,0},
     {1,2,1,0},
     {1,1,1,0},
     {2,0},
     {1,1,2,0},
     {1,1,1,2,0},
     {1,2,2,0},
     {2,1,1,2,0},
     {2,1,2,2,0},
     {2,2,1,1,0},
};
char refAlphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(12, OUTPUT);
  pinMode(13,OUTPUT);

  for (int i = 0; i < 3; i++) {
    for(int j = 0; j < 5; j++) {
      Serial.println(morseAlphabet[i][j]);
    }
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  MorseCode(Word);
}

void MorseCode(String word) {
  for (int i = 0; i < word.length(); i++) {
    char letter = word.charAt(i);
    Serial.println(letter);
    
    int indexAlph = 0;
    for(int j = 0; j < strlen(refAlphabet); j++) {
      if (letter == refAlphabet[j]) {
        indexAlph = refAlphabet[j]-65;
      }
    }    

    int aryLength = 0;
    while(morseAlphabet[indexAlph][aryLength]!=0) {
      aryLength++;
    }
      for(int k = 0; k < aryLength; k++) {
        int ticLength;
        if (morseAlphabet[indexAlph][k] == 1) {
          ticLength = morseTic;
          int test = morseAlphabet[indexAlph][k];
        } else if (morseAlphabet[indexAlph][k] == 2){
          ticLength = morseLongTic;
        } else {
          Serial.println("RIP");
        }
          digitalWrite(13,HIGH);
          digitalWrite(12,HIGH);
          if( sound != 0) {
            tone(4, 3000, ticLength);
          }
          delay(ticLength);
          digitalWrite(13,LOW);
          digitalWrite(12,LOW);
          delay(ticLength);
      }
      delay(500);
  }
   delay(5000);
}

