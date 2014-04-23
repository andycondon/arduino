#include <Adafruit_CC3000.h>
#include <SPI.h>

#define WLAN_SSID     "arduino"      // cannot be longer than 32 characters!
#define WLAN_PASS     "testing123"   // cannot be longer than 32 characters!
#define WLAN_SECURITY WLAN_SEC_WPA2  // Security can be WLAN_SEC_UNSEC, WLAN_SEC_WEP, WLAN_SEC_WPA or WLAN_SEC_WPA2

#define CC3000_TINY_DRIVER
// These are the interrupt and control pins
#define ADAFRUIT_CC3000_IRQ   3  // MUST be an interrupt pin!
// These can be any two pins
#define ADAFRUIT_CC3000_VBAT  5
#define ADAFRUIT_CC3000_CS    10
// Use hardware SPI for the remaining pins
// On an UNO, SCK = 13, MISO = 12, and MOSI = 11

Adafruit_CC3000 cc3000 = Adafruit_CC3000(ADAFRUIT_CC3000_CS, ADAFRUIT_CC3000_IRQ, ADAFRUIT_CC3000_VBAT, SPI_CLOCK_DIV2);

#define LISTEN_PORT           7    // What TCP port to listen on for connections.  The echo protocol uses port 7.

Adafruit_CC3000_Server echoServer(LISTEN_PORT);

void wifi_init()
{
  lcd_clear();
  lcd_cursor("0", "00");
  lcd_print("WiFi Initializing...");
  
  /* Initialise the module */
  if (!cc3000.begin())
  {
    lcd_cursor("1", "00");
    lcd_print("Couldn't begin()! Check your wiring?");
    while(1);
  }
  
  lcd_cursor("1", "00");
  lcd_print("Connecting...");
  if (!cc3000.connectToAP(WLAN_SSID, WLAN_PASS, WLAN_SECURITY)) {
    lcd_cursor("1", "00");
    lcd_print("Failed!");
    while(1);
  }
  
  lcd_cursor("2", "00");
  lcd_print("Request DHCP");
  while (!cc3000.checkDHCP())
  {
    delay(100); // ToDo: Insert a DHCP timeout!
  }
}

bool displayConnectionDetails(void)
{
  uint32_t ipAddress, netmask, gateway, dhcpserv, dnsserv;
  
  lcd_clear();
  lcd_cursor("0", "00");
  
  if(!cc3000.getIPAddress(&ipAddress, &netmask, &gateway, &dhcpserv, &dnsserv))
  {
    lcd_print("Unable to retrieve the IP Address!");
    return false;
  }
  else
  {
    lcd_print("IP: "); printIPdots(ipAddress);
    lcd_cursor("1", "00");
    lcd_print("GW: "); printIPdots(gateway);
    lcd_cursor("2", "00");
    lcd_print("DHCP: "); printIPdots(dhcpserv);
    lcd_cursor("3", "00");
    lcd_print("DNS: "); printIPdots(dnsserv);
    return true;
  }
}

void printIPdots(uint32_t ip) {
  lcd_print((uint8_t)(ip >> 24));
  lcd_print('.');
  lcd_print((uint8_t)(ip >> 16));
  lcd_print('.');
  lcd_print((uint8_t)(ip >> 8));
  lcd_print('.');
  lcd_print((uint8_t)(ip)); 
}
