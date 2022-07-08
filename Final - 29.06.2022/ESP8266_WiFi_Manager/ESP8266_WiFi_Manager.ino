#include <Arduino.h>
//#include <DNSServer.h>
#include <ESP8266WiFi.h>
//#include <WiFiManager.h> // https://github.com/tzapu/WiFiManager
#include <ESPAsyncWebServer.h>
#include <ESPAsyncTCP.h>
#include "LittleFS.h"

//DNSServer dnsServer;
// Create AsyncWebServer object on port 80
AsyncWebServer server(80);

// Search for parameter in HTTP POST request
const char* WifiSSID = "pnlWifi-ssid";
const char* WifiPass = "pnlWifi-password";
//const char* PARAM_INPUT_3 = "ip";
//const char* PARAM_INPUT_4 = "gateway";
//const char* PARAM_INPUT_5 = "pnlWifi-data";
const char* LoRa = "lora";
const char* Valve_Position = "pnlAdvance-valvePosition";
const char* Communication_Failure = "pnlAdvanced-communicationfail";
const char* Pre_alarm_delay = "pnlAdvanced-prealarmdelay";
const char* Exit_delay = "pnlAdvanced-exitdelay";
const char* Infrared_delay = "pnlAdvanced-infrareddelay";
const char* Low_Temp_Control = "off";
const char* Maximum_flow_time = "pnlAdvanced-maxflowtime";
const char* Flow_Alarm = "flowAlarm";
const char* Flow_Type = "pnlAdvance-flowtype";
const char* Flow_Meter = "pnlAdvance-flowmeter";
const char* LoRa_Channel = "pnlLoRa-channel";
const char* LoRa_ID = "pnlLoRa-ID";
const char* LoRa_Power = "pnlLoRa-power";
const char* zone_ZoneNo = "zone_ZoneNo";


//Variables to save values from HTML form
String ssid;
String pass;
//String ip;
//String gateway;
String data[10];
String TestAP;

// File paths to save input values permanently
const char* ssidPath = "/ssid.txt";
const char* passPath = "/pass.txt";
//const char* ipPath = "/ip.txt";
//const char* gatewayPath = "/gateway.txt";

IPAddress localIP;
//IPAddress localIP(192, 168, 1, 200); // hardcoded

// Set your Gateway IP address
IPAddress localGateway;
//IPAddress localGateway(192, 168, 1, 1); //hardcoded
IPAddress subnet(255, 255, 0, 0);

// Timer variables
unsigned long previousMillis = 0;
const long interval = 10000;  // interval to wait for Wi-Fi connection (milliseconds)

// Set LED GPIO
const int ledPin = 2;
// Stores LED state

String ledState;

boolean restart = false;

// Wifi Scanning...
void prinScanResult(int networksFound)
{
  Serial.printf("%d network(s) found\n", networksFound);
  for (int i = 0; i < networksFound; i++)
  {
    Serial.printf("%d: %s, Ch:%d (%ddBm) %s\n", i + 1, WiFi.SSID(i).c_str(), WiFi.channel(i), WiFi.RSSI(i), WiFi.encryptionType(i) == ENC_TYPE_NONE ? "open" : "");
  }
  TestAP = WiFi.SSID(0).c_str();
}

// Initialize LittleFS
void initFS() {
  if (!LittleFS.begin()) {
    Serial.println("An error has occurred while mounting LittleFS");
  }
  else{
    Serial.println("LittleFS mounted successfully");
  }
}


// Read File from LittleFS
String readFile(fs::FS &fs, const char * path){
  Serial.printf("Reading file: %s\r\n", path);

  File file = fs.open(path, "r");
  if(!file || file.isDirectory()){
    Serial.println("- failed to open file for reading");
    return String();
  }

  String fileContent;
  while(file.available()){
    fileContent = file.readStringUntil('\n');
    break;
  }
  file.close();
  return fileContent;
}

// Write file to LittleFS
void writeFile(fs::FS &fs, const char * path, const char * message){
  Serial.printf("Writing file: %s\r\n", path);

  File file = fs.open(path, "w");
  if(!file){
    Serial.println("- failed to open file for writing");
    return;
  }
  if(file.print(message)){
    Serial.println("- file written");
  } else {
    Serial.println("- frite failed");
  }
  file.close();
}

