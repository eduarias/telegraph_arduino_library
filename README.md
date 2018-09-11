# Telegraph Arduino Library

A library to send morse messages on Arduino using led or speakers.

Simple example of library initialization and how to send a message using a led.
```c
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
```
To use a speaker use the class Speaker instead of Led.
