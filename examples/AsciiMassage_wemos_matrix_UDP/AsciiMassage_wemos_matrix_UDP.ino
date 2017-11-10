// EXAMPLE FOR ESP8266

// A CYCLING 74 EXAMPLE TO COMMUNICATE WITH THIS SKETCH CAN BE FOUND INSIDE
// "applications/Cycling 74 Max 7/AsciiMassenger UDP.maxpat" OF THE FOLLOWING DOWNLOAD :
// https://github.com/SofaPirate/AsciiMassage/archive/master.zip

// THIS EXAMPLE USES THE DEBUG LED PIN FOR THE WEMOS D1 MINI (https://wiki.wemos.cc/products:d1:d1_mini).
// CHANGE THIS PIN TO FIT YOUR MODEL.
int debugLedPin = 2;

// INCLUDE THE CODE IN THE esp8266AP.h TAB.
#include <ESP8266WiFi.h>

const char* ssid     = "****";
const char* password = "****";
IPAddress ip(10, 5, 0, 120);
IPAddress gateway(10, 5, 0, 1);
IPAddress subnet(255, 255, 255, 0);

// INCLUDE ESP8266 UDP
#include <WiFiUdp.h>
WiFiUDP udp;

// ICLUDE MASSAGE
#include <AsciiMassagePacker.h>
#include <AsciiMassageParser.h>

// PACKER(FOR SENDING) AND PARSER(FOR RECEIVING) INSTANCES.
AsciiMassageParser inbound;
AsciiMassagePacker outbound;

#include <WEMOS_Matrix_GFX.h>
MLED matrix(5); //set intensity=5

///////////
// SETUP //
///////////
void setup() {

  // INITIATE SERIAL COMMUNICATION.
  Serial.begin(57600);

  // SET PIN 13 (DEBUG LEG) AS OUTPUT.
  pinMode(debugLedPin, OUTPUT);

  WiFi.config(ip , gateway , subnet );
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    digitalWrite(debugLedPin, !digitalRead(debugLedPin));
    Serial.print(".");
  }
  digitalWrite(debugLedPin, LOW);
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());



  // START LISTENING ON UDP PORT 7777.
  udp.begin(7777);

}


//////////
// LOOP //
//////////
void loop() {

  // RECEIVE PACKETS OVER UDP
  if ( udp.parsePacket() ) {
    if ( inbound.parseStream( &udp ) ) {
      if ( inbound.fullMatch("data") ) {
        for ( int row = 0 ; row < 8 ; row++) {
          byte rowData = inbound.nextByte();
          for ( int col = 0 ; col < 8 ; col++) {
            matrix.drawPixel(row, col, bitRead(rowData, col)  );
          }
        }
        matrix.writeDisplay();
      }
    }
  }

}




