/*  GE 1502 - 9:15 am
*  This code is for the second RedBoard, which controls both buttons, the
*  piezo buzzer, the LCD display, and the potentiometer */
/*-----------------------------------------------------------------------------*/
#include <LiquidCrystal.h>
const int potPin = A1;
const int ampPin = 9;
const int buttonPin = 7;
const unsigned int sampleRate = 44100;
float freqs_f[3];

void setup() {
    int contrast = 85;
    analogWrite(6, contrast);
    pinMode(potPin, INPUT);
    pinMode(ampPin, OUTPUT);
    pinMode(buttonPin, INPUT);
    Serial.begin(57600);
    freqs_f[0] = 130.81;
    freqs_f[1] = 164.81;
    freqs_f[2] = 196;
}

void loop() {
    int shift = map(analogRead(potPin), 0, 1023, 0, 12);
    for (unsigned int sample = 0; sample < sampleRate; sample++) {
        float t = sample / (float) sampleRate;
        float music = 0.5 * sin(2 * PI * freqs_f[0] * t) + 0.5 * sin(2 * PI * freqs_f[1] * t) + 0.5 * sin(2 * PI * freqs_f[2] * t) + 1.5;
        analogWrite(ampPin, music * 255/3.0);
    }
}
