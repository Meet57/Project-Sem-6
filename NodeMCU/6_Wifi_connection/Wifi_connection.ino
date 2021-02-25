#include "ESP8266WiFi.h"


void connectWifi(){
  WiFi.begin("Meet","MeetMeet."); //wifi id password
  
  // while wifi not connected yet, print '.'
  // then after it connected, get out of the loop
  while (WiFi.status() != WL_CONNECTED) {
     delay(500);
     Serial.print(".");
  }
  //print a new line, then print WiFi connected and the IP address
  Serial.println("");
  Serial.println("WiFi connected");
  // Print the IP address
  Serial.println(WiFi.localIP());
}

void setup()
{ 
  Serial.begin(9600);
  connectWifi();

}
void loop() {
  
}
