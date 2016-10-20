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
    msg.dispatch("echo", echo ); // If "led" is received, run ledMsg
  }
 
  delay(50);


}

// Process received massages.
void echo() {

  int i = msg.nextInt(); // ...read the next element as an int...
  float f = msg.nextFloat();
  byte b = msg.nextByte();


  msg.sendBegin("echo");
  msg.sendInt(i);
  msg.sendFloat(f);
  msg.sendByte(b);
  
  msg.sendEnd();
  

}