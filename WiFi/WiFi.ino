#include <Adafruit_CC3000.h>
#include <SoftwareSerial.h>
#include <ccspi.h>
#include <SPI.h>
#include "utility/debug.h"

#define CC3000_TINY_DRIVER
// These are the interrupt and control pins
#define ADAFRUIT_CC3000_IRQ   3  // MUST be an interrupt pin!
// These can be any two pins
#define ADAFRUIT_CC3000_VBAT  5
#define ADAFRUIT_CC3000_CS    10
// Use hardware SPI for the remaining pins
// On an UNO, SCK = 13, MISO = 12, and MOSI = 11
Adafruit_CC3000 cc3000 = Adafruit_CC3000(ADAFRUIT_CC3000_CS, ADAFRUIT_CC3000_IRQ, ADAFRUIT_CC3000_VBAT, SPI_CLOCK_DIV2);

#define WLAN_SSID       "arduino"           // cannot be longer than 32 characters!
#define WLAN_PASS       "testing123"
// Security can be WLAN_SEC_UNSEC, WLAN_SEC_WEP, WLAN_SEC_WPA or WLAN_SEC_WPA2
#define WLAN_SECURITY   WLAN_SEC_WPA2

#define LISTEN_PORT           7    // What TCP port to listen on for connections.  The echo protocol uses port 7.

Adafruit_CC3000_Server echoServer(LISTEN_PORT);

#define rxPin 4  // rxPin is immaterial - not used - just make this an unused Arduino pin number
#define txPin 14 // pin 14 is analog pin 0, on a BBB just use a servo cable :), see Reference pinMode
SoftwareSerial mySerial =  SoftwareSerial(rxPin, txPin);

void setup(void)
{
  pinMode(txPin, OUTPUT);
   mySerial.begin(9600);      // 9600 baud is chip comm speed

   mySerial.print("?G420");   // set display geometry,  2 x 16 characters in this case
   delay(500);                // pause to allow LCD EEPROM to program

   mySerial.print("?B77");    // set backlight to ff hex, maximum brightness
   delay(1000);                // pause to allow LCD EEPROM to program

   mySerial.print("?s6");     // set tabs to six spaces
   delay(1000);               // pause to allow LCD EEPROM to program
   
    mySerial.print("?D00000000000000000");       // define special characters
   delay(300);                                  // delay to allow write to EEPROM
                                                // see moderndevice.com for a handy custom char generator (software app)
   mySerial.print("?f");                   // clear the LCD
   delay(10);                                              
   mySerial.print("...");   
                                                
                                                
   //crashes LCD without delay
   mySerial.print("?D11010101010101010");
   delay(300);

   mySerial.print("?D21818181818181818");
   delay(300);

   mySerial.print("?D31c1c1c1c1c1c1c1c");
   delay(300);

   mySerial.print("?D41e1e1e1e1e1e1e1e");
   delay(300);

   mySerial.print("?D51f1f1f1f1f1f1f1f");
   delay(300);

   mySerial.print("?D60000000000040E1F");
   delay(300);

   mySerial.print("?D70000000103070F1F");
   delay(300);

   mySerial.print("?c0");                  // turn cursor off
   delay(300);
   
   mySerial.print("?f");                   // clear the LCD

   delay(1000);

   mySerial.print("?f");                   // clear the LCD
   delay(100);
   delay(3000);

   mySerial.print("?x00?y0");              // cursor to first character of line 0

  mySerial.print(F("Hello, CC3000!\n")); 
  
  delay(1000);
  mySerial.print("?f");                   // clear the LCD
  mySerial.print("?x00?y0");              // cursor to first character of line 0
  mySerial.print("Free RAM: "); mySerial.println(getFreeRam(), DEC);
  
  delay(1000);
  mySerial.print("?f");                   // clear the LCD
  mySerial.print("?x00?y0");              // cursor to first character of line 0
  mySerial.print("Initializing...");
  
  /* Initialise the module */
  if (!cc3000.begin())
  {
    mySerial.print("?x00?y1");           // locate cursor to beginning of line 1
    mySerial.print("Couldn't begin()! Check your wiring?");
    while(1);
  }
  
  mySerial.print("?x00?y1");              // cursor to first character of line 0
  mySerial.print("Connecting...");
  
  if (!cc3000.connectToAP(WLAN_SSID, WLAN_PASS, WLAN_SECURITY)) {
    mySerial.print("?x00?y1");           // locate cursor to beginning of line 1
    mySerial.print("Failed!");
    while(1);
  }
  
  mySerial.print("?x00?y2");              // cursor to first character of line 2
  mySerial.print("Connected!");
  
  delay(1000);
  mySerial.print("?f");                   // clear the LCD
  mySerial.print("?x00?y0");              // cursor to first character of line 0
  
  mySerial.print("Request DHCP");
  while (!cc3000.checkDHCP())
  {
    delay(100); // ToDo: Insert a DHCP timeout!
  }
  
  delay(1000);
  mySerial.print("?f");                   // clear the LCD
  mySerial.print("?x00?y0");              // cursor to first character of line 0

  /* Display the IP address DNS, Gateway, etc. */  
  while (! displayConnectionDetails()) {
    delay(1000);
  }
  
  // Start listening for connections
  echoServer.begin();
  
  delay(3000);
  mySerial.print("?f");                   // clear the LCD
  mySerial.print("?x00?y0");              // cursor to first character of line 0
  
  mySerial.print("Listening...");
}

void loop(void)
{
  // Try to get a client which is connected.
  Adafruit_CC3000_ClientRef client = echoServer.available();
  if (client) {
     // Check if there is data available to read.
     if (client.available() > 0) {
       // Read a byte and write it to all clients.
       uint8_t ch = client.read();
       mySerial.print((char) ch);
       client.write(ch);
     }
  }
}

/**************************************************************************/
/*!
    @brief  Tries to read the IP address and other connection details
*/
/**************************************************************************/
bool displayConnectionDetails(void)
{
  uint32_t ipAddress, netmask, gateway, dhcpserv, dnsserv;
  
  mySerial.print("?f");                   // clear the LCD
  mySerial.print("?x00?y0");              // cursor to first character of line 0
  
  if(!cc3000.getIPAddress(&ipAddress, &netmask, &gateway, &dhcpserv, &dnsserv))
  {
    mySerial.print("Unable to retrieve the IP Address!");
    return false;
  }
  else
  {
    mySerial.print("IP: "); printIPdots(ipAddress);
    mySerial.print("?x00?y1");              // cursor to first character of line 1
    mySerial.print("GW: "); printIPdots(gateway);
    mySerial.print("?x00?y2");              // cursor to first character of line 2
    mySerial.print("DHCP: "); printIPdots(dhcpserv);
    mySerial.print("?x00?y3");              // cursor to first character of line 3
    mySerial.print("DNS: "); printIPdots(dnsserv);
    return true;
  }
}

void printIPdots(uint32_t ip) {
  mySerial.print((uint8_t)(ip >> 24));
  mySerial.print('.');
  mySerial.print((uint8_t)(ip >> 16));
  mySerial.print('.');
  mySerial.print((uint8_t)(ip >> 8));
  mySerial.print('.');
  mySerial.print((uint8_t)(ip)); 
}
