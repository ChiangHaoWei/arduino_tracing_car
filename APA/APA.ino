#include <SoftwareSerial.h>
#include <SPI.h>
#define EN1 6
#define EN2 3
#define IN1 5
#define IN2 7
#define IN3 2
#define IN4 4
#define rxd 10
#define txd 11

SoftwareSerial BT(rxd, txd);
byte Pin[6] = {A0, A1, A2, A3, A4, A5};
double weight[11] = {1, 0.8, 0.75, 0.27, 0, 0, 0, -0.27, -0.75, -0.8, -1};
const int Kp = 75;
void MotorWriting(double, double);
bool Coner();
bool turning(char);

void setup() {
  // put your setup code here, to run once:
   for (byte i = 2; i < 8; i++) {
    pinMode(i, OUTPUT);
    pinMode(Pin[i-2], INPUT);
  }
  pinMode(13, OUTPUT);
  Serial.begin(9600);
  BT.begin(9600);
  while (!(BT.available())) {
   digitalWrite(13, HIGH); 
  }
  BT.read();
  digitalWrite(13, LOW);
}

void loop() {
  // detected whether the car is in the square
  int detected[11] = {0,0,0,0,0,0,0,0,0,0,0};
  byte j = 0;
  int previous = 0;
  int vL = 0, vR = 0;
  double error = 0;
  char corner = 'c';
  
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
  if (detected[1] && detected[5] && detected[9]) {
    MotorWriting(0, 0);
    BT.write(corner);
    while (!(BT.available())) {
    }
    char BTRead = BT.read();
    while (inConer()) {
      MotorWriting(80, 60);
    }
    switch (BTRead) {
      case 'f':
        MotorWriting(50, 80);
        break;
      case 'l':
        while(turning('1')){
          MotorWriting(-100, 100);
        }
        break;
      case 'r':
        while (turning('r')){
          MotorWriting(100, -100);
        }
        break;
      default:
        break;
    }
  }

  //start tracing
  for (byte i = 0; i < 11; i++) {
    if (detected[i] > 0) {
      detected[i] = 1;
    }
    else {detected[i] = 0;}
    error = error + (detected[i] * weight[i]);
  }
  for (int i = 0; i < 11; i++) {
    if (detected[i] == 1) {
        goto Normal;
    }
    Serial.print(detected[i]);
    Serial.print(" ");
  }
  MotorWriting(-80, -60);
  //MotorWriting(0, 0);
  Serial.println();
  goto FuncEnd;
  Normal:;
  vL = 80 - Kp * error ;
  vR = 60 + 0.75 * (Kp * error);
  MotorWriting(vL, vR);
  FuncEnd:;
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

bool inConer() {
  for (byte i = 0; i < 6; i++) {
    if (digitalRead(Pin[i]) == 0) {return false;} 
  }
  return true;
}

bool turning(char command) {
  switch(command) {
    case 'l':
      if (digitalRead(Pin[0]) && digitalRead(Pin[1])) {
        return false;
      }
      return true;
    case 'r':
      if (digitalRead(Pin[0]) && digitalRead(Pin[1])) {
        return false;
      }
      return true;
  }
}
