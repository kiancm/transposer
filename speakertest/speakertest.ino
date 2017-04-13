/*  GE 1502 - 9:15 am
*  This code is for the second RedBoard, which controls both buttons, the
*  piezo buzzer, the LCD display, and the potentiometer */
/*-----------------------------------------------------------------------------*/
#include <MozziGuts.h>
#include <Oscil.h>
#include <tables/sin4096_int8.h>
Oscil <SIN4096_NUM_CELLS, AUDIO_RATE> aSin0(SIN4096_DATA);
Oscil <SIN4096_NUM_CELLS, AUDIO_RATE> aSin1(SIN4096_DATA);
Oscil <SIN4096_NUM_CELLS, AUDIO_RATE> aSin2(SIN4096_DATA);
void setup() {
    startMozzi(CONTROL_RATE);
    aSin0.setFreq(523);
    aSin1.setFreq(659);
    aSin2.setFreq(784);
}

void updateControl() {

}

int updateAudio() {
    return (int) (.5 * aSin0.next() + .25 * aSin1.next() + .25 * aSin2.next());
}

void loop() {
    audioHook();
}
