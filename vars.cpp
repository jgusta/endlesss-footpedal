#include <stdint.h>
#include <Bounce2.h>
#include <ResponsiveAnalogRead.h> 
#include <AsyncTimer.h>
#include "vars.h"

uint8_t Lds[] = {Ld1, Ld2, Ld3, Ld4};
uint8_t Bts[] = {Bt1, Bt2, Bt3, Bt4};
uint8_t Btx[] = {Bt1, Bt2, Bt3, Bt4, BtT};
uint8_t Sws[] = {S1u,S1d,S2u,S2d};
uint8_t ExAs[] = {Ex1A, Ex2A};
uint8_t ExDs[] = {Ex1D, Ex2D};
char aNames[2][16] = {"Analog Port 1", "Analog Port 2"};

Bounce2::Button button1 = Bounce2::Button();
Bounce2::Button button2 = Bounce2::Button();
Bounce2::Button button3 = Bounce2::Button();
Bounce2::Button button4 = Bounce2::Button();
Bounce2::Button buttonT = Bounce2::Button();
Bounce2::Button switch1Up = Bounce2::Button();
Bounce2::Button switch1Down = Bounce2::Button();
Bounce2::Button switch2Up = Bounce2::Button();
Bounce2::Button switch2Down = Bounce2::Button();

Bounce2::Button buttons[] = {button1, button2, button3, button4, buttonT};
Bounce2::Button switches[] = {switch1Up,switch1Down,switch2Up,switch2Down};
ResponsiveAnalogRead analog1(Ex1A, true);
ResponsiveAnalogRead analog2(Ex2A, true);
ResponsiveAnalogRead analogs[] = {analog1, analog2};

bool cons[] = {false, false};
uint16_t lastsRaw[] = {0, 0};
uint16_t lasts[] = {0, 0};
uint16_t reads[] = {0, 0};
uint16_t maxs[] = {500, 500};
uint16_t mins[] = {400, 400};

unsigned short intervals[5] = {0,0,0,0,0};

AsyncTimer t;