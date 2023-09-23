#include <WiFiNINA.h>
#include <BH1750.h>
#include <Wire.h>

const char* ssid = "Lakshya's iPhone";//My personal hotspot's name
const char* password = "987654321";//My personal hotspot's password
WiFiClient client;
BH1750 lightMeter;

const char* hostName = "maker.ifttt.com";
const String pathName = "/trigger/light/with/key/ncAdrrKTO4VozWBpz8Cd5fk0QQ2r7HlBoIF2yj9xdN_";//MY pathway of IFTTT webhook 
String queryString = "?value1=57&value2=25";

void setup() {
  Serial.begin(9600);
  WiFi.begin(ssid, password);
  Wire.begin();

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi...");
  }

  if (client.connect(hostName, 80)) {
    Serial.println("Connected to host!");
  } else {
    Serial.println("Failed to connect to host.");
  }

  lightMeter.begin();
  Serial.println("BH1750 sensor initialized.");
}

void loop() {
  Serial.print("Working On It...");
  float lux = lightMeter.readLightLevel();

  queryString = "?value1=" + String(lux);
  Serial.println(queryString);

  if (lux > 500) {
    client.print("GET " + pathName + queryString + " HTTP/1.1\r\n");
    client.print("Host: " + String(hostName) + "\r\n");
    client.print("Connection: close\r\n\r\n");
    client.flush();

    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.print(c);
      }
    }

    client.stop();
    Serial.println();
    Serial.println("Disconnected from host.");
  }

  queryString = "";
  delay(3000);
}
