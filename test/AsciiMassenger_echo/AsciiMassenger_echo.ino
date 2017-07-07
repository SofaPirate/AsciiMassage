#include <AsciiMassenger.h>


// Instantiate a Massenger object,
AsciiMassenger msg;

void setup() {

  // Initiate serial communication.
  Serial.begin(57600);

  // Setup pin 13 as a digital output.
  pinMode(13, OUTPUT);

}

void loop() {

  while ( Serial.available() ) {
    // PARSE INPUT AND EXECUTRE massageReceived IF A COMPLETE MASSAGE IS RECEIVED 
    msg.parse( Serial.read() , massageReceived );
  }

}

// Process received massages.
void massageReceived() {

  if ( msg.fullMatch("echo")) {
    int i = msg.nextInt(); // ...read the next element as an int...
    float f = msg.nextFloat();
    byte b = msg.nextByte();

    msg.beginPacket("echo");
    msg.addInt(i);
    msg.addFloat(f);
    msg.addByte(b);
    msg.endPacket();
    
    Serial.write(msg.buffer);
    
  } else {
    msg.beginPacket("echo");
    Serial.write( msg.buffer , msg.size );
  }
}
