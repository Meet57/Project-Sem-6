#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

const char * ssid = "Meet";
const char * password = "MeetMeet.";
String thumbprint = "94fcf6236c37d5e792783c0b5fad0ce49efd9ea8";

void connectWifi() {
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("WiFi connected");
  Serial.println(WiFi.localIP());
}

String getResponseString(String URL){
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(URL,thumbprint);
    int httpCode = http.GET();
    String payload = http.getString();
    http.end();
    return payload;
  }
  return "Error";
}

String motorStatus(int id){
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    String URL = "https://smartwaterpump.herokuapp.com/motor/";
    http.begin(URL+id,thumbprint);
    int httpCode = http.GET();
    String payload = http.getString();
    http.end();
    return payload;
  }
  return "Error";
}

String uploadData(int id,int lower,int upper,String motor){
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    String URL = "https://smartwaterpump.herokuapp.com/add/";
    String a = "&";
    URL = URL+id+a+upper+a+lower+a+motor;
    http.begin(URL,thumbprint);
    int httpCode = http.GET();
    String payload = http.getString();
    http.end();
    return payload;
  }
  return "Error";
}

void setup() {
  Serial.begin(9600);
  connectWifi();
}

void loop() {
//  String res = getResponseString("https://smartwaterpump.herokuapp.com/read/1");
  Serial.println(uploadData(10,90,10,"HIGH"));
  delay(100000);
}
