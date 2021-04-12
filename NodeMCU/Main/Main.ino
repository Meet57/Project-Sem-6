#define TankBase 60
#define TankTop 5

#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

//defined variables
const char * ssid = "Meet";
const char * password = "MeetMeet.";
int id = 1;
String thumbprint = "94fcf6236c37d5e792783c0b5fad0ce49efd9ea8";

//Undefined varibales
long duration;
long distance;

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

int UltrasonicLength(int tri,int echo){
  digitalWrite(tri, LOW);
  delayMicroseconds(2);

  digitalWrite(tri, HIGH);
  delayMicroseconds(10);
  digitalWrite(tri, LOW);

  duration = pulseIn(echo, HIGH);

  distance = duration * 0.034 / 2;
  
  if(distance <= TankTop){
    return 100;
  }

  if(distance >= TankBase){
    return 0;
  }

  return 100 - ((distance-TankTop)*100)/(TankBase-TankTop);
}

void setup() {
  pinMode(D4, OUTPUT); 
  pinMode(D5, INPUT); 
  
  Serial.begin(9600);
  connectWifi();
}

void loop() {
  Serial.println("LOOP STARTED");
  distance = UltrasonicLength(D4,D5);
  Serial.println(distance);
  
  String motor;

  if(distance < 20){
    motor = "HIGH";
  }else{
//    motor = motorStatus(1);
    if(distance > 90){
      motor = "LOW";
    }
  }
  
  String res = uploadData(id,10,distance,motor);
  Serial.println(res);

  Serial.println("LOOP END");
  delay(100);
}
