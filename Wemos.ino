//http://www.esp8266learning.com/wemos-webserver-example.php



#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>

const char* ssid = "name of your wifi network";             //!!!!!!!!modify this
const char* password = "password of your wifi network";                //!!!!!!!!modify this
 
int fanPin = D2;
int lightPin = D3;
int bulbPin = D4;

WiFiServer server(80);
 
void setup() {
  Serial.begin(115200);
  delay(10);
 
  pinMode(fanPin, OUTPUT);
  pinMode(lightPin, OUTPUT);
  pinMode(bulbPin, OUTPUT);
  
  
  digitalWrite(fanPin, LOW);
  digitalWrite(lightPin, LOW);
  digitalWrite(bulbPin, LOW);
  
 
  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
 
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
 
  // Start the server
  server.begin();
  Serial.println("Server started");
 
  // Print the IP address
  Serial.print("Use this URL : ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
}

 
void loop() {

   
   
   MQTT_connect();
   
   
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
 
  // Wait until the client sends some data
  Serial.println("new client");
  while(!client.available()){
    delay(1);
  }
 
  // Read the first line of the request
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();
 
  // Match the request
 
  int value = LOW;
  if (request.indexOf("/FAN=ON") != -1) {
    digitalWrite(fanPin, HIGH);
    value = HIGH;
  } 
  if (request.indexOf("/FAN=OFF") != -1){
    digitalWrite(fanPin, LOW);
    value = LOW;
  }
  
  
  value = LOW;
  if (request.indexOf("/LIGHT=ON") != -1) {
    digitalWrite(lightPin, HIGH);
    value = HIGH;
  } 
  if (request.indexOf("/LIGHT=OFF") != -1){
    digitalWrite(lightPin, LOW);
    value = LOW;
  }
  
   value = LOW;
  if (request.indexOf("/BULB=ON") != -1) {
    digitalWrite(bulbPin, HIGH);
    value = HIGH;
  } 
  if (request.indexOf("/BULB=OFF") != -1){
    digitalWrite(bulbPin, LOW);
    value = LOW;
  }
  
   
 
  // Return the response
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  do not forget this one
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
 
  
  
  client.print("Fan pin is now: ");
 
  if(value == HIGH) {
    client.print("On");  
  } else {
    client.print("Off");
  }
  client.println("<br><br>");
  client.println("Click <a href=\"/FAN=ON\">here</a> turn the FAN on pin 1 ON<br>");
  client.println("Click <a href=\"/FAN=OFF\">here</a> turn the FAN on pin 1 OFF<br>");
  
  client.println("<br><br>");
  
  
  
  client.print("Light pin is now: ");
 
  if(value == HIGH) {
    client.print("On");  
  } else {
    client.print("Off");
  }
  client.println("<br><br>");
  client.println("Click <a href=\"/LIGHT=ON\">here</a> turn the LIGHT on pin 3 ON<br>");
  client.println("Click <a href=\"/LIGHT=OFF\">here</a> turn the LIGHT on pin 3 OFF<br>");
  
  client.println("<br><br>");
  
  
  
  
  client.print("Bulb pin is now: ");
 
  if(value == HIGH) {
    client.print("On");  
  } else {
    client.print("Off");
  }
  client.println("<br><br>");
  client.println("Click <a href=\"/BULB=ON\">here</a> turn the BULB on pin 2 ON<br>");
  client.println("Click <a href=\"/BULB=OFF\">here</a> turn the BULB on pin 2 OFF<br>");

  
  client.println("</html>");
 
  delay(1);
  Serial.println("Client disconnected");
  Serial.println("");
 
}




void MQTT_connect() {
  int8_t ret;

  // Stop if already connected.
  if (mqtt.connected()) {
    return;
  }
  
  Serial.print("Connecting to MQTT... ");
  
  uint8_t retries = 3;
  while ((ret = mqtt.connect()) != 0) { // connect will return 0 for connected
       Serial.println(mqtt.connectErrorString(ret));
       Serial.println("Retrying MQTT connection in 5 seconds...");
       mqtt.disconnect();
       delay(5000);  // wait 5 seconds
       retries--;
       if (retries == 0) {
         // basically die and wait for WDT to reset me
         while (1);
       }
  }
  Serial.println("MQTT Connected!");
}

