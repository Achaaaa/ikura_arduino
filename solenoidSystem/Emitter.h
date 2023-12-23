//#include <ESP32Servo.h>
#include <Servo.h>
Servo sv; //Servoオブジェクト“sv”を作成する

class Emitter {
  public:
    Emitter() {}
    ~Emitter() {}

    int angle = 0;
    void set(int _servoPin) {
      sv.attach(_servoPin); //svの出力をD6番ピンに割り当てる
    }
    void emit(int _num){
      angle += _num;
      sv.write(angle);
    }
};
