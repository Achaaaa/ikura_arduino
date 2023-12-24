#include <Adafruit_NeoPixel.h>
#define pixelPin  19
#define pixelsNum 35

Adafruit_NeoPixel Pixels(pixelsNum, pixelPin, NEO_GRB + NEO_KHZ800);

class LED {
  public:
    LED() {}
    ~LED() {}

    float pixel_timer;
    int pixel_index;
    int switch_status;
    int switch_status_prev;
    int lightcount;

    void set() {
      Pixels.begin();
    }

    void update(int _switch) {
      //pixels
      switch_status = _switch;
      pixel_timer++;
      if (switch_status != switch_status_prev) {
        pixel_timer = 0;
        pixel_index = 0;
      }
      switch (switch_status) {
        case 0:
          Pixels.clear();
          if (pixel_timer < 60) {
            for (int i = 0;  i < pixelsNum; i += 2) {
              Pixels.setPixelColor(i, Pixels.Color(255, 140, 0));
            }
            for (int i = 1;  i < pixelsNum; i += 2) {
              Pixels.setPixelColor(i, Pixels.Color(255, 255, 255));
            }
          } else if (60 < pixel_timer) {
            for (int i = 0;  i < pixelsNum; i += 2) {
              Pixels.setPixelColor(i, Pixels.Color(255, 255, 255));
            }
            for (int i = 1;  i < pixelsNum; i += 2) {
              Pixels.setPixelColor(i, Pixels.Color(255, 140, 0));
            }
          }
          Pixels.show();
          if (120 < pixel_timer) pixel_timer = 0;
          break;
        case 1:
          Pixels.clear();
          for (int i = 0; i < 2; i++) {
            Pixels.setPixelColor(pixel_index + i, Pixels.Color(255, 0, 0));
            Pixels.setPixelColor((pixelsNum - 1) - pixel_index - i, Pixels.Color(255, 0, 0));
          }
          Pixels.show();
          if (pixel_index / 2 < pixel_timer) {
            pixel_index++;
            pixel_timer = 0;
          }

          break;
        case 2:
          Pixels.clear();
          if (pixel_timer < 20) {
            for (int i = 0;  i < pixelsNum; i++ ) {
              Pixels.setPixelColor(i, Pixels.Color(255, 0, 0));
            }
          } else if (20 < pixel_timer) {
            for (int i = 0;  i < pixelsNum; i++) {
              Pixels.setPixelColor(i, Pixels.Color(255, 140, 0));
            }
          }
          Pixels.show();
          if (40 < pixel_timer) pixel_timer = 0;
          break;
      }
      switch_status_prev = switch_status;
    }
};
