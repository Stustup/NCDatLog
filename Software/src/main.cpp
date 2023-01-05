#include <Arduino.h>
#include <mainVar.h>
#include <debug.h>
#include <blink.h>
#include <WiFi.h>
#include <time.h>
#include <ESPAsyncWebServer.h>
#include <SPIFFS.h>

//===============================Objects 
led led_onboard(onBoardLED);
led led_user1(userLED);

AsyncWebServer server(port);

File file;

//===============================Variables
volatile boolean secFlag = 0;
boolean prevSecFlag = 1;
boolean ledFlag = 0;

void setup() {

  #ifdef debug
    Serial.begin(115200);
    Serial.println("Start");
    if(!SPIFFS.begin(true)) {
      Serial.println("An Error has occured while mounting SPIFFS");
      return;
    }
  #endif

  WiFi.begin(ssid, pw);

  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi...");
  }

  Serial.print("Connected to WiFi on : ");
  Serial.println(WiFi.localIP());

  //Timer Interrupt for 1sec
  timer1 = timerBegin(0, 80, true);
  timerAttachInterrupt(timer1, &onSecTimer, true);
  timerAlarmWrite(timer1, 1000000, true);
  timerAlarmEnable(timer1);

  server.on("/dashboard", HTTP_GET, [](AsyncWebServerRequest *request){request->send(SPIFFS, "/dashboard.html", "text/html");});
  server.on("/dashboard.css", HTTP_GET, [](AsyncWebServerRequest *request){request->send(SPIFFS, "/dashboard.css", "text/css");});

  server.begin();
  Serial.println("HTTP Server started!");

  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);

}

void loop() {

  if(secFlag){

    printTime();

    if(ledFlag) led_onboard.flipState();
    else if(!ledFlag) led_onboard.off();
    
    secFlag = 0;
  }

}

void IRAM_ATTR onSecTimer() {
  secFlag = !secFlag;
}

/*void handle_onConnect() {
  ledFlag = LOW;
  server.send(200, "text/html", SendHTML(ledFlag));
}

void handle_noInt() {
  timerStop(timer1);
  server.send(200, "text/html", SendHTML(secFlag));
}

void handle_resumeInt() {
  timerRestart(timer1);
  server.send(200, "text/html", SendHTML(secFlag));
}

void handle_ledOn() {
  ledFlag = HIGH;
  server.send(200, "text/html", SendHTML(ledFlag));
}

void handle_ledOff() {
  ledFlag = LOW;
  secFlag = LOW;
  server.send(200, "text/html", SendHTML(ledFlag));
}

void handle_NotFound() {
  server.send(404, "text/plain", "Not Found");
}

String SendHTML(uint8_t led1stat){
  String ptr = "<!DOCTYPE html> <html>\n";
  ptr +="<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  ptr +="<title>LED Control</title>\n";
  ptr +="<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
  ptr +="body{margin-top: 50px;} h1 {color: #444444;margin: 50px auto 30px;} h3 {color: #444444;margin-bottom: 50px;}\n";
  ptr +=".button {display: block;width: 80px;background-color: #3498db;border: none;color: white;padding: 13px 30px;text-decoration: none;font-size: 25px;margin: 0px auto 35px;cursor: pointer;border-radius: 4px;}\n";
  ptr +=".button-on {background-color: #3498db;}\n";
  ptr +=".button-on:active {background-color: #2980b9;}\n";
  ptr +=".button-off {background-color: #34495e;}\n";
  ptr +=".button-off:active {background-color: #2c3e50;}\n";
  ptr +="p {font-size: 14px;color: #888;margin-bottom: 10px;}\n";
  ptr +="</style>\n";
  ptr +="</head>\n";
  ptr +="<body>\n";
  ptr +="<h1>ESP32 Data Logger</h1>\n";
  
   if(led1stat)
  {ptr +="<p>LED Status: ON</p><a class=\"button button-off\" href=\"/ledOff\">OFF</a>\n";}
  else
  {ptr +="<p>LED Status: OFF</p><a class=\"button button-on\" href=\"/ledOn\">ON</a>\n";}

  ptr +="</body>\n";
  ptr +="</html>\n";
  return ptr;
}
*/

void printTime() {
  struct tm timeinfo;

  #ifdef debug
    if(!getLocalTime(&timeinfo)) {
      Serial.println("Failed to get Time");
      return;
    }
    Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");
  #endif
}