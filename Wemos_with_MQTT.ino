/*
 * Dim - Relay Shield Toggle v1.0
 * Closes the relay for 100 ms, then opens based on OH2 event
 * Relay Shield transistor closes relay when D1 is HIGH
*/

#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include <Adafruit_MQTT.h>
#include <Adafruit_MQTT_Client.h>

/************************* WiFi Access Point *********************************/
#define WLAN_SSID       "<ssid>"			
#define WLAN_PASS       "<pass>"

/************************* MQTT Broker Setup *********************************/
#define mqtt_server      "<mqtt_broker>"
#define mqtt_serverport  1883                   // use 8883 for SSL
#define mqtt_username    "<mqtt_username>"
#define mqtt_password    "<mqtt_password>"

/************************* Constants, Variables, Integers, etc *********************************/
const int tubePin = D1;
const int bulbPin = D2;
const int fanPin = D3;

const long togDelay = 100;  // pause for 100 milliseconds before toggling to Open
const long postDelay = 200;  // pause for 200 milliseconds after toggling to Open
int value = 0;
int relayState = LOW;

// Create an ESP8266 WiFiClient class to connect to the MQTT server.
WiFiClient client;

// Setup the MQTT client class by passing in the WiFi client and MQTT server and login details.
Adafruit_MQTT_Client mqtt(&client, mqtt_server, mqtt_serverport, mqtt_username, mqtt_password);

// Setup subscription 'HomeAuto' for monitoring topic for changes.
Adafruit_MQTT_Subscribe HomeAuto = Adafruit_MQTT_Subscribe(&mqtt, "openhab/out/HomeAuto/command");

/*************************** Sketch Code ************************************/
void MQTT_connect();

void setup() {
  Serial.begin(115200);
  Serial.println(""); Serial.println(F("Booting... v1.0"));
  pinMode(relayPin, OUTPUT);
  // Connect to WiFi access point.
  Serial.print("Connecting to "); Serial.println(WLAN_SSID);
  WiFi.mode(WIFI_STA);
  WiFi.begin(WLAN_SSID, WLAN_PASS);
  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
  Serial.println("Connection Failed! Rebooting in 5 secs...");
  delay(5000);
  ESP.restart();
  }

  // Setup MQTT subscription for HomeAuto feed.
  mqtt.subscribe(&HomeAuto);

  // Begin OTA
  ArduinoOTA.setPort(8266); // Port defaults to 8266
  ArduinoOTA.setHostname("homeauto");   // Hostname defaults to esp8266-[ChipID]
  ArduinoOTA.setPassword((const char *)"<pass>");   // No authentication by default

  ArduinoOTA.onStart([]() {
    Serial.println("Start");
  });
  ArduinoOTA.onEnd([]() {
    Serial.println("\nEnd");
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
  });
  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
    else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
    else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
    else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
    else if (error == OTA_END_ERROR) Serial.println("End Failed");
  });
  ArduinoOTA.begin();
  Serial.println("");
  Serial.println("Ready & WiFi connected");
  Serial.print("IP address: "); Serial.println(WiFi.localIP());
}

void loop() {
  ArduinoOTA.handle();
  // Ensure the connection to the MQTT server is alive (this will make the first
  // connection and automatically reconnect when disconnected).  See the MQTT_connect
  // function definition further below.
  MQTT_connect();
  
  // this is our 'wait for incoming subscription packets' busy subloop
  // try to spend your time here

  Adafruit_MQTT_Subscribe *subscription;
  while ((subscription = mqtt.readSubscription(5000))) {
    if (subscription == &HomeAuto) {
      Serial.print(F("Got: ")); Serial.println((char *)HomeAuto.lastread);
      // close the relay for 100 ms
      Serial.println("Close Relay for 100 ms & then Open");
      
      
      //digitalWrite(relayPin, HIGH);
      //delay(togDelay);
      //digitalWrite(relayPin, LOW);
      //delay(postDelay);
      
  
  //Match the request for TUBE
  
  value = LOW;
  if (request.indexOf("/TUBE=ON") != -1) {
    digitalWrite(tubePin, HIGH);
    value = HIGH;
  } 
  if (request.indexOf("/TUBE=OFF") != -1){
    digitalWrite(tubePin, LOW);
    value = LOW;
  }
  
  
  //Match the request for BULB
  
   value = LOW;
  if (request.indexOf("/BULB=ON") != -1) {
    digitalWrite(bulbPin, HIGH);
    value = HIGH;
  } 
  if (request.indexOf("/BULB=OFF") != -1){
    digitalWrite(bulbPin, LOW);
    value = LOW;
  }
      
      
      
   //Match the request for FAN
      
      int value = LOW;
  if (request.indexOf("/FAN=ON") != -1) {
    digitalWrite(fanPin, HIGH);
    value = HIGH;
  } 
  if (request.indexOf("/FAN=OFF") != -1){
    digitalWrite(fanPin, LOW);
    value = LOW;
  }   
         
    }
  }

  // ping the server to keep the mqtt connection alive
  // NOT required if you are publishing once every KEEPALIVE seconds
//   if(! mqtt.ping()) {
//    mqtt.disconnect();
//  }
}

// Function to connect and reconnect as necessary to the MQTT server.
// Should be called in the loop function and it will take care if connecting.
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
