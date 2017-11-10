// EXAMPLE FOR ESP8266

// A CYCLING 74 EXAMPLE TO COMMUNICATE WITH THIS SKETCH CAN BE FOUND INSIDE
// "applications/Cycling 74 Max 7/AsciiMassenger UDP.maxpat" OF THE FOLLOWING DOWNLOAD :
// https://github.com/SofaPirate/AsciiMassage/archive/master.zip


// INCLUDE THE CODE IN THE esp8266AP.h TAB.
#include <ESP8266WiFi.h>

const char* ssid     = "******";
const char* password = "*****";
IPAddress ip(10, 5, 0, 120);
IPAddress gateway(10, 5, 0, 1);
IPAddress subnet(255, 255, 255, 0);

// INCLUDE ESP8266 UDP
#include <WiFiUdp.h>
WiFiUDP udp;

// INCLUDE MASSAGE PARSER
#include <AsciiMassageParser.h>

// PACKER(FOR SENDING) AND PARSER(FOR RECEIVING) INSTANCES.
AsciiMassageParser inbound;

///////////
// SETUP //
///////////
void setup() {

  // INITIATE SERIAL COMMUNICATION.
  Serial.begin(57600);

  WiFi.config(ip , gateway , subnet );
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
  }

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
      if ( inbound.fullMatch("address") ) {
          // do something with the data        
      }
    }
  }
}



