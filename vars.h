#ifndef VARS_H
#define VARS_H

#include <AsyncTimer.h>
#include <Bounce2.h>
#include <ResponsiveAnalogRead.h>

#define LOG_LEVEL 3

#define DELAY 100

#define LED_1 2
#define LED_2 3
#define LED_3 1
#define LED_4 0

#define BUTTON_1 7
#define BUTTON_2 6
#define BUTTON_3 5
#define BUTTON_4 4

#define BUTTON_T 8

#define SWITCH_1_UP 11
#define SWITCH_1_DOWN 12
#define SWITCH_2_UP 10
#define SWITCH_2_DOWN 9

// AKA OUT A
#define EncCk 32
// AKA OUT B
#define EncDt 31
#define EncSw 30

// ANALOG INPUT 1 (FURTHEST RIGHT)
#define EXPRESSION_1_ANALOG A1
#define EXPRESSION_1_DIGITAL 25

// ANALOG INPUT 2 (MIDDLE)
#define EXPRESSION_2_ANALOG A0
#define EXPRESSION_2_DIGITAL 24

extern uint8_t Lds[4];
extern uint8_t Bts[4];
extern uint8_t Sws[4];
extern uint8_t ExAs[2];
extern uint8_t ExDs[2];
extern char aNames[2][16];

extern bool cons[2];
extern uint16_t lastsRaw[2];
extern uint16_t lasts[2];
extern uint16_t reads[2];
extern uint16_t maxs[2];
extern uint16_t mins[2];

extern Bounce2::Button button1;
extern Bounce2::Button button2;
extern Bounce2::Button button3;
extern Bounce2::Button button4;
extern Bounce2::Button buttonT;
extern Bounce2::Button switch1Up;
extern Bounce2::Button switch1Down;
extern Bounce2::Button switch2Up;
extern Bounce2::Button switch2Down;

extern Bounce2::Button buttons[5];
extern Bounce2::Button switches[4];
extern ResponsiveAnalogRead analog1;
extern ResponsiveAnalogRead analog2;
extern ResponsiveAnalogRead analogs[2];

extern unsigned short intervals[5];



extern AsyncTimer t;
#endif  // VARS_H
