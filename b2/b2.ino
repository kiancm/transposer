/*  GE 1502 - 9:15 am
*  This code is for the second RedBoard, which controls both buttons, the
*  piezo buzzer, the LCD display, and the potentiometer */
/*-----------------------------------------------------------------------------*/
#include <LiquidCrystal.h>
const int potPin = A1;
const int ampPin = 9;
const int buttonPin = 7;
const unsigned int sampleRate = 44100;

LiquidCrystal lcd1(12, 11, 5, 4, 3, 2);
LiquidCrystal lcd2(12, 10, 5, 4, 3, 2);
void setup() {
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

void loop() {
    analogWrite(ampPin, 0);
    int shift = map(analogRead(potPin), 0, 1023, 0, 12);
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
        float freqs_f[3];
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
                analogWrite(ampPin, 0);
                delay(2000);
                lcd2.clear();
                lcd2.setCursor(0,0);
                lcd2.print("Transpose: ");
                break;
            }
            for (unsigned int sample = 0; sample < sampleRate; sample++) {
                float t = sample / (float) sampleRate;
                float music = sin(2 * PI * freqs_f[0] * t) + .25 * sin(2 * PI * freqs_f[1] * t) + .25 * sin(2 * PI * freqs_f[2] * t) + 1.5;
                analogWrite(ampPin, music * 127/3.0);
            }
        }
    }

}

