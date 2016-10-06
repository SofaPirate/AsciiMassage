#include <AsciiMassenger.h>


// Instantiate a Massenger object,
// link it to Serial
AsciiMassenger msg;  // same as AsciiMassenger msg =  AsciiMassenger(&Serial);

void setup() {

  // Initiate serial communication.
  Serial.begin(57600);

  // Setup pin 13 as a digital output.
  pinMode(13, OUTPUT);

}

void loop() {


  while ( msg.receive() ) { // Check if there is a new message
    msg.dispatch("led", ledMsg ); // If "led" is received, run ledMsg
  }
  

  // Send analogRead(0)
  msg.sendBegin("a0");
  msg.sendInt(analogRead(0));
  msg.sendEnd();

  msg.send("fff"); 

  delay(50);


}

// Process received massages.
void ledMsg() {

  int value = msg.nextInt(); // ...read the next element as an int...
  digitalWrite(13, value); // ...and set the state of pin 13 to the value.


}
