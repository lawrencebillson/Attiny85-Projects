#include <OneWire.h>  // The thermometer is connected to a OneWire bus - load the 'drivers' for that
#include <DallasTemperature.h> // It's a Dallas (Maxim) thermometer - load the code for that

// these #define lines are like a find/replace - the compiler will substitute the human readable value on the left
// with the actual definition on the right
#define THERMOMETER 3
#define POT A0
#define PIEZO 6

// Setup the OneWire and thermometer interface
OneWire oneWire(THERMOMETER); // THERMOMETER is defined above. If we change its pin, we only need to change it in one spot
DallasTemperature sensors(&oneWire);

void setup() {
  // This code runs once when  we power on
  sensors.begin(); // This tells the OneWire bus to start

  // Setup the output
  pinMode(PIEZO, OUTPUT); // Pin 6 is connected to the piezo speaker
}

void loop() {
  // This code will run in a loop forever
  float temp = 0; // We'll use the 'temp' variable for storing temperature from the thermometer
  int pot = 0; // We'll store the value of the potentiometer's wiper in variable 'pot'
  int ttone = 0; // We'll store the frequency (in Hertz) of what we'll play in the ttone variable

  // Turn off the tone
  noTone(PIEZO);
  

  // Read the temperature
  sensors.requestTemperatures(); // Send the command to get temperatures
  temp = sensors.getTempCByIndex(0); // store the temperature in variable 'temp'

  // Read the value of the pot wiper
  pot = analogRead(POT);

  // Some maths to get the tone in human audible range

  // The temperature sensor reads down to -55, we need to make it a positive number
  pot = pot + 50; // No such thing as a negative frequency!

  // Multiply it by the value of the potentiometer - this allows us to change its range
  ttone = ((pot * temp)/10);

  // Play the tone
  tone(PIEZO,ttone);

  // Delay (while playing the tone) for a few milliseconds before starting all over again
  delay(200);
  }
