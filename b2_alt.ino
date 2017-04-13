/*  GE 1502 - 9:15 am
*  This code is for the second RedBoard, which controls both buttons, the
*  piezo buzzer, the LCD display, and the potentiometer */
/*-----------------------------------------------------------------------------*/
#include <LiquidCrystal.h>
// #include <MozziGuts.h>
// #include <Oscil.h>
// #include <tables/sin2048_int8.h>
const int potPin = A1;
const int ampPin = 9;
const int buttonPin = 7;
const unsigned int sampleRate = 44100;
#include <MozziGuts.h>
#include <Oscil.h>
#include <tables/sin4096_int8.h>
Oscil <SIN4096_NUM_CELLS, AUDIO_RATE> aSin0(SIN4096_DATA);
Oscil <SIN4096_NUM_CELLS, AUDIO_RATE> aSin1(SIN4096_DATA);
Oscil <SIN4096_NUM_CELLS, AUDIO_RATE> aSin2(SIN4096_DATA);
LiquidCrystal lcd1(12, 11, 5, 4, 3, 2);
LiquidCrystal lcd2(12, 10, 5, 4, 3, 2);
float freqs_f[3];
void setup() {
    startMozzi(CONTROL_RATE);
    pauseMozzi();
    int contrast = 85;
    analogWrite(6, contrast);
    lcd1.begin(16, 2);
    lcd2.begin(16, 2);
    lcd1.clear();
    lcd2.clear();
    lcd1.setCursor(0,0);
    lcd2.setCursor(0,0);
    lcd2.print("Transpose: ");
    pinMode(potPin, INPUT);
    pinMode(ampPin, OUTPUT);
    pinMode(buttonPin, INPUT);
    Serial.begin(57600);
}

void updateControl() {
    aSin0.setFreq(freqs_f[0]);
    // aSin1.setFreq(freqs_f[1]);
    // aSin2.setFreq(freqs_f[2]);
}

void loop() {
    analogWrite(ampPin, 0);
    int shift = map(analogRead(potPin), 0, 1023, 0, 12);
    analogWrite(6, 85);
    lcd2.setCursor(11,0);
    lcd2.print("  ");
    lcd2.setCursor(11,0);
    lcd2.print(shift);
    delay(100);
    if (digitalRead(buttonPin) == LOW) {
        lcd2.setCursor(0, 1);
        lcd2.print("3..");
        delay(1000);
        lcd2.print("2..");
        delay(1000);
        lcd2.print("1..");
        delay(1000);
        lcd2.setCursor(0, 1);
        lcd2.print("RECORDING...");
        char freqs[23];
        while (true) {
            if (digitalRead(buttonPin) == LOW) {
                break;
            }
            if (Serial.available()) {
                Serial.readBytesUntil('\n', freqs, 23);
                for (int i = 0; i < 23; i++) {
                    if (i == 16) {
                        lcd1.setCursor(0,1);
                    }
                    lcd1.print(freqs[i]);
                }
                lcd1.setCursor(0,0);
            }
        }
        lcd2.setCursor(0, 1);
        lcd2.print("                ");
        lcd2.setCursor(0, 1);
        lcd2.print("3..");
        delay(1000);
        lcd2.print("2..");
        delay(1000);
        lcd2.print("1..");
        delay(1000);
        lcd2.setCursor(0, 1);
        lcd2.print("PLAYING...");
        
        freqs_f[0] = String(freqs).substring(0,6).toFloat();
        freqs_f[1] = String(freqs).substring(7,13).toFloat();
        freqs_f[2] = String(freqs).substring(14,20).toFloat();
        for (int i = 0; i < 3; i++) {
            freqs_f[i] *= pow(2, shift / 12.0);
        }
        while (true) {
            if (digitalRead(buttonPin) == LOW) {
                lcd2.clear();
                lcd2.setCursor(0, 0);
                lcd2.print("RESETING...");
                // analogWrite(ampPin, 0);
                delay(2000);
                lcd2.clear();
                lcd2.setCursor(0,0);
                lcd2.print("Transpose: ");
                pauseMozzi();
                break;
            }
            unPauseMozzi();
            audioHook();
            // for (unsigned int sample = 0; sample < sampleRate; sample++) {
            //     float t = sample / (float) sampleRate;
            //     float music = sin(2 * PI * freqs_f[0] * t) + .25 * sin(2 * PI * freqs_f[1] * t) + .25 * sin(2 * PI * freqs_f[2] * t) + 1.5;
            //     analogWrite(ampPin, music * 127/3.0);
            // }
        }
    }

}
int updateAudio() {
    return (int) (.1 * aSin0.next()); //+ .25 * aSin1.next() + .25 * aSin2.next());
}

