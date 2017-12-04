// This example uses :
// * the ASCII format for packing the massage;
// * the Serial protocol for sending the massage.

// INCLUDE MASSAGE
#include <AsciiMassagePacker.h>
#include <AsciiMassageParser.h>

// PACKER(FOR SENDING) AND PARSER(FOR RECEIVING) INSTANCES.
AsciiMassageParser inbound;
AsciiMassagePacker outbound;

// CREATE AN EMPTY STRING TO HOLD THE RECEIVED STRING.
// AS DETERMINDED BY RECEIVED_STRING_MAX_SIZE, THIS EMPTY 
// STRING CAN HOLD UP TO 63 CHARACTERS (THE LAST POSITION 
// IS THE NULL CHARACTER THAT ENDS THE STRING).
#define RECEIVED_STRING_MAX_SIZE 64
char receivedString[RECEIVED_STRING_MAX_SIZE];


void setup() {

  // Start the Serial protocol at 57600 baud.
  Serial.begin(57600);

}

void loop() {

  while ( inbound.parseStream( &Serial) ) {
    // PARSE INPUT. RETURNS 1 (TRUE) IF MASSAGE IS COMPLETE.

      if ( inbound.fullMatch("echo") ) {

        int stringLength = inbound.nextString(receivedString,RECEIVED_STRING_MAX_SIZE);
        outbound.beginPacket("echo"); // Start a packet with the address called "echo".
        outbound.addString(receivedString);
        outbound.addInt(stringLength);
        outbound.streamPacket(&Serial); // End and stream the packet.
        
        outbound.beginPacket("test"); // Start a packet with the address called "test".
        outbound.addString("this is a string");
        outbound.streamPacket(&Serial); // End and stream the psacket.

        
        
      } else {
        // SEND "what?" WHEN A MASSAGE IS NOT RECOGNIZED.
        outbound.streamEmpty(&Serial,"what?");
        
      }
    
  }

  // You can view the sent massages in Arduino's Serial Monitor
  // because Arduino's Serial Monitor uses the ASCII format.


}
