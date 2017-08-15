#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <WiFiManager.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
//#include <DNSServer.h>

class _EzEsp8266 {

  private :
    bool debugToSerial = false;

  public:
    _EzEsp8266() {


    }

    void debugToSerial(bool activate) {
      debugToSerial = active;

    }

    void startAccessPoint(const char* ssid, const char* password, bool appendMacAddress = false) {
      if ( debugToSerial ) Serial.println("EzEsp8266: Trying to start access point.");

      WiFi.mode(WIFI_AP);
      
      if ( appendMacAddress ) {
        // Do a little work to get a unique-ish name. Append the
        // last three bytes of the MAC (HEX'd) :
        uint8_t mac[WL_MAC_ADDR_LENGTH];
        WiFi.softAPmacAddress(mac);
        String threeLastHexBytes = String(mac[WL_MAC_ADDR_LENGTH - 3], HEX) +
                                   String(mac[WL_MAC_ADDR_LENGTH - 2], HEX) +
                                   String(mac[WL_MAC_ADDR_LENGTH - 1], HEX);
        threeLastHexBytes.toLowerCase();
        String apNameString = String(ssid) + threeLastHexBytes;

        char apName[apNameString.length() + 1];
        memset(apName, 0, apNameString.length() + 1);

        for (int i = 0; i < apNameString.length(); i++)
          apName[i] = apNameString.charAt(i);

        WiFi.softAP(apName, password);  

      } else {
        WiFi.softAP(ssid, password);
      }
    }

    void startAccessPoint(const char* ssid, const char* password, IPAddress ip , IPAddress gateway, IPAddress subnet, bool appendMacAddress = false) {
      if ( debugToSerial ) Serial.println("EzEsp8266: Setting custom access point configuration.");
      WiFi.softAPConfig (ip, gateway, subnet) ;
      startAccessPoint(ssid, password, appendMacAddress)
    }


    void connect(const char* ssid, const char* password) {
      if ( debugToSerial ) Serial.println("EzEsp8266: trying to connect");
      WiFi.begin(ssid, password);
    }

    void connect(const char* ssid, const char* password, IPAddress ip , IPAddress gateway, IPAddress subnet) {

      if ( debugToSerial ) Serial.println("EzEsp8266: trying to connect");
      WiFi.config(ip, gateway, subnet);
      WiFi.begin(ssid, password);

    }


    void autoConnect(const char* fallback_ssid, const char* fallback_password) {

      WiFiManager wifiManager;
      wifiManager.autoConnect(fallback_ssid, fallback_password);

    }

    void autoConnect(const char* fallback_ssid, const char* fallback_password, IPAddress ip , IPAddress gateway, IPAddress subnet) {
      WiFiManager wifiManager;
      wifiManager.setSTAStaticIPConfig(ip, gateway, subnet);
      wifiManager.autoConnect(fallback_ssid, fallback_password);
    }



};

_EzEsp8266 EzEsp8266;


