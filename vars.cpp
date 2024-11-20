#include "vars.h"

#include <AsyncTimer.h>
#include <Bounce2.h>
#include <ResponsiveAnalogRead.h>
#include <stdint.h>

uint8_t Lds[] = {LED_1, LED_2, LED_3, LED_4};
uint8_t Bts[] = {BUTTON_1, BUTTON_2, BUTTON_3, BUTTON_4};
uint8_t Sws[] = {SWITCH_1_UP, SWITCH_1_DOWN, SWITCH_2_UP, SWITCH_2_DOWN};
uint8_t ExAs[] = {EXPRESSION_1_ANALOG, EXPRESSION_2_ANALOG};
uint8_t ExDs[] = {EXPRESSION_1_DIGITAL, EXPRESSION_2_DIGITAL};
char aNames[2][16] = {"Analog Port 1", "Analog Port 2"};

Bounce2::Button button1 = Bounce2::Button();
Bounce2::Button button2 = Bounce2::Button();
Bounce2::Button button3 = Bounce2::Button();
Bounce2::Button button4 = Bounce2::Button();
Bounce2::Button buttonE = Bounce2::Button();
Bounce2::Button buttonT = Bounce2::Button();
Bounce2::Button switch1Up = Bounce2::Button();
Bounce2::Button switch1Down = Bounce2::Button();
Bounce2::Button switch2Up = Bounce2::Button();
Bounce2::Button switch2Down = Bounce2::Button();

Bounce2::Button buttons[] = {button1, button2, button3, button4, buttonE};
Bounce2::Button switches[] = {switch1Up, switch1Down, switch2Up, switch2Down};
ResponsiveAnalogRead analog1(EXPRESSION_1_ANALOG, true);
ResponsiveAnalogRead analog2(EXPRESSION_2_ANALOG, true);
ResponsiveAnalogRead analogs[] = {analog1, analog2};

bool cons[] = {false, false};
uint16_t lastsRaw[] = {0, 0};
uint16_t lasts[] = {0, 0};
uint16_t reads[] = {0, 0};
uint16_t maxs[] = {500, 500};
uint16_t mins[] = {400, 400};

unsigned short intervals[5] = {0, 0, 0, 0, 0};

AsyncTimer t;
