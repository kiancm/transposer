// 9:15 AM
/* This code is for the second RedBoard, which controls both buttons, the 
   piezo buzzer, the LCD display, and the potentiometer */
/****************************************************************************************/
#include <LiquidCrystal.h>  // For the LCD display
const int potPin = A1;    //to use as a selector
const int ampPin = 9;   // Set the pins for each input and output
const int buttonPin = 8;
const float sampleRate = 44100;
const int duration = 3;  
const float pi = acos(-1);  
      //<--- For the length of the note-input array. This can be set 
                            // to any number as long as the board's memory can handle it.
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);    // Initializing the LCD
typedef union {
  float f;
  byte b[4];
} byteFloat;

void setup() {
  int contrast = 85;
  analogWrite(6, contrast);   // Set the contrast of the LCD and
  lcd.begin(16, 2);           // set up the cursor 
  lcd.clear();
  lcd.setCursor(0,0);
  pinMode(potPin, INPUT);     // Specify the input and output pins
  pinMode(ampPin, OUTPUT);
  pinMode(buttonPin, INPUT);
  Serial.begin(57600);
}

void loop() {
//  lcd.clear();                                // clear the LCD after each run through
  //lcd.setCursor(7,0);                         // Now the screen will display the number of semitones the user will
//  lcd.print("1 2 3  4  5  6 7");              // choose to shift in the transposition
//  lcd.setCursor(0,1);
//  lcd.print(" 8 9 10 11 12");
  int shift = 0;
  delay(1000);
  //Serial.println(analogRead(potPin));
//  while (digitalRead(buttonPin) != LOW) {       // The user will use the potentiometer to select what level of transposition they would like to enact
//  	lcd.setCursor(7,0);
////  	lcd.print("0");
////  	lcd.setCursor(0,1);
////  	lcd.print(" 8 9 10 11 12  ");
//  	if (analogRead(potPin)<79)             // This string of if-else checks where the potentiometer is at a given point and
//  	{                                     // continuously loops while the user has not yet selected a transposition input
////  	  lcd.setCursor(0,1);                 // and once they do the shift value at that time is saved for later use
////  	  lcd.print("^");
////      lcd.clear();
//      lcd.print("01");
//  	  shift = 1;                                                // Shift up 1 semitone
//  	}
//  	else if(analogRead(potPin)>=79 && analogRead(potPin)< 158)   // Shift up 2 semitones
//  	{
////  	  lcd.setCursor(2,1);
////  	  lcd.print("^");
////      lcd.clear();
//      lcd.print("02");
//  	  shift = 2;
//  	}
//  	else if(analogRead(potPin)>=158 && analogRead(potPin)< 236)  // Shift up 3 semitones
//  	{
////  	  lcd.setCursor(4,1);
////  	  lcd.print("^");
////      lcd.clear();
//      lcd.print("03");
//  	  shift = 3;
//  	}
//  	else if(analogRead(potPin)>=236 && analogRead(potPin)< 315)  // Shift up 4 semitones
//  	{
////  	  lcd.setCursor(7,1);
////  	  lcd.print("^");
////      lcd.clear();
//      lcd.print("04");
//  	  shift = 4;
//  	}
//  	else if(analogRead(potPin)>=315 && analogRead(potPin)< 394)  // Shift up 5 semitones
//  	{
////  	  lcd.setCursor(10,1);
////  	  lcd.print("^");
////      lcd.clear();
//      lcd.print("05");
//  	  shift = 5;
//  	}
//  	else if(analogRead(potPin)>=394 && analogRead(potPin)< 473)  // Shift up 6 semitones
//  	{
////  	  lcd.setCursor(13,1);
////  	  lcd.print("^");
////      lcd.clear();
//      lcd.print("06");
//  	  shift = 6;
//  	}      
//  	else if(analogRead(potPin)>=473 && analogRead(potPin)< 551)  // Shift up 7 semitones
//  	{
////  	  lcd.setCursor(15,1);
////  	  lcd.print("^");
////  	  lcd.clear();
////      lcd.clear();
//      lcd.print("07"); 
//  	  shift = 7;
//  	}
//  	else if(analogRead(potPin)>=551 && analogRead(potPin)< 630)  // Shift up 8 semitones
//  	{
////  	  lcd.setCursor(1,0);
////  	  lcd.print("v");
////      lcd.clear();
//      lcd.print("08");
//  	  shift = 8;
//  	}
//  	else if(analogRead(potPin)>=630 && analogRead(potPin)< 709)  // Shift up 9 semitones
//  	{
////  	  lcd.setCursor(3,0);
////  	  lcd.print("v");
////      lcd.clear();
//      lcd.print("09");
//  	  shift = 9;
//  	}
//  	else if(analogRead(potPin)>=709 && analogRead(potPin)< 787)  // Shift up 10 semitones
//  	{
////  	  lcd.setCursor(5,0);
////  	  lcd.print("v");
////      lcd.clear();
//      lcd.print("10");
//  	  shift = 10;
//  	}
//  	else if(analogRead(potPin)>=787 && analogRead(potPin)< 866)  // Shift up 11 semitones
//  	{
////  	  lcd.setCursor(8,0);
////  	  lcd.print("v");
////      lcd.clear();
//      lcd.print("11");
//  	  shift = 11;
//  	}
//  	else                                                         // Shift up 12 semitones
//  	{
////  	  lcd.setCursor(11,0);
////  	  lcd.print("v");
////      lcd.clear();
//      lcd.print("12");
//  	  shift = 12;
//  	}
//   }
   
  delay(1000);          //delay time for the user to start recording
  char freqs[20];
  float freqs_f[3];
//  while (digitalRead(buttonPin) != LOW) { // Begin recording by saying if the button is not pressed (i.e. press the button to stop)
       //Serial.println("Test");
       if (Serial.available()) {
        Serial.readBytesUntil('\n', freqs, 20);
//        for (int i = 0; i < 20; i++) {
//          if (i == 16) {
//            lcd.setCursor(0,1); 
//          }
//            lcd.print(freqs[i]);
//        }
//        lcd.clear();
//        lcd.setCursor(0,0);
//        delay(500);
       }
       //Serial.println(freqs);
//  }
  freqs_f[0] = String(freqs).substring(0,6).toFloat();
  freqs_f[1] = String(freqs).substring(7,13).toFloat();
  freqs_f[2] = String(freqs).substring(14,20).toFloat();
  for (int i = 0; i < 3; i++) {
    freqs_f[i] *= pow(2, (float)shift / 12);    //Apply the transposition to each of the 3 harmonic tones
  }
  for (int sample = 0; sample < sampleRate * duration; sample++) {       
     float t = (float)sample / sampleRate;                          
     float music = 0.5 * sin(2 * pi * freqs_f[0] * t) + 0.5 * sin(2 * pi * freqs_f[1] * t) + 0.5 * sin(2 * pi * freqs_f[2] * t);
     analogWrite(ampPin, music);      //send to amp and speaker   
  }
  analogWrite(ampPin, 0);
  //the loop repeats for each note the user wants to transpose                                      
}

