#include "metro.h"
#include "emitter.h"

Metro metro;
Metro inMetro;
Metro impactMetro;
Metro impactMetro2;
Emitter emitter;
int openTime;
int impactTime;
bool flg;
bool flg2;
int val;
int emitNum;
int emitNumOld;
int impactPin = 2;
int sole_in_pin = 3;
int sole_out_pin = 4;
int led_pin = 9;
int handle_pin = 0;
int impactPower = 0;

void setup() {
  metro.set(2500);
  //  inMetro.set(1000);
  //  impactMetro.set(1000);
  //  impactMetro2.set(1100);
  //emitter.set(9);
  pinMode(handle_pin, INPUT);
  pinMode(5, INPUT);
  pinMode(impactPin, OUTPUT);
  pinMode(sole_in_pin, OUTPUT);
  pinMode(sole_out_pin, OUTPUT);
  pinMode(led_pin, OUTPUT);
  Serial.begin(9600);
  Serial.println("START");
}

void loop() {
  val = analogRead(5) ; //球が射出されてるか確認
  impactPower = map(analogRead(handle_pin), 0, 443, 0, 255); //可変抵抗の値を２５５
  analogWrite(led_pin, 3);
  Serial.print(analogRead(handle_pin)) ;
  Serial.print("\t");
  Serial.print(impactPower) ;
  Serial.print("\t");
  Serial.println(val) ;


  //Serial.println(flg);
  if (metro.update()) {
    flg = true;
  }
  if (flg) {
    if (30 < val) {
      digitalWrite(sole_in_pin, HIGH);
      digitalWrite(sole_out_pin, HIGH);
    }
    openTime++;
    if (7 < openTime) {
      //    if (inMetro.update()) {
      flg2 = true;
      flg = false;
    }
  } else {
    openTime = 0;
    digitalWrite(sole_in_pin, LOW);
    digitalWrite(sole_out_pin, LOW);
  }
  //Serial.println(impactTime);
  //Serial.println(emitter.angle);

  if (flg2) {
    impactTime++;
    //    if (impactMetro.update()) {
    if (60 < impactTime) {
      analogWrite(impactPin, 255);
    }
    //    if (impactMetro2.update()) {
    if (70 < impactTime) {
      flg2 = false;
    }
  } else {
    analogWrite(impactPin, 0);
    impactTime = 0;
  }

  //  if (Serial.available() > 0) {
  //    emitNum = Serial.read();
  //  }
  //  if (emitNum != emitNumOld ) {
  //    emitter.emit(60);
  //    Serial.println("emit");
  //  }
  //  emitNumOld = emitNum;
}
