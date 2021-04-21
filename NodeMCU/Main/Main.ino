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

void loop(){
  int mode = getResponseString("https://smartwaterpump.herokuapp.com/mode/1").toInt();
  int motor = getResponseString("https://smartwaterpump.herokuapp.com/motor/1").toInt();
  int tank1 = random(0,100);
  int tank2 = random(0,100);
  
  if(mode == 0){
    
    Serial.println("---Auto---");
    if(tank1 > 95 || tank2 < 20){
      motor = 0;
      digitalWrite(BUILTIN_LED,HIGH);
    }
    if(tank1 < 30 && tank2 >20){
      motor = 1;
      digitalWrite(BUILTIN_LED,LOW);
    }

    uploadData(1,tank1,tank2,motor);
    
  }else{
    Serial.println("---Manual---");

    if(tank1 > 98){
      motor = 0;
    }
    if(tank2 < 5){
      motor = 0;
    }

    uploadData(1,tank1,tank2,motor);

    if(motor == 1){
      digitalWrite(BUILTIN_LED,LOW);
    }else{
      digitalWrite(BUILTIN_LED,HIGH);
    }
    
  }
}