// Initialize WiFi
bool initWiFi() {
//  if(ssid=="" || ip==""){
//    Serial.println("Undefined SSID or IP address.");
//    return false;
//  }

  WiFi.mode(WIFI_STA);

  WiFi.disconnect();
  delay(100);

  WiFi.scanNetworksAsync(prinScanResult);
//  localIP.fromString(ip.c_str());
//  localGateway.fromString(gateway.c_str());

//  if (!WiFi.config(localIP, localGateway, subnet)){
//    Serial.println("STA Failed to configure");
//    return false;
//  }
//  WiFi.begin(ssid.c_str(), pass.c_str());

//    WiFiManager wm;

    // reset settings - wipe stored credentials for testing
    // these are stored by the esp library
//    wm.resetSettings();

    // Automatically connect using saved credentials,
    // if connection fails, it starts an access point with the specified name ( "AutoConnectAP"),
    // if empty will auto generate SSID, if password is blank it will be anonymous AP (wm.autoConnect())
    // then goes into a blocking loop awaiting configuration and will return success result

//    bool res;
//    // res = wm.autoConnect(); // auto generated AP name from chipid
//    // res = wm.autoConnect("AutoConnectAP"); // anonymous ap
//    res = wm.autoConnect("AutoConnectAP","password"); // password protected ap
//
//    if(!res) {
//        Serial.println("Failed to connect");
//        // ESP.restart();
//    } 
//    else {
//        //if you get here you have connected to the WiFi    
//        Serial.println("connected...yeey :)");
//    }
//
//  Serial.println("Connecting to WiFi...");
//  delay(20000);
//  if(WiFi.status() != WL_CONNECTED) {
//    Serial.println("Failed to connect.");
//    return false;
//  }

//  Serial.println(WiFi.localIP());
//  return true;
}

// Replaces placeholder with LED state value
String processor(const String& var) {
  if(var == "TestAP") {
    return String(WiFi.SSID(0).c_str());
  }
//  return String();
}

                                                                                                                      //// Replaces placeholder with DHT values
                                                                                                                      //String processor1(const String& var){
                                                                                                                      //  //Serial.println(var);
                                                                                                                      //  if(var == "TEMPERATURE"){
                                                                                                                      //    return String(t);
                                                                                                                      //  }
                                                                                                                      //  else if(var == "HUMIDITY"){
                                                                                                                      //    return String(h);
                                                                                                                      //  }
                                                                                                                      //  return String();
                                                                                                                      //}

void setup() {
  // Serial port for debugging purposes
  Serial.begin(115200);

  initFS();

  // Set GPIO 2 as an OUTPUT
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
  
  // Load values saved in LittleFS
  ssid = readFile(LittleFS, ssidPath);
  pass = readFile(LittleFS, passPath);
//  ip = readFile(LittleFS, ipPath);
//  gateway = readFile (LittleFS, gatewayPath);
  Serial.println(ssid);
  Serial.println(pass);
//  Serial.println(ip);
//  Serial.println(gateway);
  if(initWiFi()) {
    // Route for root / web page
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
      request->send(LittleFS, "/index.html", "text/html", false, processor);
    });
    
    server.serveStatic("/", LittleFS, "/");
    
                                                                                                    //    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
                                                                                                    //      request->send_P(200, "text/html", index_html, processor1);
                                                                                                    //    });
  }
  else {
    // Connect to Wi-Fi network with SSID and password
    Serial.println("Setting AP (Access Point)");
    // NULL sets an open Access Point
    WiFi.softAP("ESP-WIFI-MANAGER");
//    dnsServer.start(53, "*", WiFi.softAPIP());  

    IPAddress IP = WiFi.softAPIP();
    Serial.print("AP IP address: ");
    Serial.println(IP); 

    
    // Web Server Root URL
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
      request->send(LittleFS, "/wifimanager.html", "text/html", false, processor);
    });
    
    server.serveStatic("/", LittleFS, "/");
    
    server.on("/", HTTP_POST, [](AsyncWebServerRequest *request) {
      int params = request->params();
      for(int i=0;i<params;i++){
        AsyncWebParameter* p = request->getParam(i);
        if(p->isPost()){
          // HTTP POST ssid value
          String dataaa = p->value().c_str();
          String naaam = p->name().c_str();
          Serial.println("=================================================================> " + naaam + ":::" + dataaa);
          if (p->name() == WifiSSID) {
            ssid = p->value().c_str();
            Serial.print("SSID set to: ");
            // Write file to save value
            writeFile(LittleFS, ssidPath, ssid.c_str());
          }
          // HTTP POST pass value
          if (p->name() == WifiPass) {
            pass = p->value().c_str();
            Serial.print("Password set to: ");
            Serial.println(pass);
            // Write file to save value
            writeFile(LittleFS, passPath, pass.c_str());
          }
          // HTTP POST ip value
//          if (p->name() == PARAM_INPUT_3) {
//            ip = p->value().c_str();
//            Serial.print("IP Address set to: ");
//            Serial.println(ip);
//            // Write file to save value
//          writeFile(LittleFS, ipPath, ip.c_str());
//          }
//          // HTTP POST gateway value
//          if (p->name() == PARAM_INPUT_4) {
//            gateway = p->value().c_str();
//            Serial.print("Gateway set to: ");
//            Serial.println(gateway);
//            // Write file to save value
//            writeFile(LittleFS, gatewayPath, gateway.c_str());
//          }
          //Serial.printf("POST[%s]: %s\n", p->name().c_str(), p->value().c_str());
        }
      }
//      restart = true;
      request->send(200, "text/plain", "Done. ESP will restart, connect to your router and go to IP address: ");
    });
    server.begin();
  }
}

void loop() {
  if (restart){
    delay(5000);
    ESP.restart();
  }
}
