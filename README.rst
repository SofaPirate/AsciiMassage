# AsciiMassage

*AsciiMassage* is a microcontroller message packer and parser for the ASCII format in different protocols. An *AsciiMassage* compatible message is called a *massage*.

A *massage* message always starts with an address string and is followed by a user defined number of bytes, ints, longs, or floats.  The address string is used to route the message as in [Open Sound Control (OSC)](http://opensoundcontrol.org/introduction-osc).

[This repository](https://github.com/SofaPirate/AsciiMassage) is the ASCII implementation of the [Massage API](https://github.com/SofaPirate/Massenger).

*Massages* can be sent and received over different communication protocols such as serial, UDP, or web sockets.

----