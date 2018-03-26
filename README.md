# AsciiMassage

*AsciiMassage* allows the sending and receiving of messages. 
More precisely, it is a microcontroller *massage* packer and parser for the ASCII format for any type of stream (Serial, UDP, etc).  A *massage* message always starts with an address string and is followed by a user defined number of elements (bytes, ints, longs, floats or strings).  The address string is used to route the message as in [Open Sound Control (OSC)](http://opensoundcontrol.org/introduction-osc).
[This repository](https://github.com/SofaPirate/AsciiMassage) is the ASCII implementation of the [Massage API](https://github.com/SofaPirate/Massenger).

Sending (packing) a massage example
-------------------------------------

Add the library to the top of your code and instantiate an AsciiMassagePacker called "outbound":
```
#include <AsciiMassagePacker.h>
AsciiMassagePacker outbound;
```

Pack a *massage* and then steam it through Serial:
```
outbound.beginPacket("value"); // Start a packet with the address called "value".
outbound.addLong( millis() ); // Add the milliseconds.
outbound.addInt( analogRead(0) ); // Add a reading of analog 0.
outbound.streamPacket(&Serial); // End the packet and stream it.
```

Receiving (parsing) a massage example
---------------------------------------

Add the library to the top of your code and instantiate an AsciiMassageParser called "inbound":
```
#include <AsciiMassageParser.h>
AsciiMassageParser inbound;
```
Inside loop() parse the Serial stream with parse(). If parse() returns true, the massage is completed and ready.
```
    if ( inbound.parseStream( &Serial ) ) {
       // parse completed massage elements here.
    }
```

This example parses the elements of a  massage that starts with the address "value" and that contains one long followed by one int:
```
// Does the massage's address match "value"?
if ( inbound.fullMatch ("value") ) {
    // Get the first long.
    long ms = inbound.nextLong();
    // Get the next int.
    int an0 = inbound.nextInt();
}
```

The complete block of code is as follows:
```
 if ( inbound.parseStream( &Serial ) ) {
    // parse completed massage elements here.

    // Does the massage's address match "value"?
    if ( inbound.fullMatch ("value") ) {
        // Get the first long.
        long ms = inbound.nextLong();
        // Get the next int.
        int an0 = inbound.nextInt();
    }

    }
```

AsciiMassagePacker basic methods
-------------

`AsciiMassagePacker()` : Constructor

`beginPacket(const char* address)` : Begins a packet (erasing any previous packet).

`addByte(uint8_t value)` : Adds a byte.

`addInt(int16_t value)` : Adds an int.

`addLong(int32_t value)` : Adds a long.

`addFloat(float value)` : Adds a float.

`addString(const char* string)` : Adds a string.

`streamPacket( Stream* )` : Ends the packet and sends out the stream (Serial, UDP, etc).

`streamEmpty(Stream*, const char *address)` : Stream a packet with no arguments.
  
`streamOneByte(Stream*, const char *address, uint8_t value)` : Stream a packet with a single byte element.

`streamOneInt(Stream*, const char *address, int16_t value)` : Stream a packet with a single int element.

`streamOneLong(Stream*, const char *address, int32_t value)` :   Stream a packet with a single long element.

`streamOneFloat(Stream*, const char *address, float value)` : Stream a packet with a single float element.

`streamOneString(Stream* , const char *address, const char * string)` : Stream a packet with a single string element.



AsciiMassageParser basic methods
-------------

`AsciiMassageParser ()`: Constructor.
 
`parseStream ( Stream)` : Reads the stream, flushing previous message if needed. Returns true if a new message has arrived. 
 
`fullMatch (const char *address)` : Return true if current message matches "address".
 
`nextByte ()` : Returns next byte in the parsed massage.

`nextFloat()` : Returns next float in the parsed massage.

`nextInt ()` : Returns next int in the parsed massage.

`nextLong()` : Returns next long in the parsed massage.
 
`nextString(char* stringBuffer, int bufferLength)` : Fills stringBuffer with the next string in the parsed massage. Returns the number of characters written.




