#define EN1 6
#define EN2 3
#define IN1 5
#define IN2 7
#define IN3 2
#define IN4 4


void setup() {
  for (byte i = 2; i < 8; i++) {
    pinMode(i, OUTPUT);
  }
}
void MotorWriting(int vR, int vL){
  if (vR > 0 && vL > 0) {
    analogWrite(EN1, vR);
    analogWrite(EN2, vL);
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
  }
  else if (vR > 0 && vL < 0) {
    analogWrite(EN1, vR);
    analogWrite(EN2, -vL);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
  }
  else if (vR < 0 && vL > 0) {
    analogWrite(EN1, -vR);
    analogWrite(EN2, vL);
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
  }
  else if (vR < 0 && vL < 0) {
    analogWrite(EN1, -vR);
    analogWrite(EN2, -vL);
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
  }
}
void loop() {
  MotorWriting(150, 125);
  delay(3000);

}
