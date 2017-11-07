// A PROCESSING EXAMPLE TO COMMUNICATE WITH THIS SKETCH CAN BE FOUND  INSIDE
// "extras/applications/Processing/AsciiMassage_Processing/" OF THE FOLLOWING DOWNLOAD :
// https://github.com/SofaPirate/AsciiMassage/archive/master.zip

// A CYCLING 74 EXAMPLE TO COMMUNICATE WITH THIS SKETCH CAN BE FOUND INSIDE 
// "extras/applications/Cycling 74 Max 7/AsciiMassenger.maxpat" OF THE FOLLOWING DOWNLOAD :
// https://github.com/SofaPirate/AsciiMassage/archive/master.zip


// INCLUDE MASSAGE
#include <AsciiMassagePacker.h>
#include <AsciiMassageParser.h>

// PACKER(FOR SENDING) AND PARSER(FOR RECEIVING) INSTANCES.
AsciiMassageParser inbound;
AsciiMassagePacker outbound;


///////////
// SETUP //
///////////
void setup() {

  // INITIATE SERIAL COMMUNICATION.
  Serial.begin(57600);

}

//////////////////////
// SEND AND RECEIVE //
//////////////////////
// THE FOLLOWING FUNCTIONS ARE HELPER FUNCTIONS.
// sendPacket() SENDS OUT A PRE-PACKED MASSAGE.
// receivePacket() CHECK FOR A COMPLETED MASSAGE AND
// INDICATES WHAT TO DO WITH ITS CONTENTS.

// SEND A PRE-PACKED PACKET OVER SERIAL.
void sendPacket() {
  Serial.write(outbound.buffer(), outbound.size());
}

// RECEIVE OVER SERIAL AND PARSE ASCII PACKET
void receivePacket() {
  while ( Serial.available() ) {
    // PARSE INPUT. RETURNS 1 (TRUE) IF MASSAGE IS COMPLETE.
    if ( inbound.parse( Serial.read() ) ) {
      if ( inbound.fullMatch("address") ) {
      	byte byteValue = inbound.nextByte();
        int intValue = inbound.nextInt();
        float floatValue = inbound.nextFloat();
        long longValue = inbound.nextLong();
      } else {
        // SEND "what?" WHEN A MASSAGE IS NOT RECOGNIZED.
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
 

  // BUILD A PACKET:

  /// Begins the sending of a message.
  outbound.beginPacket("address");

  /// Adds a byte.
  outbound.addByte(45);

  /// Adds an int.
  outbound.addInt(1024);

  /// Adds a long.
  outbound.addLong(64823);

  /// Adds a float.
  outbound.addFloat(183.92);

  /// Ends the sending of a message.
  outbound.endPacket();
  
  // SEND THE PACKET:

  sendPacket();

}




