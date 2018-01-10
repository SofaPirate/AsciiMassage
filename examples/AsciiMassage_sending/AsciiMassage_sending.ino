// This example uses :
// * the ASCII format for packing the massage;
// * the Serial protocol for sending the massage.


// Include AsciiMassage
#include <AsciiMassage.h>

// Instantiate an AsciiMassagePacker for packing massages.
AsciiMassagePacker outbound;

void setup() {

  // Start the Serial protocol at 57600 baud.
  Serial.begin(57600);

}

void loop() {

  // This is just an example of sending dummy values.
  // You must customize with your own addresses and values.
  // The application receiving the massage must expect a massage 
  // with the same address ("value" in this case).
  outbound.beginPacket("value"); // Start a packet with the address called "value".
  outbound.addLong( millis() ); // Add the milliseconds.
  outbound.addInt( analogRead(0) ); // Add a reading of analog 0.
  outbound.streamPacket(&Serial); // End and send packet through Serial.

  // You can view the sent massages in Arduino's Serial Monitor
  // because Arduino's Serial Monitor uses the ASCII format.

  // A little delay to slow down everything for this example.
  // It is not required in your use.
  delay(1000);

}
