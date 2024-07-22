# Endlesss Footpedal

Code for a custom-made footpedal powered by Teensy 4.1

Runs in Arduino IDE 2

Requires libraries:
- ResponsiveAnalogRead
- Bounce2
- AsyncTImer

```
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
```

Foot Switches have a debounce period, so long as the led is on, they cannot be retriggered.
Switches change the footswitches to a different bank of midi CCs.
Analog inputs are for expression pedals. 
They are self-calibrating, just move pedal up and down once and it will adjust to that range.

