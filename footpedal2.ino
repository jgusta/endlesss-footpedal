#include <ResponsiveAnalogRead.h>
#include "enums.h"
#include "functions.h"
#include "vars.h"
#include "midiReceive.h"

void setup() {
  Serial.begin(115200);
  midiSetup();
  for (uint8_t i = 0; i < 4; i++) pinMode(Lds[i], OUTPUT);
  for (int i = 0; i < 4; i++) {
    buttons[i].attach(Bts[i], INPUT_PULLUP);
    buttons[i].interval(40);
    buttons[i].setPressedState(LOW);
  }
  buttonT.attach(BUTTON_T, INPUT_PULLUP);
  buttonT.interval(40);
  buttonT.setPressedState(LOW);
  pinMode(SWITCH_1_UP, INPUT_PULLUP);
  pinMode(SWITCH_1_DOWN, INPUT_PULLUP);
  pinMode(SWITCH_2_UP, INPUT_PULLUP);
  pinMode(SWITCH_2_DOWN, INPUT_PULLUP);
  pinMode(EXPRESSION_1_DIGITAL, INPUT_PULLUP);
  pinMode(EXPRESSION_2_DIGITAL, INPUT_PULLUP);
  // A
  pinMode(EncCk, INPUT);
  // B
  pinMode(EncDt, INPUT);

  delay(200);
  logToSerial("booting", Sgfs::LogLevel::INFO);
  bootSequence();
  logToSerial("ready", Sgfs::LogLevel::INFO);
}

void loop() {
  updateButtons();
  checkButtons();
  checkExps();
  t.handle();
  usbMIDI.read();
}
