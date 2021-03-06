/*
p control version 2
Author: Chiang Hao Wei
Date: 2020/04/10
*/
#define EN1 6
#define EN2 3
#define IN1 5
#define IN2 7
#define IN3 2
#define IN4 4


byte Pin[6] = {A0, A1, A2, A3, A4, A5};
double weight[11] = {1, 0.8, 0.75, 0.27, 0, 0, 0, -0.27, -0.75, -0.8, -1};
const int Kp = 75;

void MotorWriting(int, int);

void setup() {
  for (byte i = 2; i < 8; i++) {
    pinMode(i, OUTPUT);
    pinMode(Pin[i-2], INPUT);
  }
  //Serial.begin(9600);
}

void loop() {
  int detected[11] = {0,0,0,0,0,0,0,0,0,0,0};
  byte previous = 0;
  byte j = 0;
  double vL = 0, vR = 0;
  int error = 0;
  for (byte i = 0; i < 6; i++) {
    detected[j] = digitalRead(Pin[i]);
    if (detected[j] && previous) {
      detected[j-2] = 0;
      detected[j-1] = 1;
      detected[j] = 0;
    }
    previous = detected[j];
    j+=2;
  }

  /*
  for (int i = 0; i < 11; i++) {
    Serial.print(detected[i]);
    Serial.print(" ");
  }
  Serial.println();*/
  
  for (byte i = 0; i < 11; i++) {
    if (detected[i] > 0) {
      detected[i] = 1;
    }
    else {detected[i] = 0;}
    error = error + (detected[i] * weight[i]);
  }
  /*
  Serial.print("vL = ");
  Serial.println(vL);
  Serial.print("vR = ");
  Serial.println(vR);
  for (int i = 0; i < 11; i++) {
    Serial.print(detected[i]);
    Serial.print(" ");
  }
  Serial.println();*/

  vL = 76 - Kp * error ;
  vR = 57 + 0.75 * (Kp * error);
  /*
  Serial.print("error = ");
  Serial.println(error);
  Serial.print("vL = ");
  Serial.println(vL);
  Serial.print("vR = ");
  Serial.println(vR);
  delay(3000);*/
  MotorWriting(vL, vR);
}

void MotorWriting(double vL, double vR) {
  if ((vR > 0) && (vL > 0)) {
    analogWrite(EN1, vL);
    analogWrite(EN2, vR);
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
  }
  else if ((vR > 0) && (vL < 0)) {
    analogWrite(EN1, -vL);
    analogWrite(EN2, vR);
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
  }
  else if ((vR < 0) && (vL > 0)) {
    analogWrite(EN1, vL);
    analogWrite(EN2, -vR);
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
  }
  else {
    analogWrite(EN1, -vL);
    analogWrite(EN2, -vR);
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
  }
}
