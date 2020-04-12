#include <SoftwareSerial.h>
#define EN1 6
#define EN2 3
#define IN1 5
#define IN2 7
#define IN3 2
#define IN4 4
byte Pin[6] = {A0, A1, A2, A3, A4, A5};
void setup() {
  // put your setup code here, to run once:
    for (byte i = 2; i < 8; i++) {
    pinMode(i, OUTPUT);
    pinMode(Pin[i-2], INPUT);
    Serial.begin(9600);
  }
}

void MotorWriting(int vR, int vL){
  if ((vR > 0) && (vL > 0)) {
    analogWrite(EN1, vR);
    analogWrite(EN2, vL);
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
  }
  else if ((vR > 0) && (vL < 0)) {
    analogWrite(EN1, vR);
    analogWrite(EN2, -vL);
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
  }
  else if ((vR < 0) && (vL > 0)) {
    analogWrite(EN1, -vR);
    analogWrite(EN2, vL);
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
  }
  else if ((vR < 0) && (vL < 0)) {
    analogWrite(EN1, -vR);
    analogWrite(EN2, -vL);
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
  }
}

void tracking(){
  int l3 = digitalRead(Pin[0]);
  int l2 = digitalRead(Pin[1]);
  int l1 = digitalRead(Pin[2]);
  int r1 = digitalRead(Pin[3]);
  int r2 = digitalRead(Pin[4]);
  int r3 = digitalRead(Pin[5]);
  
  double error = 1*l3 + 0.5*l2 + 0.25*l1 - 0.75*(l3 == l2 && l3==1)- 0.5*(l1 == l2 && l1==1)- 0.25*(l1 == 1 && l2==0)
                 -(1*r3 + 0.5*r2 - 0.25*r1 - 0.75*(r3 == r2 && r3==1)-0.5*(r1 == r2 && r1==1)-0.25*(r1 == 1 && r2==0)) ;
  double vR = 100 + 100*error;
  double vL = 100 - 100*error;
  //Serial.println(error);
  //delay(2000);

  MotorWriting(vR, vL);
}

void loop() {
  // put your main code here, to run repeatedly:
  tracking();
}
