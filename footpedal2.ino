#include <ResponsiveAnalogRead.h>
#include "functions.h"
#include "vars.h"

void setup() {
  Serial.begin(9600);
  for (uint8_t i = 0; i < 4; i++)
    pinMode(Lds[i], OUTPUT);
  for (int i = 0; i < 4; i++) {
    buttons[i].attach(Bts[i], INPUT_PULLUP);
    buttons[i].interval(40);
    buttons[i].setPressedState(LOW);
  }
  buttonT.attach(BtT, INPUT_PULLUP);
  buttonT.interval(40);
  buttonT.setPressedState(HIGH);
  pinMode(S1u, INPUT_PULLUP);
  pinMode(S1d, INPUT_PULLUP);
  pinMode(S2u, INPUT_PULLUP);
  pinMode(S2d, INPUT_PULLUP);
  pinMode(Ex1D, INPUT_PULLUP);
  pinMode(Ex2D, INPUT_PULLUP);
  Serial.println("booting");
  bootSequence();
}



void loop() {
  updateButtons();
  checkButtons();
  checkExps();
  t.handle();
  while (usbMIDI.read()) {
    // discard incoming messages
  }
  delay(5);
}
