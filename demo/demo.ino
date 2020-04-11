/*
Demo code
Arthor: ChiangHaoWei
Date: 2020/04/01
*/
#define EN1 6
#define EN2 3
#define IN1 5
#define IN2 7
#define IN3 2
#define IN4 4

void setup() {
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
  // put your main code here, to run repeatedly:
  foreward();
  delay(1000);
  backward();
  delay(1000);
  turnRight();
  delay(1000);
  turnLeft();
  delay(1000);
  Right();
  delay(1000);
  Left();
  delay(1000);
  stopMoving();
  delay(1000);
}
