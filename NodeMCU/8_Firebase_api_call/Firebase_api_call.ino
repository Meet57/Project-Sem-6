#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

const char * ssid = "Meet";
const char * password = "MeetMeet.";
String thumbprint = "94fcf6236c37d5e792783c0b5fad0ce49efd9ea8";
//Website SSL security certificates provide the site's Public cryptographic key 
//which is the public side of the server's secret Private cryptographic key which is never publicly disclosed.

void setup() {

  Serial.begin(9600);

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

    HTTPClient http; //Declare an object of class HTTPClient

    String url = "https://smartwaterpump.herokuapp.com/read/1";
    http.begin(url,thumbprint); //Specify request destination
    
    int httpCode = http.GET(); //Send the request
    String payload = http.getString(); //Get the request response payload
      
    Serial.println(payload); //Print the response payload
    Serial.println(httpCode); //Print the response payload

    

    http.end(); //Close connection
  }

  delay(10000); //Send a request every 30 seconds
}
