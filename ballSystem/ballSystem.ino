#include "metro.h"
#include "emitter.h"
#include "Prize.h"
#include "LED.h"
#include <EEPROM.h>
#include <ArduinoOSCWiFi.h>
#include <WiFi.h>
//const char* ssid = "HappyDream";
//const char* ssid = "kaedamamuryo2.4";
const char* ssid = "CR_ikura";
//const char* password = "yppahyrevmi";
//const char* password = "ramengekisenku";
const char* password = "hokkaidouminosachi";
String host = "192.168.0.109";//リビオメゾンWindows

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

int led_status = 0;

Prize prize_right;
Prize prize_left;
Prize prize_center;

LED led;

void setup() {
  metro.set(2500);
  Serial.begin(19200);
  led.set();
  int cnt = 0;
  prize_right.set(PrizePin_right,60);
  prize_left.set(PrizePin_left,40);
  prize_center.set(PrizePin_center,60);
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
  Serial.println(WiFi.localIP());
  OscWiFi.subscribe(9001, "/fromUnity/ikura/win", WinSignal);
}

void loop() {
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
  prize_left.update();
  Serial.print("\t");
  prize_center.update();
  Serial.print("\t");
  prize_right.update();
  Serial.println("");
  
  if(prize_right.observe()){
    if(led_status != 2) led_status = 1;
    OscWiFi.send(host.c_str(), 9000, "/toUnity/ikura/credit", 1);
    Serial.println("000000000000000000000");
  }
  if(prize_left.observe()){
    if(led_status != 2) led_status = 1;
    OscWiFi.send(host.c_str(), 9000, "/toUnity/ikura/credit", 1);
    Serial.println("111111111111111111111");
  }
  if(prize_center.observe()){
    if(led_status != 2) led_status = 1;
    OscWiFi.send(host.c_str(), 9000, "/toUnity/ikura/credit", 1);
    Serial.println("222222222222222222222");
  }
  WinSignal_prev = WinSignal;
  WinSignal = 0;
  OscWiFi.update();
}
