#include <AsciiMassenger.h>
AsciiMassenger msg;

void setup() {
  Serial.begin(57600); // Initiate serial communication.
}

void loop() {
  msg.sendBegin("bob");
  msg.sendInt(32);
  msg.sendFloat(4.5);
  msg.sendEnd();
  delay(1000);
}
