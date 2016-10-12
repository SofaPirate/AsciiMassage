#include <AsciiMassenger.h>
AsciiMassenger msg;

void setup() {
  Serial.begin(57600); // Initiate serial communication.
}

void loop() {
 while ( msg.receive() ) { // Check if there is a new massage
    msg.dispatch("debugLed", debugLedMsg); // If "debugLed" is received, execute debugLedMsg
  }
}

void debugLedMsg() { // dispatch function
    pinMode(13,OUTPUT);
    int state = msg.nextInt(); // Get the first int from the "debugLed" massage
    digitalWrite(13,state); // Apply the value to the debug LED
}

