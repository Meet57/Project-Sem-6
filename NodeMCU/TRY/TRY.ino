#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

//defined variables
const char * ssid = "Meet";
const char * password = "MeetMeet.";
String thumbprint = "94fcf6236c37d5e792783c0b5fad0ce49efd9ea8";
int status = 1;

void connectWifi() {
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("WiFi connected");
  Serial.println(WiFi.localIP());
}

String uploadData(int id,int lower,int upper,int motor){
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
  pinMode(BUILTIN_LED, OUTPUT);
  Serial.begin(9600);
  connectWifi();
}

void loop() {
  digitalWrite(BUILTIN_LED, status);
  if(status == 1){
    for(int i=1;i<=1000;i++){
      Serial.print(i);
      Serial.println(uploadData(i,50,50,1));
    }
    status = 0;
  }
}
