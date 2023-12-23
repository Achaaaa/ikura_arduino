#include "metro.h"
#include "emitter.h"
#include "Prize.h"
#include <EEPROM.h>
#include <ArduinoOSCWiFi.h>
#include <WiFi.h>
const char* ssid = "HappyDream";
const char* password = "yppahyrevmi";
String host = "192.168.0.109";

int PrizePin_0 = 32 ;
int PrizePin_1 = 34;
int PrizePin_2 = 35;

int WinSignal;
int WinSignal_prev;

Metro metro;
Emitter emitter;
bool isEmitting;
int EmitCount;
long EmitStamp;

Prize prize0;
Prize prize1;
Prize prize2;

void setup() {
  metro.set(2500);
  Serial.begin(19200);
  int cnt = 0;
  prize0.set(PrizePin_0);
  prize1.set(PrizePin_1);
  prize2.set(PrizePin_2);
  Serial.printf("Connecting to %s\n", ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    cnt++;
    delay(500);
    Serial.print(".");
    if (cnt % 10 == 0) {
      WiFi.disconnect();
      WiFi.begin(ssid, password);
      Serial.println("");
    }
    if (cnt >= 30) {
      ESP.restart();
    }
  }
  emitter.set(15);
  Serial.print(WiFi.localIP());
  OscWiFi.subscribe(9001, "/fromUnity/ikura/win", WinSignal);
}

void loop() {
  Serial.print(analogRead(PrizePin_0));
  Serial.print("\t");  
  Serial.print(analogRead(PrizePin_1));
  Serial.print("\t");   
  Serial.print(analogRead(PrizePin_2));
  Serial.println("\t");    
  if (WinSignal_prev == 0 && WinSignal == 1) {
    Serial.println("Win");
    emitter.emit(180);
    EmitCount = 0;
    isEmitting = true;
    EmitStamp = millis();
  }
  if (isEmitting) {
    if (3000 < millis() - EmitStamp) {
      emitter.emit(90);
      isEmitting = false;
    }
  }
  
//  if (Serial.available() > 0) {
//    OscWiFi.send(host.c_str(), 9000, "/toUnity/ikura/credit", Serial.read());
//  }
  if(prize0.update()){
    OscWiFi.send(host.c_str(), 9000, "/toUnity/ikura/credit", 1);
    Serial.println("000000000000000000000");
  }
  if(prize1.update()){
    OscWiFi.send(host.c_str(), 9000, "/toUnity/ikura/credit", 1);
    Serial.println("111111111111111111111");
  }
  if(prize2.update()){
    OscWiFi.send(host.c_str(), 9000, "/toUnity/ikura/credit", 1);
    Serial.println("222222222222222222222");
  }
  WinSignal_prev = WinSignal;
  WinSignal = 0;
  OscWiFi.update();
}
