#include <AsciiMassageDecoder.h>
#include <AsciiMassageEncoder.h>


// Instantiate Massage objects for encoding and decoding massages
AsciiMassageDecoder decoder;
AsciiMassageEncoder encoder;

void setup() {

  // Initiate serial communication.
  Serial.begin(57600);

  // Setup pin 13 as a digital output.
  pinMode(13, OUTPUT);

}

void loop() {

  while ( Serial.available() ) {
    // PARSE INPUT AND EXECUTRE massageReceived IF A COMPLETE MASSAGE IS RECEIVED 
    decoder.parse( Serial.read() , massageReceived );
  }

}

// Process received massages.
void massageReceived() {

  if ( decoder.fullMatch("echo")) {
    int i = decoder.nextInt(); // ...read the next element as an int...
    float f = decoder.nextFloat();
    byte b = decoder.nextByte();

    encoder.beginPacket("echo");
    encoder.addInt(i);
    encoder.addFloat(f);
    encoder.addByte(b);
    encoder.endPacket();
    
    Serial.write(encoder.buffer);
    
  } else {
    
    encoder.sendEmpty("what?");
    Serial.write( encoder.buffer , encoder.size );
    
  }
}
