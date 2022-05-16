#include <TM1637Display.h>

#define CLK 3
#define DIO 4
int score = 0;

TM1637Display display = TM1637Display(CLK, DIO);

const uint8_t data[] = {0xff, 0xff, 0xff, 0xff};
const uint8_t blank[] = {0x00, 0x00, 0x00, 0x00};

void setup() {
  // Clear the display
  display.clear();
  delay(1000);
}

void loop() {
  // Set the brightness
  display.setBrightness(3);
  score = score+1;
  countScore();
  delay(300);
}

void countScore(){
  display.showNumberDec(score);
}
