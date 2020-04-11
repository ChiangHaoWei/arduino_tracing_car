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

void test(){
  MotorWriting(150, 125);
  delay(3000);
  MotorWriting(-150, 125);
  delay(3000);
  MotorWriting(150, -125);
  delay(3000);
  MotorWriting(-150, -125);
  delay(3000);
}

void loop() {
  int left = 75;
  int right = 75;
  byte error[3] = {-80, -20, 0};
  byte left_pin[3] = {A0, A1, A2};
  byte right_pin[3] = {A5, A4, A3};
  for (byte i = 0; i < 3; i++) {
    if (analogRead(left_pin[i]) > 250) {
      left += error[i];
      Serial.print("left ");
      Serial.print(i);
      Serial.println(analogRead(left_pin[i]));
      break;
     }
     if (analogRead(right_pin[i]) > 250) {
      right += error[i];
      Serial.print("Right ");
      Serial.print(i);
      Serial.println(analogRead(right_pin[i]));
      break;
     }
   MotorWriting(right, left);
  }
}
