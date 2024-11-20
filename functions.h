#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <Arduino.h>
#include <stdint.h>
#include <functional>
#include "enums.h"
void sp(int i, int stat);
void bootSequence(void);
uint8_t Sw1(void);
uint8_t Sw2(void);
void LdsOff(void);
void LdsOn(void);
void LdOn(uint8_t);
void LdOff(uint8_t);
uint16_t remap(uint16_t iMin, uint16_t iMax, uint16_t oMin, uint16_t oMax, uint16_t v);
void checkButtons(void);
void blinkall(void);
void updateButtons(void);
void blinkit(int i);
void bounceFootButtonOn(int i, int cc);
void checkExps(void);
void ledsLater(int delay, Sgfs::LedState state, std::function<void()> callback); 
void flashLeds(std::function<void()> callback);
void stepLeds(std::function<void()> callback);
void logToSerial(String msg, Sgfs::LogLevel level);
void logPress(String btn);
void logMidiCC(int cc, int value);
#endif // FUNCTIONS_H
