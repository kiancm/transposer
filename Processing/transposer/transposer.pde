import cc.arduino.*;
import org.firmata.*;
import processing.sound.*;

int sampleRate = 44100;
float period = 1 / sampleRate;
int sampleSize = 10000;
float[] spectrum;
float[] os_spectrum;
float[] frequencies;
PrintWriter out;
SoundFile file; 
AudioDevice board; 
FFT fft;

void setup() {
  spectrum = new float[sampleSize];
  os_spectrum = new float[sampleSize / 2];
  frequencies = new float[sampleSize / 2];
  out = createWriter("fftout.txt");
  file = new SoundFile(this, dataPath("cmin.wav"));
  board = new AudioDevice(this, sampleRate, sampleSize);
  fft = new FFT(this, sampleSize);
  file.play();
  fft.input(file);
}

void draw() {
  fft.analyze(spectrum);
  for (int i = 0; i < sampleSize; i++) {
    spectrum[i] = abs(spectrum[i]) / sampleSize;
    out.println(spectrum[i]);
  }
  for (int j = 0; j < sampleSize / 2; j++) {
    os_spectrum[j] = spectrum[j];
    os_spectrum[j] *= 2;
    frequencies[j] = j;
    frequencies[j] *= sampleRate / sampleSize; 
    //out.println(os_spectrum[j]);
  }
  float max = -1;
  float max_f = -1;
  for (int k = 0; k < sampleSize / 2; k++) {
    if (max < os_spectrum[k]) {
      max = os_spectrum[k];
      max_f = frequencies[k];
    }
  }
  out.println(
             "Largest Amplitude: " + max +
             "\nLargest Frequency: " + max_f
             );
  exit();
}