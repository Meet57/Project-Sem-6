#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
 
const char* ssid = "Meet";
const char* password = "MeetMeet.";
 
void setup () {
 
  Serial.begin(115200);
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
 
    delay(1000);
    Serial.print(".");
 
  }
  Serial.println("WiFi connected");
  // Print the IP address
  Serial.println(WiFi.localIP());
}
 
void loop() {
 
  if (WiFi.status() == WL_CONNECTED) { //Check WiFi connection status
 
    HTTPClient http;  //Declare an object of class HTTPClient

    for(int i=1;i<1000;i++){
      String url = "http://jsonplaceholder.typicode.com/posts/";
      Serial.println(url+i);
      http.begin(url+i);  //Specify request destination
      int httpCode = http.GET();                                  //Send the request
   
      if (httpCode > 0) { //Check the returning code
   
        String payload = http.getString();   //Get the request response payload
        Serial.println(payload);             //Print the response payload
   
      }
   
      http.end();   //Close connection
      delay(1000);
    }
  }
 
  delay(30000);    //Send a request every 30 seconds
}
