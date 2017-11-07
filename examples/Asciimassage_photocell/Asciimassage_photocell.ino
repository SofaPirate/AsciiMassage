// ICLUDE CHRONO
#include <Chrono.h>

Chrono messageSendInterval = Chrono();

// ICLUDE MASSAGE PACKER
#include <AsciiMassagePacker.h>

// PACKER(FOR SENDING) INSTANCE:
AsciiMassagePacker outbound;

void setup() {

  // INITIATE SERIAL COMMUNICATION.
  Serial.begin(57600);

}

void loop() {

  if ( messageSendInterval.hasPassed(100) ) {
    messageSendInterval.restart();

    int photocellReading = analogRead( A0 );

    outbound.beginPacket("a0");
    outbound.addInt( photocellReading );
    outbound.endPacket();

    Serial.write(outbound.buffer(), outbound.size());

  }

}
