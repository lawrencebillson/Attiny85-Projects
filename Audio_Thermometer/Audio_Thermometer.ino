#include <OneWire.h>  // The thermometer is connected to a OneWire bus - load the 'drivers' for that
#include <DallasTemperature.h> // It's a Dallas (Maxim) thermometer - load the code for that

// these #define lines are like a find/replace - the compiler will substitute the human readable value on the left
// with the actual definition on the right
#define THERMOMETER 3 // Pin 2 on the DIP-8 packaged chip
#define POT A2 // Pin 3 on the DIP-8 packaged chip
#define PIEZO 1 // Pin 6 on the DIP-8 packaged chip


// Setup the OneWire and thermometer interface
OneWire oneWire(THERMOMETER); // THERMOMETER is defined above. If we change its pin, we only need to change it in one spot
DallasTemperature sensors(&oneWire);

void setup() {
  // This code runs once when  we power on
  sensors.begin(); // This tells the OneWire bus to start

  // Tell the chip this pin is an output
  pinMode(PIEZO, OUTPUT);
  pinMode(POT, INPUT);
}

void loop() {
  // This code will run in a loop forever
  float temp = 0; // We'll use the 'temp' variable for storing temperature from the thermometer
  int pot = 0; // We'll store the value of the potentiometer's wiper in variable 'pot'
  long unsigned int ttone = 0; // We'll store the frequency (in Hertz) of what we'll play in the ttone variable
  long unsigned int unscaled = 0; 

  // Read the temperature
  sensors.requestTemperatures(); // Send the command to get temperatures
  temp = sensors.getTempCByIndex(0); // store the temperature in variable 'temp'

  // Read the value of the pot wiper
  pot = analogRead(POT);
  pot = pot / 10; 

  // The thermometer reports in degrees C, but down to -55. We need this to be a positive value 
  temp = temp + 60;
  // Square it?
  
  // Convert it to a range we can hear
  unscaled = (temp * pot) + (pot * 100);
  ttone = 4000 - unscaled;

  // Play the tone
  playTone(ttone,400); 
}

void playTone(int tone, int duration) {
  // The highest tone this can play on an 8Mhz Attiny85 is about '120' - about 7.8Khz
  // The lowest is about 4000 - 250Hz
  if(tone >= 4000) {
     tone = 4000;
  }
  if (tone <= 120) {
     tone = 120;
  }

  
  for (long i = 0; i < duration * 1000L; i += tone * 2) {
    digitalWrite(PIEZO, HIGH);
    delayMicroseconds(tone);
    digitalWrite(PIEZO, LOW);
    delayMicroseconds(tone);
  }
}



