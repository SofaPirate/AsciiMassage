// EXAMPLE FOR ESP8266

// A CYCLING 74 EXAMPLE TO COMMUNICATION WITH THIS SKETCH CAN BE FOUND INSIDE 
// "applications/Cycling 74 Max 7/AsciiMassenger UDP.maxpat" OF THE FOLLOWING DOWNLOAD :
// https://github.com/SofaPirate/AsciiMassage/archive/master.zip

// THIS EXAMPLE USES THE DEBUG LED PIN FOR THE WEMOS D1 MINI (https://wiki.wemos.cc/products:d1:d1_mini).
// CHANGE THIS PIN TO FIT YOUR MODEL.
int debugLedPin = 2;

// INCLUDE THE CODE IN THE esp8266AP.h TAB.
#include "esp8266AP.h"


// INCLUDE ESP8266 UDP
#include <WiFiUdp.h>
WiFiUDP udp;
IPAddress recipientIp(192, 168, 4, 2); // THIS IS USUALLY THE FIRST *DEFAULT* ADDRESS GIVEN TO A CLIENT BY THE ACCES POINT.


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
  pinMode(debugLedPin, OUTPUT);

  // START THE ACCESS POINT WITH A BASE NAME OF "asciimassage".
  // THE LAST THREE HEX BYTES OF THE MAC ADDRESS WILL BE APPENDED
  // TO THE BASE NAME. SEE THE esp8266AP.h TAB FOR THE CODE.
  startWifiAp("asciimassage");

  // START LISTENING ON UDP PORT 7777.
  udp.begin(7777);

}

//////////////////////
// SEND AND RECEIVE //
//////////////////////
// THE FOLLOWING FUNCTIONS ARE HELPER FUNCTIONS.
// sendPacket() SENDS OUT A MASSAGE ONCE IT IS PACKED.
// receivePacket() CHECK FOR A COMPLETED MASSAGE AND
// INDICATES WHAT TO DO WITH ITS CONTENTS.

// SEND PACKED PACKET OVER UDP.
void sendPacket() {
  udp.beginPacket(recipientIp, 7777);
  udp.write(outbound.buffer(), outbound.size());
  udp.endPacket();
}

// RECEIVE OVER UDP AND PARSE ASCII PACKET
void receivePacket() {
  if ( udp.parsePacket() ) {
    while ( udp.available() ) {
      // PARSE INPUT. RETURNS 1 (TRUE) IF MASSAGE IS COMPLETE.
      if ( inbound.parse( udp.read() ) ) {
        if ( inbound.fullMatch("d") ) {
          digitalWrite(debugLedPin, inbound.nextInt() );
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

  if ( sendAnalog && (millis() - lastTimeSentAnalogReading  >= 1000) ) {
    lastTimeSentAnalogReading = millis();
    outbound.packOneInt("a0", analogRead(0) );
    sendPacket();
  }

}




