#include <AsciiMassenger.h>
AsciiMassenger msg;

// INCLUDE CHRONO LIBRARY : http://github.com/thomasfredericks/Chrono
#include <Chrono.h>
Chrono serialChrono;

void setup() {
  Serial.begin(57600); // Initiate serial communication.
}

void loop() {
  while ( msg.receive() ) { // Check if there is a new massage
    msg.dispatch("dw", dw); // If "dw" is received, execute dw
    msg.dispatch("aw", aw); // If "aw" is received, execute aw
  }

  if  (serialChrono.hasPassed(50)) {
  serialChrono.restart();
  
    msg.sendBegin("dr2");
    msg.sendInt(digitalRead(2));
    msg.sendEnd();
    
    msg.sendBegin("ar0");
    msg.sendInt(analogRead(0));
    msg.sendEnd();
  }
}

void dw() { // dispatch function : digitalWrite( int , int)
  int pin =  msg.nextInt(); // Get the first int as the pin
  pinMode(pin, OUTPUT);
  int state = msg.nextInt(); // Get the second int as the state
  digitalWrite(pin, state);
}

void aw() { // dispatch function : analogWrite( int , int)
  int pin =  msg.nextInt(); // Get the first int as the pin
  int pwm = msg.nextInt(); // Get the second int as the pwm
  analogWrite(pin, pwm); // Apply the value to the debug LED
}

