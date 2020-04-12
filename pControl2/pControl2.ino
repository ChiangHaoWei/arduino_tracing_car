#define EN1 6
#define EN2 3
#define IN1 5
#define IN2 7
#define IN3 2
#define IN4 4


byte Pin[6] = {A0, A1, A2, A3, A4, A5};
int weight[11] = {100, 80, 75, 25, 0, 0, 0, -25, -75, -80, -100};

void MotorWriting(int, int);

void setup() {
  for (byte i = 2; i < 8; i++) {
    pinMode(i, OUTPUT);
    pinMode(Pin[i-2], INPUT);
  }
}

void loop() {
  int detected[11] = {0,0,0,0,0,0,0,0,0,0,0};
  byte previous = 0;
  byte j = 0;
  int vL = 0, vR = 0;
  int error;
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
  for (byte i = 0; i < 11; i++) {
    error = error + (detected[i] * weight[i]);
  }

  vL = 76 -error ;
  vR = 57 + 0.75 * error;
  MotorWriting(vL, vR);
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
