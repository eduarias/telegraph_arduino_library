#include "telegraph.h"

const byte OUTPUT_PIN = 9;
const unsigned int DIT_LENGTH = 200;

Led led(OUTPUT_PIN);
Telegraph telegraph(&led, DIT_LENGTH);

void setup() {
  Serial.begin(9600);
}

void loop() {
  telegraph.sendMessage("Hello, world!");
  delay(5000);
}
