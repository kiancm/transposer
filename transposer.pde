import ddf.minim.*;
import ddf.minim.analysis.*;
import ddf.minim.effects.*;
import ddf.minim.signals.*;
import ddf.minim.spi.*;
import ddf.minim.ugens.*;

import cc.arduino.*;
import org.firmata.*;
import processing.sound.AudioDevice;

int sampleRate = 44100;
int sampleSize = 4096;
Minim minim;
AudioInput ain;
AudioOutput aout;
Oscil wave1;
Oscil wave2;
Oscil wave3;
AudioDevice board; 
FFT fft;

void setup() {
  size(511, 511);
  minim = new Minim(this);
  ain = minim.getLineIn(Minim.MONO, sampleSize);
  aout = minim.getLineOut(Minim.MONO, sampleSize);
  aout.mute();
  wave1 = new Oscil(Frequency.ofPitch("C6"), .2, Waves.SINE);
  wave2 = new Oscil(Frequency.ofPitch("E6"), .2, Waves.SINE);
  wave3 = new Oscil(Frequency.ofPitch("G6"), .2, Waves.SINE);
  wave1.patch(aout);
  wave2.patch(aout);
  wave3.patch(aout);
  board = new AudioDevice(this, sampleRate, sampleSize);
  //fft = new FFT(aout.bufferSize(), aout.sampleRate());
  fft = new FFT(ain.bufferSize(), ain.sampleRate());
  
  //fft.forward(aout.mix);
  //float max_amp1 = -1;
  //float max_amp2 = -1;
  //float max_amp3 = -1;
  //float max_f1 = -1;
  //float max_f2 = -1;
  //float max_f3 = -1;
  //for (int i = 0; i < sampleSize; i++) {
  //  if (max_amp1 < fft.getBand(i)) {
  //    max_amp1 = fft.getBand(i); 
  //    max_f1 = fft.indexToFreq(i);
  //  }
  //}
  //fft.setFreq(max_f1,0);
  //for (int i = 0; i < sampleSize; i++) {
  //  if (max_amp2 < fft.getBand(i)) {
  //    max_amp2 = fft.getBand(i); 
  //    max_f2 = fft.indexToFreq(i);
      
  //  }
  //}
  //fft.setFreq(max_f2,0);
  //for (int i = 0; i < sampleSize; i++) {
  //  if (max_amp3 < fft.getBand(i)) {
  //    max_amp3 = fft.getBand(i); 
  //    max_f3 = fft.indexToFreq(i);
  //  }
  //}
  //println(
  //       "Largest Amplitudes: " + max_amp1 + ", " + max_amp2 + ", " + max_amp3 +
  //       "\nLargest Frequencies: " + max_f1 + ", " + max_f2 + ", " + max_f3
  //       );
}

void draw() {
  background(50, 50, 50);
  fft.forward(ain.mix);
  int[] max = new int[3];
  for (int i = 0; i < sampleSize; i++) {
    float v = fft.getBand(i);
    if (fft.getBand(max[0]) < v) {
        max[2] = max[1];
        max[1] = max[0];
        max[0] = i;
    }
    else if (fft.getBand(max[1]) < v) {
        max[2] = max[1];
        max[1] = i;
    }
    else if (fft.getBand(max[2]) < v) {
        max[2] = i;
    }
  }
  text("Largest Amplitudes: " + fft.getBand(max[0]) + ", " + fft.getBand(max[1]) + ", " + fft.getBand(max[2]), 0, 20);
  text("Largest Frequencies: " + fft.indexToFreq(max[0]) + ", " + fft.indexToFreq(max[1]) + ", " + fft.indexToFreq(max[2]), 0, 50);
  delay(300);
  //println(
  //       "Largest Amplitudes: " + max_amp1 + ", " + max_amp2 + ", " + max_amp3 +
  //       "\nLargest Frequencies: " + max_f1 + ", " + max_f2 + ", " + max_f3
  //       );
}