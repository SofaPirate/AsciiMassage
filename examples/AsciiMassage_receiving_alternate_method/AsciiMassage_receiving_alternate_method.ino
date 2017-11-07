// This example uses :
// * the Serial protocol for receiving the massage.
// * the ASCII format for unpacking the massage;



// Include AsciiMassageParser.h for ASCII format massage parsing.
#include <AsciiMassageParser.h>

// Instantiate an AsciiMassageParser for parsing massages.
AsciiMassageParser inbound;

void setup() {

  // Start the Serial protocol at 57600 baud.
  Serial.begin(57600);

}

void loop() {

  // Parse received data as long as it is available over serial
  // and call the function "massageReceived" when a completed
  // massage has been received.
  while ( Serial.available() ) {
    inbound.parse( Serial.read() , massageReceived );
  }
  
}

// This function will be called when a completed massage
// has been received. Its name must match the name given
// in the second argument of parse() (see loop() above).
void massageReceived() {

  // We are expecting a massage that starts with the address 
  // "value" and that contains one long followed by one int. See 
  // the "AsciiMassenger_packing_sending" example to see
  // how this data is sent.

  // Check the address of the massage.
  if ( inbound.fullMatch ("value") ) {
    // Get the first long.
    long ms = inbound.nextLong();
    // Get the next int.
    int an0 = inbound.nextInt();

    // The "ms" and "an0" are not used for anything
    // in this example. This is simply an example of how 
    // to receive and parse the massage.
  }

}

