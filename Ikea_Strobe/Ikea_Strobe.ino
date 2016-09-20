
// Setup runs when the chip is powered on or reset
void setup() {
  pinMode(0, OUTPUT); // Pin 0 (pin 5 on an 8 pin DIP) is connected to our MOSFET and the lamp
  pinMode(A2, INPUT);  // Pin A2 (pin 3 on an 8 pin DIP) is connected to our pot's wiper
}

// Loop will repeat forever
void loop() {
  int wiper; // We will store the value of the wiper in this variable. It will range from 0 (0v) to 1023 (VCC, or 4v)
             // we need to declare variables before we use them. An int will store this integer value nicely
             
  digitalWrite(0, HIGH);   // turn on the lamp
  delay(10);               // wait for 10 ms
  digitalWrite(0, LOW);    // turn off the lamp

  // Now we need to leave the lamp off for a few moments, that way, it'll be a strobe
  wiper = analogRead(A2);  // Store the wiper's value in 'wiper' variable

  delay(wiper);              // wait for the value (0 to 1023) we read from the pot, then repeat
}
