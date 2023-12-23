#include "metro.h"
#include "emitter.h"
#include "Prize.h"
#include "LED.h"
#include <EEPROM.h>
#include <ArduinoOSCWiFi.h>
#include <WiFi.h>
const char* ssid = "HappyDream";
const char* password = "yppahyrevmi";
String host = "192.168.0.109";

int PrizePin_right = 32 ;
int PrizePin_left = 34;
int PrizePin_center = 35;

int WinSignal;
int WinSignal_prev;

Metro metro;
Emitter emitter;
bool isEmitting;
int EmitCount;
long EmitStamp;

int led_status = 1;

Prize prize_right;
Prize prize_left;
Prize prize_center;

LED led;

void setup() {
  metro.set(2500);
  Serial.begin(19200);
  led.set();
  int cnt = 0;
  prize_right.set(PrizePin_right,70);
  prize_left.set(PrizePin_left,60);
  prize_center.set(PrizePin_center,70);
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
  Serial.print(analogRead(PrizePin_left));
  Serial.print("\t");   
  Serial.print(analogRead(PrizePin_center));
  Serial.print("\t");  
  Serial.print(analogRead(PrizePin_right));
  Serial.print("\t");    
  if (WinSignal_prev == 0 && WinSignal == 1) {
    Serial.println("Win");
    emitter.emit(180);
    EmitCount = 0;
    isEmitting = true;
    EmitStamp = millis();
    led_status = 2;
  }
  if (isEmitting) {
    if (3000 < millis() - EmitStamp) {
      emitter.emit(90);
      led_status = 0;
      isEmitting = false;
    }
  }

  led.update(led_status);
  if(16<led.pixel_index)led_status = 0;
  
  
//  if (Serial.available() > 0) {
//    OscWiFi.send(host.c_str(), 9000, "/toUnity/ikura/credit", Serial.read());
//  }
  if(prize_right.update()){
    led_status = 1;
    OscWiFi.send(host.c_str(), 9000, "/toUnity/ikura/credit", 1);
    Serial.println("000000000000000000000");
  }
  if(prize_left.update()){
    led_status = 1;
    OscWiFi.send(host.c_str(), 9000, "/toUnity/ikura/credit", 1);
    Serial.println("111111111111111111111");
  }
  if(prize_center.update()){
    led_status = 1;
    OscWiFi.send(host.c_str(), 9000, "/toUnity/ikura/credit", 1);
    Serial.println("222222222222222222222");
  }
  WinSignal_prev = WinSignal;
  WinSignal = 0;
  OscWiFi.update();
}
