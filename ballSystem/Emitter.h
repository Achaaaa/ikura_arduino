#include <ESP32Servo.h>
//#include <Servo.h>
Servo sv; //Servoオブジェクト“sv”を作成する
int servoPin;

class Emitter {
  public:
    Emitter() {}
    ~Emitter() {}

    int angle = 0;
    void set(int _servoPin) {
      sv.attach(_servoPin); //svの出力をD6番ピンに割り当てる
      servoPin = _servoPin; 
    }
    void emit(int _num){
      sv.write(_num);
    }
    void stay(){
      sv.detach();
    }

    void update(){
      if (!sv.attached()) {
        sv.attach(servoPin);
      }
    }
};
