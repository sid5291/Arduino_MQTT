#include <WiFi.h>
#include "PubSubClient.h"

// Update these with values suitable for your network.
byte mac[] = { 0xDE, 0xED, 0xBA, 0xFE, 0xFE, 0xED };

char ssid[] = "ncsu"; // your network SSID (name)
char topic[] = "hello/world";
int status = WL_IDLE_STATUS; // the Wifi radio's status

void callback(char* topic, byte* payload, unsigned int length) {
// handle message arrived
}

WiFiClient wfClient;
PubSubClient client("m10.cloudmqtt.com", 16430, callback, wfClient);

void setup()
{
  
Serial.begin(9600);

if (WiFi.status() == WL_NO_SHIELD) 
{
  Serial.println("WiFi shield not present");
  while(true);
}

while ( status != WL_CONNECTED) 
{
  Serial.print("Attempting to connect to WPA SSID: ");
  Serial.println(ssid);
  status = WiFi.begin(ssid);
  delay(10000);
}

Serial.println("You're connected to the network");
  printWifiData();
  printCurrentNet();
}

void loop()
{
  if (!client.connected())
  {
    delay(1000);
    Serial.println("Connecting to Mosquitto");
    if (client.connect("ArduinoClient","giprtpyb","XfWBpKOq3FG2")) 
    {
      client.publish(topic,"Connected to Mosquitto");
      Serial.println("Connected to Mosquitto");
    }
  } 
  else 
  {
    client.publish(topic,"Hello");
  }
client.loop();
}

void printWifiData() {
IPAddress ip = WiFi.localIP();
Serial.print("IP Address: ");
Serial.println(ip);
byte mac[6];
WiFi.macAddress(mac);
Serial.print("MAC address: ");
Serial.print(mac[5],HEX);
Serial.print(":");
Serial.print(mac[4],HEX);
Serial.print(":");
Serial.print(mac[3],HEX);
Serial.print(":");
Serial.print(mac[2],HEX);
Serial.print(":");
Serial.print(mac[1],HEX);
Serial.print(":");
Serial.println(mac[0],HEX);
}

void printCurrentNet() {
Serial.print("SSID: ");
Serial.println(WiFi.SSID());
byte bssid[6];
WiFi.BSSID(bssid);
Serial.print("BSSID: ");
Serial.print(bssid[5],HEX);
Serial.print(":");
Serial.print(bssid[4],HEX);
Serial.print(":");
Serial.print(bssid[3],HEX);
Serial.print(":");
Serial.print(bssid[2],HEX);
Serial.print(":");
Serial.print(bssid[1],HEX);
Serial.print(":");
Serial.println(bssid[0],HEX);
long rssi = WiFi.RSSI();
Serial.print("signal strength (RSSI):");
Serial.println(rssi);
byte encryption = WiFi.encryptionType();
Serial.print("Encryption Type:");
Serial.println(encryption,HEX);
}
