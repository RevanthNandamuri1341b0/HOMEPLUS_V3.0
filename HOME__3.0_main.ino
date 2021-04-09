int device1 = 5;
int device2 = 4;
int device3 = 0;
int device4 = 2;
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ArduinoJson.h> 
#include <StreamString.h>
#include <WebSocketsClient.h>
ESP8266WiFiMulti WiFiMulti;
WebSocketsClient webSocket;
WiFiClient client;

#define MyApiKey "" // TODO: Change to your sinric API Key. Your API Key is displayed on sinric.com dashboard
#define MySSID "" // YOUR WIFI
#define MyWifiPassword "" // TODO: Change to your Wifi network password

#define HEARTBEAT_INTERVAL 300000   // 5 Minutes

uint64_t heartbeatTimestamp = 0;
bool isConnected = false;

void setPowerStateOnServer(String deviceId, String value);
void setTargetTemperatureOnServer(String deviceId, String value, String scale);

// TODO:deviceId is the ID assgined to your smart-home-device in sinric.com dashboard.
// TODO:Copy it from dashboard and paste it below according.

string dID1="";//Device ID1
string dID2="";//Device ID2
string dID3="";//Device ID3
string dID4="";//Device ID4

void turnOn(String deviceId) {
 if (deviceId == dID1)  // Device1 ID
 { 
 Serial.print("Turn on device id: ");
 Serial.println(deviceId);
 digitalWrite(device1, HIGH);
 } 
 else if (deviceId == dID2) // Device2 ID
 { 
 Serial.print("Turn on device id: ");
 Serial.println(deviceId);
 digitalWrite(device2, HIGH);
 }
 else if (deviceId == dID3) // Device3 ID 
 { 
 Serial.print("Turn on device id: ");
 Serial.println(deviceId);
 digitalWrite(device3, HIGH);
 } 
 else if (deviceId == dID4) // Device4 ID
 { 
 Serial.print("Turn on device id: ");
 Serial.println(deviceId);
 digitalWrite(device4, HIGH);
 }
 else 
 {
 Serial.print("Turn on for unknown device id: ");
 Serial.println(deviceId); 
 } 
}

void turnOff(String deviceId) {
 if (deviceId == dID1)
 { 
 Serial.print("Turn off Device ID: ");
 Serial.println(deviceId);
 digitalWrite(device1, LOW);
 }
 else if (deviceId == dID2) 
 { 
 Serial.print("Turn off Device ID: ");
 Serial.println(deviceId);
 digitalWrite(device2, LOW);
 }
 else if (deviceId == dID3) 
 { 
 Serial.print("Turn off Device ID: ");
 Serial.println(deviceId);
 digitalWrite(device3, LOW);
 }
 else if (deviceId == dID4) 
 { 
 Serial.print("Turn off Device ID: ");
 Serial.println(deviceId);
 digitalWrite(device4, LOW);
 }
 else 
 {
 Serial.print("Turn off for unknown device id: ");
 Serial.println(deviceId); 
 }
}

void webSocketEvent(WStype_t type, uint8_t * payload, size_t length) {
 switch(type) {
 case WStype_DISCONNECTED:
 isConnected = false; 
 Serial.printf("[WSc] Webservice disconnected from sinric.com!\n");
 break;
 case WStype_CONNECTED: {
 isConnected = true;
 Serial.printf("[WSc] Service connected to sinric.com at url: %s\n", payload);
 Serial.printf("Waiting for commands from sinric.com ...\n"); 
 }
 break;
 case WStype_TEXT: {
 Serial.printf("[WSc] get text: %s\n", payload);
 
 DynamicJsonBuffer jsonBuffer; // load version 5 from IDE libraries
 JsonObject& json = jsonBuffer.parseObject((char*)payload); 
 String deviceId = json ["deviceId"]; 
 String action = json ["action"];
 
 if(action == "setPowerState") { // Switch or Light
 String value = json ["value"];
 if(value == "ON") {
 turnOn(deviceId);
 } else {
 turnOff(deviceId);
 }
 }
 else if (action == "SetTargetTemperature") {
 String deviceId = json ["deviceId"]; 
 String action = json ["action"];
 String value = json ["value"];
 }
 else if (action == "test") {
 Serial.println("[WSc] received test command from sinric.com");
 }
 }
 break;
 case WStype_BIN:
 Serial.printf("[WSc] get binary length: %u\n", length);
 break;
 }
}

void setup() 
{
 pinMode (device1, OUTPUT);
 pinMode (device2, OUTPUT);
 pinMode (device3, OUTPUT);
 pinMode (device4, OUTPUT);




Serial.begin(115200);
 
 WiFiMulti.addAP(MySSID, MyWifiPassword);
 Serial.println();
 Serial.print("Connecting to Wifi: ");
 Serial.println(MySSID);

// Waiting for Wifi connect
 while(WiFiMulti.run() != WL_CONNECTED) {
 delay(500);
 Serial.print(".");
 }
 if(WiFiMulti.run() == WL_CONNECTED) {
 Serial.println("");
 Serial.print("WiFi connected. ");
 Serial.print("IP address: ");
 Serial.println(WiFi.localIP());
 }

 webSocket.begin("iot.sinric.com", 80, "/");


 webSocket.onEvent(webSocketEvent);     
 webSocket.setAuthorization("apikey", MyApiKey);
 
 
 webSocket.setReconnectInterval(5000); // tries again every 5s if connection has failed
}

void loop() {
 
 webSocket.loop();
 
 if(isConnected) {
 uint64_t now = millis();
 
 if((now - heartbeatTimestamp) > HEARTBEAT_INTERVAL) {
 heartbeatTimestamp = now;
 webSocket.sendTXT("H"); 
 }
 } 
}


void setPowerStateOnServer(String deviceId, String value) {
 DynamicJsonBuffer jsonBuffer;
 JsonObject& root = jsonBuffer.createObject();
 root["deviceId"] = deviceId;
 root["action"] = "setPowerState";
 root["value"] = value;
 StreamString databuf;
 root.printTo(databuf);
 
 webSocket.sendTXT(databuf);
}

void setTargetTemperatureOnServer(String deviceId, String value, String scale) {
 DynamicJsonBuffer jsonBuffer;
 JsonObject& root = jsonBuffer.createObject();
 root["action"] = "SetTargetTemperature";
 root["deviceId"] = deviceId;
 
 JsonObject& valueObj = root.createNestedObject("value");
 JsonObject& targetSetpoint = valueObj.createNestedObject("targetSetpoint");
 targetSetpoint["value"] = value;
 targetSetpoint["scale"] = scale;
 
 StreamString databuf;
 root.printTo(databuf);
 
 webSocket.sendTXT(databuf);
}
