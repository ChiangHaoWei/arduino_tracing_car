#include <SoftwareSerial.h>
#include <SPI.h>
#include <MFRC522.h>
#define EN1 6
#define EN2 3
#define IN1 5
#define IN2 7
#define IN3 2
#define IN4 4
#define rxd A0
#define txd A1
#define SS_Pin 9
#define RST_Pin 10


MFRC522 mfrc522(SS_Pin, RST_Pin);
SoftwareSerial BT(rxd, txd);
void setup() {
  Serial.begin(9600);
  BT.begin(9600);
  Serial.println("BT is ready!");
  for (byte i = 2; i < 8; i++){
    pinMode(i, OUTPUT);
  }

}

void forward() {
  analogWrite(EN1, 120);
  analogWrite(EN2, 170);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void backward() {
  analogWrite(EN1, 200);
  analogWrite(EN2, 255);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void turnRight() {
  analogWrite(EN1, 200);
  analogWrite(EN2, 0);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}
void Right() {
  analogWrite(EN1, 250);
  analogWrite(EN2, 180);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}
void turnLeft() {
  analogWrite(EN1, 0);
  analogWrite(EN2, 200);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}
void Left() {
  analogWrite(EN1, 180);
  analogWrite(EN2, 250);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}
void stopMoving(){
  analogWrite(EN1, 0);
  analogWrite(EN2, 0);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void loop() {
  if(!mfrc522.PICC_IsNewCardPresent() || !mfrc522.PICC_ReadCardSerial()){
    goto FuncEnd;
  }
  byte *id = mfrc522.uid.uidByte;
  byte idSize = mfrc522.uid.size;
  byte goID[4] = {0, 135, 96, 201};
  for (byte i = 0; i < idSize; i++) {
    if (goID[i] != id[i]) {
      Serial.println(F("Not available card"));
      goto FuncEnd;
    }
  }
  mfrc522.PICC_HaltA();
  if (BT.available()) {
    char BTRead = BT.read();
    Serial.print(BTRead);
    switch(BTRead) {
      case '0':
      stopMoving();
      break;
      case '1':
        forward();
        break;
      case '2':
        backward();
        break;
      case '3':
        turnLeft();
        break;
      case '4':
        turnRight();
        break;
      case '5':
        Left();
        break;
      case '6':
        Right();
        break;
       default:
       stopMoving();
        break;
    }
  }
  if (Serial.available()) {
    BT.write(Serial.read());
  }
  FuncEnd:;
}
