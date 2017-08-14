// ICLUDE MASSAGE
#include <AsciiMassagePacker.h>
#include <AsciiMassageParser.h>

// PACKER(FOR SENDING) AND PARSER(FOR RECEIVING) INSTANCES.
AsciiMassageParser inbound;
AsciiMassagePacker outbound;

bool sendAnalog = true;
unsigned long lastTimeSentAnalogReading = 0;

bool sendMs = true;
unsigned long lastTimeSentMs = 0;

///////////
// SETUP //
///////////
void setup() {

  // INITIATE SERIAL COMMUNICATION.
  Serial.begin(57600);

  // SET PIN 13 (DEBUG LEG) AS OUTPUT.
  pinMode(13, OUTPUT);

}

//////////////////////
// SEND AND RECEIVE //
//////////////////////
// THE FOLLOWING FUNCTIONS ARE HELPER FUNCTIONS.
// sendPacket() SENDS OUT A MASSAGE ONCE IT IS PACKED.
// receivePacket() CHECK FOR A COMPLETED MASSAGE AND
// INDICATES WHAT TO DO WITH ITS CONTENTS.

// SEND PACKED PACKET OVER SERIAL.
void sendPacket() {
  Serial.write(outbound.buffer(), outbound.size());
}

// RECEIVE OVER SERIAL AND PARSE ASCII PACKET
void receivePacket() {
  while ( Serial.available() ) {
    // PARSE INPUT. RETURNS 1 (TRUE) IF MASSAGE IS COMPLETE.
    if ( inbound.parse( Serial.read() ) ) {
      if ( inbound.fullMatch("d") ) {
        digitalWrite(13, inbound.nextInt() );
      } else if ( inbound.fullMatch("ms") ) {
        sendMs = inbound.nextInt();
      } else if ( inbound.fullMatch("a0") ) {
        sendAnalog = inbound.nextInt();
      } else {
        outbound.packEmpty("what?");
        sendPacket();
      }
    }
  }
}

//////////
// LOOP //
//////////
void loop() {

  receivePacket();

  if ( sendMs && (millis() - lastTimeSentMs >= 1000) ) {
    lastTimeSentMs = millis();
    
    outbound.beginPacket("ms");
    outbound.addLong(millis());
    outbound.endPacket();
    sendPacket();

  }

  if ( sendAnalog && (millis() -lastTimeSentAnalogReading  >= 1000) ) {
    lastTimeSentAnalogReading = millis();
    outbound.packOneInt("a0", analogRead(0) );
    sendPacket();
  }

}




