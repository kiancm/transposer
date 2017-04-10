// 9:15 AM
/* This code is for the second RedBoard, which controls both buttons, the 
   piezo buzzer, the LCD display, and the potentiometer */
/****************************************************************************************/
#include <LiquidCrystal.h>  // For the LCD display
#include <SoftwareSerial.h>
const int potPin = A1;    //to use as a selector
const int ampPin = 9;   // Set the pins for each input and output
const int buttonPin = 8;
const float sampleRate = 44100;
const int duration = 3;  
const float pi = acos(-1);  
      //<--- For the length of the note-input array. This can be set 
                            // to any number as long as the board's memory can handle it.
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);    // Initializing the LCD
SoftwareSerial serial(7,10);
typedef union {
  float f;
  byte b[4];
} byteFloat;

void setup() {
int contrast = 85;
analogWrite(6, contrast);   // Set the contrast of the LCD and
lcd.begin(16, 2);           // set up the cursor 
lcd.clear();
pinMode(potPin, INPUT);     // Specify the input and output pins
pinMode(ampPin, OUTPUT);
pinMode(buttonPin, INPUT);
lcd.clear();
serial.begin(57600);
}

void loop() {
  Serial.println("Hello, World!");
  lcd.clear();                                // clear the LCD after each run through
  lcd.setCursor(0,0);                         // Now the screen will display the number of semitones the user will
  lcd.print("1 2 3  4  5  6 7");              // choose to shift in the transposition
  lcd.setCursor(0,1);
  lcd.print(" 8 9 10 11 12");
  int shift = 0;
//  delay(1000);
//  while( digitalRead(buttonPin) != LOW) {       // The user will use the potentiometer to select what level of transposition they would like to enact
//  	lcd.setCursor(0,0);
//  	lcd.print("1 2 3  4  5  6 7");
//  	lcd.setCursor(0,1);
//  	lcd.print(" 8 9 10 11 12  ");
//  	if (analogRead(potPin)<79)             // This string of if-else checks where the potentiometer is at a given point and
//  	{                                     // continuously loops while the user has not yet selected a transposition input
//  	  lcd.setCursor(0,1);                 // and once they do the shift value at that time is saved for later use
//  	  lcd.print("^");
//  	  shift = 1;                                                // Shift up 1 semitone
//  	}
//  	else if(analogRead(potPin)>=79 && analogRead(potPin)< 158)   // Shift up 2 semitones
//  	{
//  	  lcd.setCursor(2,1);
//  	  lcd.print("^");
//  	  shift = 2;
//  	}
//  	else if(analogRead(potPin)>=158 && analogRead(potPin)< 236)  // Shift up 3 semitones
//  	{
//  	  lcd.setCursor(4,1);
//  	  lcd.print("^");
//  	  shift = 3;
//  	}
//  	else if(analogRead(potPin)>=236 && analogRead(potPin)< 315)  // Shift up 4 semitones
//  	{
//  	  lcd.setCursor(7,1);
//  	  lcd.print("^");
//  	  shift = 4;
//  	}
//  	else if(analogRead(potPin)>=315 && analogRead(potPin)< 394)  // Shift up 5 semitones
//  	{
//  	  lcd.setCursor(10,1);
//  	  lcd.print("^");
//  	  shift = 5;
//  	}
//  	else if(analogRead(potPin)>=394 && analogRead(potPin)< 473)  // Shift up 6 semitones
//  	{
//  	  lcd.setCursor(13,1);
//  	  lcd.print("^");
//  	  shift = 6;
//  	}
//  	else if(analogRead(potPin)>=473 && analogRead(potPin)< 551)  // Shift up 7 semitones
//  	{
//  	  lcd.setCursor(15,1);
//  	  lcd.print("^");
//  	  lcd.clear();
//  	  shift = 7;
//  	}
//  	else if(analogRead(potPin)>=551 && analogRead(potPin)< 630)  // Shift up 8 semitones
//  	{
//  	  lcd.setCursor(1,0);
//  	  lcd.print("v");
//  	  shift = 8;
//  	}
//  	else if(analogRead(potPin)>=630 && analogRead(potPin)< 709)  // Shift up 9 semitones
//  	{
//  	  lcd.setCursor(3,0);
//  	  lcd.print("v");
//  	  shift = 9;
//  	}
//  	else if(analogRead(potPin)>=709 && analogRead(potPin)< 787)  // Shift up 10 semitones
//  	{
//  	  lcd.setCursor(5,0);
//  	  lcd.print("v");
//  	  shift = 10;
//  	}
//  	else if(analogRead(potPin)>=787 && analogRead(potPin)< 866)  // Shift up 11 semitones
//  	{
//  	  lcd.setCursor(8,0);
//  	  lcd.print("v");
//  	  shift = 11;
//  	}
//  	else                                                         // Shift up 12 semitones
//  	{
//  	  lcd.setCursor(11,0);
//  	  lcd.print("v");
//  	  shift = 12;
//  	}
//   }
   
  delay(1000);          //delay time for the user to start recording
  byteFloat freqs[3];
  
//  while (digitalRead(buttonPin) != LOW) { // Begin recording by saying if the button is not pressed (i.e. press the button to stop)
       Serial.println("Test");
       if (serial.available()) {
       	for (int i = 0; i < 3; i++) {
       		serial.readBytes(freqs[i].b, 4);
       		Serial.println(freqs[i].f);
       	}
       }
//  }

  for (int i = 0; i < 3; i++) {
    freqs[i].f *= pow(2, (float)shift / 12);    //Apply the transposition to each of the 3 harmonic tones
  }

  for (int sample = 0; sample < sampleRate * duration; sample++) {       
     float t = (float)sample / sampleRate;                          
     float music = 0.5 * sin(2 * pi * freqs[0].f * t) + 0.5 * sin(2 * pi * freqs[1].f * t) + 0.5 * sin(2 * pi * freqs[2].f * t);
     analogWrite(ampPin, music);      //send to amp and speaker
     
    }
     analogWrite(ampPin, 0);
     //the loop repeats for each note the user wants to transpose                                      
}

