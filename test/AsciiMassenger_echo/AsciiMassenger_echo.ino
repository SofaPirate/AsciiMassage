#include <AsciiMassage.h>


// Instantiate Massage objects for receiving and sending massages
AsciiMassage inbound;
AsciiMassage outbound;

void setup() {

  // Initiate serial communication.
  Serial.begin(57600);

  // Setup pin 13 as a digital output.
  pinMode(13, OUTPUT);

}

void loop() {

  while ( Serial.available() ) {
    // PARSE INPUT AND EXECUTRE massageReceived IF A COMPLETE MASSAGE IS RECEIVED 
    inbound.parse( Serial.read() , massageReceived );
  }

}

// Process received massages.
void massageReceived() {

  if ( inbound.fullMatch("echo")) {
    int i = inbound.nextInt(); // ...read the next element as an int...
    float f = inbound.nextFloat();
    byte b = inbound.nextByte();

    outbound.beginPacket("echo");
    outbound.addInt(i);
    outbound.addFloat(f);
    outbound.addByte(b);
    outbound.endPacket();
    
    Serial.write(outbound.buffer);
    
  } else {
    
    outbound.beginPacket("what?");
    outbound.endPacket();
    Serial.write( outbound.buffer , outbound.size );
    
  }
}
