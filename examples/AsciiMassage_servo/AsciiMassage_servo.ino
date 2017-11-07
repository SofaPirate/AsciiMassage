// THIS EXAMPLE SHOWS HOW TO CONTROL A SERVOMOTOR ATTACHED TO PIN 9
// WITH ASCIIMASSAGE.
// THE "angle" MASSAGE WILL CONTROL THE ANGLE OF THE SERVO IN DEGREES.
// THE "us" MASSAGE WILL CONTROL THE ANGLE OF THE SERVO IN MICROSECONDS.

// A PROCESSING EXAMPLE TO COMMUNICATE WITH THIS SKETCH CAN BE FOUND  INSIDE
// "extras/applications/Processing/" OF THE FOLLOWING DOWNLOAD :
// https://github.com/SofaPirate/AsciiMassage/archive/master.zip

// A CYCLING 74 EXAMPLE TO COMMUNICATE WITH THIS SKETCH CAN BE FOUND INSIDE
// "extras/applications/Cycling 74 Max 7/" OF THE FOLLOWING DOWNLOAD :
// https://github.com/SofaPirate/AsciiMassage/archive/master.zip

// INCLUDE MASSAGE
#include <AsciiMassagePacker.h>
#include <AsciiMassageParser.h>

// PACKER(FOR SENDING) AND PARSER(FOR RECEIVING) INSTANCES.
AsciiMassageParser inbound;
AsciiMassagePacker outbound;

// INCLUDE SERVO.
#include <Servo.h>

// INSTANTIATE A SERVO OBJECT.
Servo myServo;


///////////
// SETUP //
///////////
void setup() {

  // INITIATE SERIAL COMMUNICATION.
  Serial.begin(57600);

  // ATTACH THE SERVO TO PIN 9
  myServo.attach(9);

}

//////////////////////
// SEND AND RECEIVE //
//////////////////////
// THE FOLLOWING FUNCTIONS ARE HELPER FUNCTIONS.
// sendPacket() SENDS OUT A PRE-PACKED MASSAGE.
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

      // THE "angle" MASSAGE WILL CONTROL THE ANGLE OF THE SERVO IN DEGREES.
      if ( inbound.fullMatch("angle") ) {

        int value = inbound.nextInt();
        myServo.write( value );

      // THE "us" MASSAGE WILL CONTROL THE ANGLE OF THE SERVO IN MICROSECONDS.
      } else if ( inbound.fullMatch("us") ) {

        int value = inbound.nextInt();
        myServo.writeMicroseconds( value );

      // SEND "what?" WHEN A MASSAGE IS NOT RECOGNIZED.
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


}




