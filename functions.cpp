#include <stdint.h>

#include "functions.h"
#include "vars.h"

void LdsOff(void) {
  for (uint8_t i = 0; i < 4; i++) {
    digitalWrite(Lds[i], LOW);
  }
}

void LdsOn(void) {
  for (uint8_t i = 0; i < 4; i++) {
    digitalWrite(Lds[i], HIGH);
  }
}

void LdOn(uint8_t i) {
  digitalWrite(Lds[i], HIGH);
}

void LdOff(uint8_t i) {
  digitalWrite(Lds[i], LOW);
}

uint8_t Sw1() {
  int up = digitalRead(S1u);
  int down =  digitalRead(S1d);
  if (up == LOW) {
    sp(1,2);
    return 2;
  }
  if (down == LOW) {
    sp(1,1);
    return 1;
  }
  sp(1,0);
  return 0;
}

void sp(int i, int stat) {
    Serial.print("Switch ");
    Serial.print(i);
    Serial.print(": ");
    Serial.println(stat);
}


uint8_t Sw2() {
  int up = digitalRead(S2u);
  int down =  digitalRead(S2d);
  if (up == LOW) {
    sp(2,2);
    return 2;
  }
  if (down == LOW) {
    sp(2,1);
    return 1;
  }
  sp(2,0);
  return 0;
}

uint16_t remap(uint16_t iMin, uint16_t iMax, uint16_t oMin, uint16_t oMax, uint16_t v) {
    return (uint16_t)(((v - iMin) * (oMax - oMin)) / (iMax - iMin) + oMin);
}

void updateButtons() {
  for (uint8_t i=0; i<5;i++) {
    buttons[i].update();
  }
  for (uint8_t i=0;i<4;i++) {
    switches[i].update();  
  }
}

void blinkit(int i) {
  if (intervals[i] == 0) {
    LdOn(i);
    intervals[i] = t.setTimeout([i](){
      LdOff(i);
      intervals[i] = 0;
    }, 2000);
  }
}

void bounceButtonOn(int i, int cc) {
  if (intervals[i] == 0) {
    LdOn(i);
    usbMIDI.sendControlChange(cc, 127, 1);
    intervals[i] = t.setTimeout([i](){
      LdOff(i);
      intervals[i] = 0;
    }, 2000);
  }
}

void blinkall() {
  if (intervals[4] == 0) {
    LdsOn();
    intervals[4] = t.setTimeout([](){
      LdsOff();
      intervals[4] = 0;
    }, 2000);
  }
}



void checkButtons() {
  for (int i=0; i<4; i++) {
    if(buttons[i].pressed()) {
      Serial.println("button " + String(i) + " pressed");
      uint16_t trans = Sw1() * 4;
      bounceButtonOn(i,20+trans+i);
    }
  }
  if (buttonT.pressed()) {
//    Serial.println("blink");
    delay(40);
    blinkall();
  }
}

void checkExps() {
  for (int i = 0; i < 2; i++) {
    analogs[i].update();
    uint16_t myread = digitalRead(ExDs[i]);
    if (myread != cons[i]) {
      cons[i] = digitalRead(ExDs[i]);
      if (myread) {
        mins[i] = 400;
        maxs[i] = 500;
        Serial.print(aNames[i]);
        Serial.println(" connected");
      }
      else {
        Serial.print(aNames[i]);
        Serial.println(" disconnected");
      }
      delay(1000);
    }
    if (cons[i]) {
      reads[i] = analogs[i].getValue();
      if (reads[i] != lastsRaw[i]) {
        if (maxs[i] < reads[i]) {
          maxs[i] = reads[i];
        }
        if (mins[i] > reads[i]) {
          mins[i] = reads[i];
        }
        lastsRaw[i] = reads[i];
        uint16_t mapped = remap(mins[i], maxs[i], 0, 127, reads[i]);
        if (lasts[i] != mapped) {
          uint16_t trans = Sw2() * 2;
          usbMIDI.sendControlChange(4+trans+i, mapped, 1);
          lasts[i] = mapped;
        }
      }
    }
  }
}

void bootSequence() {
  LdsOn();
  delay(DELAY);
  LdsOff();
  delay(DELAY);
  LdOn(0);
  delay(DELAY);
  LdOn(1);
  delay(DELAY);
  LdOn(2);
  delay(DELAY);
  LdOn(3);
  delay(DELAY);
  LdsOff();
  delay(DELAY);
  LdsOn();
  delay(DELAY);
  LdsOff();
  delay(DELAY);
  LdsOn();
  delay(DELAY);
  LdsOff();
  delay(DELAY);
  LdsOn();
  delay(DELAY);
  LdsOff();
  delay(DELAY);
  LdOn(0);
  delay(DELAY);
  LdOn(1);
  delay(DELAY);
  LdOn(2);
  delay(DELAY);
  LdOn(3);
  delay(DELAY);
  LdsOff();
  delay(DELAY);
}