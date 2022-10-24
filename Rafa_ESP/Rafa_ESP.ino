
#include "DHT.h"
#include <WiFiClientSecure.h>
#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#define DHTPIN 13   // Digital pin DI esp8266 nomor D7 tapi di code nomor 13 bacanya

// Uncomment whatever type you're using!
#define DHTTYPE DHT11   // DHT 11
// Connect pin 1 (on the left) of the sensor to +5V
// NOTE: If using a board with 3.3V logic like an Arduino Due connect pin 1
// to 3.3V instead of 5V!
// Connect pin 2 of the sensor to whatever your DHTPIN is
// Connect pin 4 (on the right) of the sensor to GROUND
// Connect a 10K resistor from pin 2 (data) to pin 1 (power) of the sensor

// Initialize DHT sensor.
// Note that older versions of this library took an optional third parameter to
// tweak the timings for faster processors.  This parameter is no longer needed
// as the current DHT reading algorithm adjusts itself to work on faster procs.
DHT dht(DHTPIN, DHTTYPE);
char ssid[] = "hamori";     //  your network SSID (name)
char pass[] = "rapaganteng";  // your network password
const char *ruangan = "1"; //Nomor ruangan / nama ruangan
const char *host = "http://192.168.152.234/rafa_sensor/node.php/"; //alamt web mengirim data / ip selalu berubah, cek dulu


void setup() {
 
 Serial.begin(9600);
 dht.begin();
 WiFi.mode(WIFI_OFF); 
 delay(1000);
 WiFi.mode(WIFI_STA); //WiFi Station Mode default mode is both station and acccess point modes
 
 WiFi.begin(ssid, pass); //connecting to router
 Serial.println("");
Serial.print("Connecting");
 // Wait for connection
 while (WiFi.status() != WL_CONNECTED) {
 delay(500);
 Serial.print(".");
 }
 Serial.println("");
 Serial.print("Connected to ");
 Serial.println(ssid);
}

void loop() {
  

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  

  // Check if any reads failed and exit early (to try again).
//  if (isnan(h) || isnan(t) || isnan(f)) {
//    Serial.println(F("Failed to read from DHT sensor!"));
//    return;
//  }

  float h = dht.readHumidity();
  float t = dht.readTemperature();

 Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print("\n");
  Serial.print(F("  Temperature: "));
  Serial.print(t);
  Serial.print(F("°C "));
  delay(2000);

  DynamicJsonDocument doc(2048);
  doc["Kelembaban"] = h;
  doc["Suhu"] = t;
  doc["ruang"] = ruangan;
  
  // Serialize JSON document
  String json;
  serializeJson(doc, json);
//  Serial.print(json);
  WiFiClient client;
  HTTPClient http;

  String posting;
  Serial.print("Mau ngirim data");
//  String json=json;
//posting = "names=" + names + "&age=" + age ;
  
  http.begin(client, host);//your PHP location
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  int httpCode = http.POST(json);   //Sending the request
  String payload = http.getString();    //Get the response payload
//Serial.println(httpCode);   //Print HTTP return code(200)
  Serial.println(payload);    //printing the respose from the submitted data
  http.end();  //Close connection
  
  delay(2000);//Looping delay 2Secs
}
