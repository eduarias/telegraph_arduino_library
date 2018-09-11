#include "telegraph.h"

const byte OUTPUT_PIN_LED = 9;
const byte OUTPUT_PIN_SPEAKER = 10;
const unsigned int DIT_LENGTH = 200;
const unsigned int MAX_MESSAGE_LEN = 128;
const unsigned int BAUD_RATE = 9600;
const int LINE_FEED = 13;

char messageText[MAX_MESSAGE_LEN];
int index = 0;

Led led(OUTPUT_PIN_LED);
Speaker speaker(OUTPUT_PIN_SPEAKER);
OutputDevice* ledDevice = &led;
OutputDevice* speakerDevice = &speaker;
Telegraph telegraph1(ledDevice, DIT_LENGTH);
Telegraph telegraph2(speakerDevice, DIT_LENGTH);

void setup() {
  Serial.begin(BAUD_RATE);
}

void loop() {
  if (Serial.available() > 0){
    int currentChar = Serial.read();
    if (currentChar == LINE_FEED || index == MAX_MESSAGE_LEN -1) {
      messageText[index] = 0;
      index = 0;
      telegraph1.sendMessage(messageText);
      telegraph2.sendMessage(messageText);
    } else {
      messageText[index++] = currentChar;
    }
  }
}
