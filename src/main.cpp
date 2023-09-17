/****************************************
 * Include Libraries
 ****************************************/
#include <WiFi.h>
#include <WiFiUdp.h>
#include <OSCBundle.h>

#define WIFISSID "zynd.at" // Put your Wifi SSID here
#define PASSWORD "" // Put your WIFI password here
//it should be a random and unique ascii string and different from all other devices

#define SENSOR A0 // Set the A0 as SENSOR

WiFiUDP Udp;

const IPAddress outIp(10,13,42,206);        // remote IP of your computer
const unsigned int outPort = 5005;

void setup() {
  Serial.begin(115200);
  WiFi.begin(WIFISSID, PASSWORD);
  // Assign the pin as INPUT
  pinMode(SENSOR, INPUT);

  Serial.println();
  Serial.print("Waiting for WiFi...");

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println("");
  Serial.println("WiFi Connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

unsigned long last_us = 0L;

void loop() {
  if (micros() - last_us > 1000) {
    last_us += 1000;
    float sensor = analogRead(SENSOR);

    OSCMessage msg("/test");
    msg.add(sensor);
    Udp.beginPacket(outIp, outPort);
    msg.send(Udp);
    Udp.endPacket();
    msg.empty();
  }
}
