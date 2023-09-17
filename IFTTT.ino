#include <WiFiNINA.h>
#include <BH1750.h>
#include <Wire.h>

char ssid[] = "Lakshya's iPhone";// my personal hotspot's name
char pass[] = "987654321";// my personal hotspot's password

WiFiClient client;
BH1750 lightMeter;

char   HOST_NAME[] = "maker.ifttt.com";
String PATH_NAME  = "https://maker.ifttt.com/trigger/lightsensor/with/key/djmTxByajgaXmwohDns7rvPK_Nsk553vDqSaO1saWzK";
String queryString = "?value1=57&value2=25";

void setup() {
  Serial.begin(9600);
  Serial.print("BEGINNN...");
  while (!Serial);

     WiFi.begin(ssid, pass);
     Wire.begin();
while(true)
  {
  if (client.connect(HOST_NAME, 80)) {
    Serial.println("Connected!!r");
    break;
  }
  else {
    Serial.println("Can not connect!!");
    
  }
  delay(500);
}
lightMeter.begin();
Serial.println("Connected!!");
}
void loop() {
  Serial.print("BEGINNN...");
  float lux = lightMeter.readLightLevel();

  if (lux > 1000) {
    queryString = "?value1=" + String(lux) + "&value2=It's very bright!!";
  } else if (lux > 500) {
    queryString = "?value1=" + String(lux) + "&value2=It's bright!!";
  } else if (lux > 100) {
    queryString = "?value1=" + String(lux) + "&value2=It's average1!";
  } else if (lux > 10) {
    queryString = "?value1=" + String(lux) + "&value2=It's dark!!";
  } else {
    queryString = "?value1=" + String(lux) + "&value2=It's very dark!!";
  }

  Serial.println(queryString);

  if (lux > 500) {
    client.println("GET " + PATH_NAME + queryString + " HTTP/1.1");
    client.println("Host: " + String(HOST_NAME));
    client.println("Connection has been closed!!");
    client.println(); 

    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.print(c);
      }
    }
    client.stop();
    Serial.println();
    Serial.println("Disconnected!!");
  }
  
  queryString = "";
  delay(3000);
}
