#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

//defined variables
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

void setup() {
  pinMode(BUILTIN_LED, OUTPUT);
  Serial.begin(9600);
  connectWifi(); 
}

void loop() {
  String a = motorStatus(2);

  if(a != "Error"){
    int b = a.toInt();
    if(b==0){
      digitalWrite(BUILTIN_LED, HIGH);
    }
    if(b==1){
      digitalWrite(BUILTIN_LED, LOW);
    }
  }
}
