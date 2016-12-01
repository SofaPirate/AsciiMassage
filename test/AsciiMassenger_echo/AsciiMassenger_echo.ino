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


  while ( msg.parsePacket() ) { // Check if there is a new message
    msg.dispatch("echo", echo ); // If "led" is received, run ledMsg
  }
 
  delay(50);


}

// Process received massages.
void echo() {

  int i = msg.nextInt(); // ...read the next element as an int...
  float f = msg.nextFloat();
  byte b = msg.nextByte();


  msg.beginPacket("echo");
  msg.addInt(i);
  msg.addFloat(f);
  msg.addByte(b);
  
  msg.endPacket();
  

}