#include <ctype.h>
#include <Arduino.h>
#include "telegraph.h"

char* CHARACTERS[] = {
  "-.-.--", ".-..-.", "", "...-..-",    // ! " # $
  "", ".-...", ".----.", "-.--.",       // % & ' (
  "-.--.-", "", ".-.-.", "--..--",      // ) * + ,
  "-....-", ".-.-.-", "-..-.",          // - . /  
  "-----", ".----", "..---", "...--",   // 0-3
  "....-", ".....", "-....", "--...",   // 4-7
  "---..", "----.",                     // 8-9
  "---...", "-.-.-.", "", "-...-",      // : ; < =
  "", "..--..", ".--.-.",               // > ? @
  ".-", "-...", "-.-.", "-..", ".",     // A-E
  "..-.", "--.", "....", "..", ".---",  // F-J
  "-.-", ".-..", "--", "-.", "---",     // K-O
  ".--.", "--.-", ".-.", "...", "-",    // P-T
  "..-", "...-", ".--", "-..-", "-.--", // U-Y
  "--..",                               // Z
  "", "", "", "", "..--.-"              // [ \ ] ^ _
};


OutputDevice::OutputDevice(const byte outputPin) {
  pinMode(outputPin, OUTPUT);
  _outputPin = outputPin;
}

Led::Led(const byte outputPin) : OutputDevice(outputPin) { }

void Led::outputSymbol(const int length) {
  digitalWrite(_outputPin, HIGH);
  delay(length);
  digitalWrite(_outputPin, LOW);
}

Speaker::Speaker(const byte outputPin) : OutputDevice(outputPin) { }

void Speaker::outputSymbol(const int length) {
  const int frequency = 131;
  tone(_outputPin, frequency, length);
}

Telegraph::Telegraph(OutputDevice *outputDevice, const int ditLength) {
  _ditLength = ditLength;
  _dahLength = ditLength * 3;
  _outputDevice = outputDevice;
}

void Telegraph::outputCode(const char* code) {
  for (int i=0; i < strlen(code); i++){
    if (code[i] == '.')
      dit();
    else
      dah();
    delay(_ditLength); // Make a silence betwen symbols
  }
}

void Telegraph::dit() {
  Serial.print(".");
  outputSymbol(_ditLength);
}

void Telegraph::dah() {
  Serial.print("-");
  outputSymbol(_dahLength);
}

void Telegraph::outputSymbol(const int length) {
  _outputDevice->outputSymbol(length);
}

void Telegraph::sendMessage(const char* message) {
  unsigned int charIndex;

  for (int i=0; i < strlen(message); i++){
    const char currentChar = toupper(message[i]);
    if (isalpha(currentChar) || isdigit(currentChar) || ispunct(currentChar)) {
      charIndex = currentChar - 33;
      outputCode(CHARACTERS[charIndex]);
    } else if (currentChar == ' ') {
      Serial.print(" / ");
      delay(_ditLength * 4);  // make 4 silences + char silence (7)
    }
    delay(_ditLength * 2); // make 2 silences + letter silence (3)
    Serial.print(" ");
  }
  Serial.println();
}

