#ifndef VARS_H
#define VARS_H

#include <Bounce2.h> 
#include <ResponsiveAnalogRead.h>
#include <AsyncTimer.h>
///////////////////////////////////////
// buttons defined from left to right.
// pins are all mixed up.
// These are mine.
// (o)   = pushbutton
// [!]   = three-way switch
// (*)   = led
// (0)   = momentary guitar pedal switch
// (U)   = Switchable TRS analog input jack
///////////////////////////////////////
//               (U)       (U)
// pin:         A0/24     A1/25
//
//               (o)   [!]   [!]
// pin:           8    9/10  11/12
//
//         (*)   (*)   (*)   (*)
// pin:     2     3     1     0
//
//         (0)   (0)   (0)   (0)
// pin:     7     6     5     4
///////////////////////////////////////


#define DELAY 100

#define Ld1 2
#define Ld2 3
#define Ld3 1
#define Ld4 0

#define Bt1 7
#define Bt2 6
#define Bt3 5
#define Bt4 4

#define BtT 8

#define S1u 11
#define S1d 12
#define S2u 10
#define S2d 9 


// ANALOG INPUT 1 (FURTHEST RIGHT)
//15
#define Ex1A A1
#define Ex1D 25


// ANALOG INPUT 2 (MIDDLE)
// pin 14
#define Ex2A A0
#define Ex2D 24


extern uint8_t Lds[4];
extern uint8_t Bts[4];
extern uint8_t Btx[5];
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
#endif // VARS_H