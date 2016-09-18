#include <OneWire.h>  // The thermometer is connected to a OneWire bus - load the 'drivers' for that
#include <DallasTemperature.h> // It's a Dallas (Maxim) thermometer - load the code for that

// these #define lines are like a find/replace - the compiler will substitute the human readable value on the left
// with the actual definition on the right
#define THERMOMETER 3 // Pin 2 on the DIP-8 packaged chip
#define POT A2 // Pin 3 on the DIP-8 packaged chip
#define PIEZO 1 // Pin 5 on the DIP-8 packaged chip


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
  int temp = 0; // We'll use the 'temp' variable for storing temperature from the thermometer
  int pot = 0; // We'll store the value of the potentiometer's wiper in variable 'pot'
  int ttone = 0; // We'll store the frequency (in Hertz) of what we'll play in the ttone variable


  // Read the temperature
  sensors.requestTemperatures(); // Send the command to get temperatures
  temp = sensors.getTempCByIndex(0); // store the temperature in variable 'temp'

  // Read the value of the pot wiper
  pot = analogRead(POT);
  pot = pot + 10; // Add a couple, otherwise we get a divide by zero
  pot = pot * 4;

  

  playTone(pot,200); 
  }

void playTone(int tone, int duration) {
  for (long i = 0; i < duration * 1000L; i += tone * 2) {
    digitalWrite(PIEZO, HIGH);
    delayMicroseconds(tone);
    digitalWrite(PIEZO, LOW);
    delayMicroseconds(tone);
  }
}



