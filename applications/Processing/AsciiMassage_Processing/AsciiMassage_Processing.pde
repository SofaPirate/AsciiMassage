import processing.serial.*;
/*
Lorsque vous demarrez ce code, tout les ports
series s'affichent dans la fenetre de deboguage.
Changer la variable ''portName'' pour qu'elle
corresponde au nom du port serie qui correspond a
l'Arduino.

Sous Linux et OS X le nom du port ressemble a ceci :
String portName = "/dev/tty.usbmodem24121";

Sous Windows, il ressemble a ceci :
String portName = "COM4";
*/

String portName = "COM10";

// Declarer une instance de la classe Serial:
Serial serial;

AsciiMassageParser inbound;

long msFromArduino = 0;

void setup() {
  size(512, 256);

  // Affiche les noms des ports.
  println(Serial.list());

  // Creer une instance de la classe Serial avec
  // une vitesse de 57600 baud:
  serial = new Serial(this, portName, 57600);
  

   inbound = new AsciiMassageParser(this);
   
}


void draw() {
    
  background(0);
  
   while ( serial.available( ) > 0 ) inbound.parse( serial.read( ) , "massageReceived" );

  textAlign(CENTER, CENTER);
  text( "ms : " + msFromArduino , width * 0.5 , height * 0.5);
  
}

void massageReceived() {

  if ( inbound.fullMatch("ms") ) {
  
    msFromArduino = inbound.nextLong();
  }
  
}

/*
void mousePressed() {
  
  if ( debugLed == 0 ) debugLed = 1;
  else debugLed = 0;
  
  serial.write("led"+" "+debugLed+"\n");
  
}
*/