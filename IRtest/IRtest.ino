/*
IRtest
Author: ChiangHaoWei
Date: 2020/04/09
*/
#include <SoftwareSerial.h>
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  byte Pin[6] = {A0, A1, A2, A3, A4, A5};
  for (int i = 0; i < 6; i++){
    int val = analogRead(Pin[i]);
    Serial.print(i);
    Serial.print("=");
    Serial.println(val);
  }
  Serial.println(" ");
  delay(3000);
}
