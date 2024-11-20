#include "functions.h"
#include "enums.h"
#include "vars.h"
#include <AsyncTimer.h>
#include <ResponsiveAnalogRead.h>
#include <Bounce2.h>

// turn all leds off
void LdsOff(void) {
  for (uint8_t i = 0; i < 4; i++) {
    digitalWrite(Lds[i], LOW);
  }
}

// turn all leds on
void LdsOn(void) {
  for (uint8_t i = 0; i < 4; i++) {
    digitalWrite(Lds[i], HIGH);
  }
}

// turn single led on
void LdOn(uint8_t i) { digitalWrite(Lds[i], HIGH); }

// turn single led off
void LdOff(uint8_t i) { digitalWrite(Lds[i], LOW); }

// read switch 1
uint8_t Sw1() {
  int up = digitalRead(SWITCH_1_UP);
  int down = digitalRead(SWITCH_1_DOWN);
  if (up == LOW) {
    sp(1, 2);
    return 2;
  }
  if (down == LOW) {
    sp(1, 1);
    return 1;
  }
  sp(1, 0);
  return 0;
}
void logToSerial(String msg, Sgfs::LogLevel level) {
  if (level <= LOG_LEVEL) {
     Serial.println(msg);
  }
}
void linfo(String msg) {
  logToSerial(msg, Sgfs::LogLevel::INFO);
}
void lmore(String msg) {
  logToSerial(msg, Sgfs::LogLevel::MORE);
}
void ldebug(String msg) {
  logToSerial(msg, Sgfs::LogLevel::DEBUG);
}
void logPress(String btn) {
  logToSerial("button " + btn + " pressed", Sgfs::LogLevel::INFO);
}
void logMidiCC(int cc, int value) { 
  logToSerial("MIDI: Sent cc " + String(cc) + " value " + String(value), Sgfs::LogLevel::DEBUG); 
}


// print switch status
void sp(int i, int stat) {
  logToSerial("Switch " + String(i) + ": " + String(stat), Sgfs::LogLevel::INFO);
}

// read switch 2
uint8_t Sw2() {
  int up = digitalRead(SWITCH_2_UP);
  int down = digitalRead(SWITCH_2_DOWN);
  if (up == LOW) {
    sp(2, 2);
    return 2;
  }
  if (down == LOW) {
    sp(2, 1);
    return 1;
  }
  sp(2, 0);
  return 0;
}

/**
 * @brief Remaps a value from one range to another.
 *
 * take `v` within the range `[iMin, iMax]` and remaps it proportionally to the
 * range `[oMin, oMax]`.
 *
 * @param iMin Min value of input range.
 * @param iMax Max value of input range.
 * @param oMin Min value of output range.
 * @param oMax Max value of output range.
 * @param v The value to be remapped
 * @return The remapped value within the output range.
 */
uint16_t remap(uint16_t iMin, uint16_t iMax, uint16_t oMin, uint16_t oMax,
               uint16_t v) {
  return (uint16_t)(((v - iMin) * (oMax - oMin)) / (iMax - iMin) + oMin);
}

/**
 * @brief Update state of buttons and switches.
 */
void updateButtons() {
  for (uint8_t i = 0; i < 4; i++) {
    switches[i].update();
  }
  for (uint8_t i = 0; i < 4; i++) {
    buttons[i].update();
  }
  buttonT.update();
}

/**
 * @brief Blink a single led.
 *
 * @param i The index of the led to blink.
 */
void blinkit(int i) {
  if (intervals[i] == 0) {
    LdOn(i);
    intervals[i] = t.setTimeout(
        [i]() {
          LdOff(i);
          intervals[i] = 0;
        },
        2000);
  }
}

/**
 * @brief handle button press
 *
 * If the button is not in timeout, send CC message, turn light on and start
 * timeout. Makes sure that when the footpedal button is pressed, it cannot be
 * pressed again for 2 seconds. The LED will remain on during this period.
 *
 * @param i The index of the button to bounce.
 * @param cc The control change number to send.
 */
void bounceFootButtonOn(int i, int cc) {
  if (intervals[i] == 0) {
    LdOn(i);
    usbMIDI.sendControlChange(cc, 127, 1);
    logMidiCC(cc, 127);
    // usbMIDI.sendControlChange(cc, 0, 1);
    // logMidiCC(cc, 0);

    intervals[i] = t.setTimeout(
        [i, cc]() {
          LdOff(i);
          intervals[i] = 0;
        },
        2000);
  }
}

/**
 * @brief Blink all leds.
 */
void blinkall() {
  if (intervals[4] == 0) {
    LdsOn();
    intervals[4] = t.setTimeout(
        []() {
          LdsOff();
          intervals[4] = 0;
        },
        2000);
  }
}

void checkButtons() {
  for (int i = 0; i < 4; i++) {
    if (buttons[i].pressed()) {
      logPress(String(i));
      uint16_t trans = Sw1() * 4;
      bounceFootButtonOn(i, 20 + trans + i);
    }
  }
  if (buttonT.pressed()) {
    logPress("T");
    usbMIDI.sendControlChange(19, 127, 1);
    logMidiCC(19,127);
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
        linfo(String(aNames[i]) + " connected");
      } else {
        linfo(String(aNames[i]) + " connected");
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
          uint16_t trans =(4 + i) + (Sw2() * 2);
          usbMIDI.sendControlChange(trans, mapped, 1);
          logMidiCC(trans, mapped);
          lasts[i] = mapped;
        }
      }
    }
  }
}

void stepLeds(std::function<void()> callback) {
  LdsOff();
  for (int i = 0; i < 4; i++) {
    t.setTimeout([i]() { LdOn(i); }, (i + 1) * 100);
  }
  t.setTimeout(
      [callback]() {
        LdsOff();
        callback();
      },
      500);
}

void ledsLater(int delay, Sgfs::LedState state, std::function<void()> callback) {
  lmore("ledsLater: Starting timeout");
  t.setTimeout(
      [delay, state, callback]() {
        if (state == Sgfs::ON) {
          LdsOn();
        } else {
          LdsOff();
        }
        lmore("ledsLater: Calling callback");
        callback();
      },
      delay);
}

void flashLeds(std::function<void()> cb) {
  LdsOn();
  ledsLater(100, Sgfs::OFF, [cb]() {
    ledsLater(100, Sgfs::ON, [cb]() {
      ledsLater(100, Sgfs::OFF, [cb]() {
        ledsLater(100, Sgfs::ON, [cb]() { ledsLater(100, Sgfs::OFF, [cb]() { cb(); }); });
      });
    });
  });
}

void bootSequence() {
  flashLeds([]() {
    stepLeds([]() {
      flashLeds([]() {
        stepLeds([]() { flashLeds([]() { flashLeds([]() {}); }); });
      });
    });
  });
}
