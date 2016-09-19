#include <OneWire.h>  // The thermometer is connected to a OneWire bus - load the 'drivers' for that
#include <DallasTemperature.h> // It's a Dallas (Maxim) thermometer - load the code for that

// these #define lines are like a find/replace - the compiler will substitute the human readable value on the left
// with the actual definition on the right
#define THERMOMETER 3 // Pin 2 on the DIP-8 packaged chip
#define POT A2        // Pin 3 on the DIP-8 packaged chip
#define PIEZO 1       // Pin 7 on the DIP-8 packaged chip


// Setup the OneWire and thermometer interface
OneWire oneWire(THERMOMETER); // THERMOMETER is defined above. If we change its pin, we only need to change it in one spot
DallasTemperature sensors(&oneWire);

void setup() {
  // This code runs once when  we power on
  sensors.begin(); // This tells the OneWire bus to start
  pinMode(PIEZO, OUTPUT);
}

void loop() {
  // This code will run in a loop forever
  float temp = 0; // We'll use the 'temp' variable for storing temperature from the thermometer
  int pot = 0; // We'll store the value of the potentiometer's wiper in variable 'pot'
  long unsigned int ttone = 0; // We'll store the frequency (in Hertz) of what we'll play in the ttone variable

  // Read the temperature
  sensors.requestTemperatures(); // Send the command to get temperatures
  temp = sensors.getTempCByIndex(0); // store the temperature in variable 'temp'

  // Read the value of the pot wiper
  
  pot = analogRead(POT);
  pot = pot / 10; 

  // The thermometer reports in degrees C, but down to -55. We need this to be a positive value 
  temp = temp + 60;
  
  // Convert it to a range we can hear
  ttone = (pot * temp) - (pot * 50);

  tinyTone(ttone,600);
}


void tinyTone(long int freq,long int duration) {
  long unsigned int period;
  long unsigned int cycles;
  
  // Work out the period of our frequency in usec
  period = 1000000 / freq;

  // We're given a duration in ms so need to convert it
  duration = duration * 1000;

  // how many cycles of this will we need to get to our duration?
  cycles = duration / period;

  // Devide the period in half, we'll be off half the time, and on half the time
  period = period / 2;

  // Need to add a little fudge factor of about 5% - the looping takes a tiny bit of time
  // do this in two steps to keep it all integer maths
  period = period * 95;
  period = period / 100;

  while (cycles != 0) { // comparing a number against zero is more hardware efficient
    digitalWrite(PIEZO,HIGH);
    delayMicroseconds(period);
    digitalWrite(PIEZO,LOW);
    delayMicroseconds(period); 
    cycles--; // counting down is also more efficient on the AVR
  }
}
  
