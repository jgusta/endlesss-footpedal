//#ifndef USB_MIDI_H
//#include <usbMIDI.h>
//#endif

#ifndef MIDIRECEIVE_H
#define MIDIRECEIVE_H


void midiSetup();
void myNoteOn(byte channel, byte note, byte velocity);
void myNoteOff(byte channel, byte note, byte velocity);
void myAfterTouchPoly(byte channel, byte note, byte velocity);
void myControlChange(byte channel, byte control, byte value);
void myProgramChange(byte channel, byte program);
void myAfterTouchChannel(byte channel, byte pressure);
void myPitchChange(byte channel, int pitch);
void mySystemExclusiveChunk(const byte *data, uint16_t length, bool last);
void mySystemExclusive(byte *data, unsigned int length);
void myTimeCodeQuarterFrame(byte data);
void mySongPosition(uint16_t beats);
void mySongSelect(byte songNumber);
void myTuneRequest();
void myClock();
void myStart();
void myContinue();
void myStop();
void myActiveSensing();
void mySystemReset();
void myRealTimeSystem(uint8_t realtimebyte);
void printBytes(const byte *data, unsigned int size);

#endif
