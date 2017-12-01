#include "LM48100Q.h"

LM48100Q amp;

void setup() {
  Serial.begin(57600);
  Serial.println("Hello");
  Serial.println();

  amp.begin();
  delay(1000);

  amp.enable();
  delay(1000);

  amp.setInput(IN_1);
  amp.setVolume(IN_1, 32);
  delay(1000);

  amp.setInput(IN_1);
  amp.setVolume(IN_2, 16);
  delay(1000);

  amp.setInput(MUTE);
  delay(1000);

  amp.setInput(MUX);
  amp.setVolume(MUX, 10);
  delay(1000);

  amp.disable();
}

void loop() {}
